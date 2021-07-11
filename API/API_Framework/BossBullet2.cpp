#include "pch.h"
#include "BossBullet2.h"
#include "ObjMgr.h"

BossBullet2::BossBullet2()
	: m_fCenterAngle(0.f), m_fCenterSpeed(0.f), m_bStart(true)
{
	ZeroMemory(&m_tCenterPos, sizeof(m_tCenterPos));
}

BossBullet2::~BossBullet2()
{
	Release();
}

void BossBullet2::Initialize()
{

	m_pBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	m_tInfo.iCX = 10;
	m_tInfo.iCY = 10;
	m_tInfo.fX = 50;
	m_tInfo.fY = 50;

	m_fSpeed = 5.f;
	m_fDis = 150.f;
	
	m_pTarget = CObjMgr::Get_Instance()->Get_Boss();

	m_fCenterSpeed = 5.f;
}

int BossBullet2::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	m_fCenterAngle += 5;
	m_tInfo.fX = m_pTarget->Get_Info().fX	+cosf(m_fCenterAngle * PI / 180.f) * m_fDis;
	m_tInfo.fY =m_pTarget->Get_Info().fY+ 70 -sinf(m_fCenterAngle * PI / 180.f) * m_fDis;


	m_fAngle += m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void BossBullet2::Late_Update()
{
}

void BossBullet2::Render(HDC _DC)
{
	HBRUSH oldBrush = (HBRUSH)SelectObject(_DC, m_pBrush);
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_DC, oldBrush);
}

void BossBullet2::Release()
{
	DeleteObject(m_pBrush);
}
