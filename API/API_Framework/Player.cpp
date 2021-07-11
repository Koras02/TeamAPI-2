#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Shield.h"
#include "ObjMgr.h"
#include "ScrewBullet.h"
#include "GuideBullet.h"
#include "LineMgr.h"
#include "KeyMgr.h"


CPlayer::CPlayer()
	: m_bJump(false), m_fJumpPower(0.f), m_fJumpTime(0.f), m_fJumpY(0.f)
{
	ZeroMemory(&m_tPosin, sizeof(m_tPosin));
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initalize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;

	m_fSpeed = 5.f;

	m_fPosinDis = 100.f;

	m_fJumpPower = 50.f;
}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Key_Check();
	Jumping();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	m_tPosin.x = (LONG)(m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * m_fPosinDis);
	m_tPosin.y = (LONG)(m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * m_fPosinDis);
}

void CPlayer::Render(HDC _DC)
{
	Update_Rect();
	Rectangle(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}

void CPlayer::Key_Check()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		m_tInfo.fX -= 5.f;
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		m_tInfo.fX += 5.f;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		if (!m_bJump)
			m_fJumpY = m_tInfo.fY;

		m_bJump = true;
	}
}

void CPlayer::Jumping()
{
	float fY = 0.f;
	bool LineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_fJumpTime += 0.2f;
		m_tInfo.fY = m_fJumpY - ((m_fJumpPower * m_fJumpTime) - (0.5f * 9.8f * m_fJumpTime * m_fJumpTime));

		if (LineCol && m_tInfo.fY >= fY)
		{
			m_bJump = false;
			m_fJumpTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	else if (LineCol)
		m_tInfo.fY = fY;
}

CObj* CPlayer::Create_Shield()
{
	return CAbstractFactory<CShield>::Create(this);
}
