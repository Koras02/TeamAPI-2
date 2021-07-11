#include "pch.h"
#include "BossBullet1.h"

BossBullet1::BossBullet1()
{

}

BossBullet1::~BossBullet1()
{
	Release();
}

void BossBullet1::Initialize()
{
	m_pBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	m_tInfo.iCX = 30;
	m_tInfo.iCY = 60;

	m_fSpeed = 10.f;
}

int BossBullet1::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	m_tInfo.fY += m_fSpeed;

	Update_Rect();

	return OBJ_NOEVENT;
}

void BossBullet1::Late_Update()
{
}

void BossBullet1::Render(HDC _DC)
{

	HBRUSH oldBrush = (HBRUSH)SelectObject(_DC, m_pBrush);
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(_DC, oldBrush);
}

void BossBullet1::Release()
{
	DeleteObject(m_pBrush);
}
