#include "pch.h"
#include "BossBullet.h"

BossBullet::BossBullet()
{
}

BossBullet::~BossBullet()
{
	Release();
}

void BossBullet::Initialize()
{
	m_pBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	m_tInfo.iCX = 30;
	m_tInfo.iCY = 30;

	m_fSpeed =5.f;
}

int BossBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	m_tInfo.fY += m_fSpeed;
	if(rand()%2 == 0)
		m_tInfo.fX += rand()%5;
	else
		m_tInfo.fX -= rand()%5;
	Update_Rect();

	return OBJ_NOEVENT;
}

void BossBullet::Late_Update()
{
}

void BossBullet::Render(HDC _DC)
{
	HBRUSH oldBrush = (HBRUSH)SelectObject(_DC, m_pBrush);
	Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_DC, oldBrush);
}

void BossBullet::Release()
{
	DeleteObject(m_pBrush);
}
