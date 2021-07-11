#include "pch.h"
#include "BossBullet3.h"
#include "ObjMgr.h"
BossBullet3::BossBullet3()
{
}

BossBullet3::~BossBullet3()
{
    Release();
}

void BossBullet3::Initialize()
{
	m_tInfo.iCX = 30;
	m_tInfo.iCY = 50;

	m_fSpeed = 5.f;
	m_pBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
}

int BossBullet3::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(this , OBJID::PLAYER);
	
	if (m_pTarget)
	{
		float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
		float fDia = sqrtf(fX * fX + fY * fY);
		float	fRad = acosf(fX / fDia);
		m_fAngle = fRad * 180.f / PI;

		if (m_pTarget->Get_Info().fY >= m_tInfo.fY)
			m_fAngle *= -1.f;


	}

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void BossBullet3::Late_Update()
{
}

void BossBullet3::Render(HDC _DC)
{

	HBRUSH oldBrush = (HBRUSH)SelectObject(_DC, m_pBrush);
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_DC, oldBrush);
}

void BossBullet3::Release()
{
	DeleteObject(m_pBrush);
}
