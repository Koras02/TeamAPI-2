#include "pch.h"
#include "Boss.h"
#include "BossBullet.h"
#include "BossBullet1.h"
#include "BossBullet2.h"
#include "BossBullet3.h"
#include "ObjMgr.h"
#include <time.h>
CBoss::CBoss()
	: Leg1(0), Leg2(0), Leg3(0), fSpeed(5.f), fSpeed1(3.f), iMaxHp(10)
{
	Collision_Rec = {};
}

CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	m_pBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));

	srand(unsigned(time(NULL)));
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 100.f;
	m_tInfo.iCX = 150;
	m_tInfo.iCY = 200;
	Leg1 = m_tInfo.fX - 130.f;
	Leg2 = m_tInfo.fX - 20.f;
	Leg3 = m_tInfo.fX + 90.f;
	for (int i = 10; i > 0; --i)
	{
		rec[i].left = (i * 60) + 100;
		rec[i].right = ((i+1) * 60) + 100;
		rec[i].top = 0;
		rec[i].bottom = 25;
	}
}
int CBoss::Update()
{
	if (m_bDead)
	{
		iMaxHp -= 1;
		m_bDead = !m_bDead;

		if (iMaxHp == 0)
			return OBJ_DEAD;
	}
	if (Leg1 < 400)
	{
		Leg1 += fSpeed;
		Leg2 += fSpeed;
		Leg3 += fSpeed;
	}
	m_tInfo.fX += fSpeed1;
	

	if (_dwTime1 + 1000 <= GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<BossBullet>(Leg1, 250), OBJID::BOSSBULLET);
		_dwTime1 = GetTickCount();
	}
	if (_dwTime2 + 1500 <= GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<BossBullet>(Leg2, 250), OBJID::BOSSBULLET);
		_dwTime2 = GetTickCount();
	}
	if (_dwTime3 + 2000 <= GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<BossBullet>(Leg3, 250), OBJID::BOSSBULLET);
		_dwTime3 = GetTickCount();
	}
	if (_dwTime4 + 2000 <= GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<BossBullet1>(rand() % 800, 0), OBJID::BOSSBULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<BossBullet1>(rand() % 800, 0), OBJID::BOSSBULLET);
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<BossBullet2>(m_tInfo.fX, m_tInfo.fY), OBJID::BOSSBULLET);
		_dwTime4 = GetTickCount();
	}

	if (_dwTime5 + 2000 <= GetTickCount())
	{
		CObjMgr::Get_Instance()->Add_Object(Create_Bullet<BossBullet3>(), OBJID::BOSSBULLET);
		_dwTime1 = GetTickCount();
		_dwTime5 = GetTickCount();
	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CBoss::Late_Update()
{
	if (Leg1 >= 380 || Leg1 <= 200)
		fSpeed *= -1.f;
	if (m_tInfo.fX >= 500 || m_tInfo.fX <= 200)
		fSpeed1 *= -1.f;
	Update_Rect();
}

void CBoss::Render(HDC _DC)
{
	MoveToEx(_DC, m_tInfo.fX, m_tInfo.fY - 50, nullptr);
	LineTo(_DC, m_tInfo.fX - 50, m_tInfo.fY);
	LineTo(_DC, m_tInfo.fX + 50, m_tInfo.fY);
	LineTo(_DC, m_tInfo.fX, m_tInfo.fY - 50);
	MoveToEx(_DC, m_tInfo.fX - 50, m_tInfo.fY, nullptr);
	LineTo(_DC, m_tInfo.fX - 80, m_tInfo.fY + 100);
	LineTo(_DC, m_tInfo.fX + 80, m_tInfo.fY + 100);
	LineTo(_DC, m_tInfo.fX + 50, m_tInfo.fY);
	HBRUSH oldBrush = (HBRUSH)SelectObject(_DC, m_pBrush);
	Ellipse(_DC, m_tInfo.fX - 40, m_tInfo.fY + 10, m_tInfo.fX - 20, m_tInfo.fY + 50);
	Ellipse(_DC, m_tInfo.fX + 20, m_tInfo.fY + 10, m_tInfo.fX + 40, m_tInfo.fY + 50);
	SelectObject(_DC, oldBrush);
	MoveToEx(_DC, m_tInfo.fX, m_tInfo.fY +50, nullptr);
	LineTo(_DC, m_tInfo.fX, m_tInfo.fY +80);
	MoveToEx(_DC, m_tInfo.fX - 100, m_tInfo.fY + 100, nullptr);
	LineTo(_DC, m_tInfo.fX + 100, m_tInfo.fY + 100);
	LineTo(_DC, m_tInfo.fX + 110, m_tInfo.fY + 110);
	LineTo(_DC, m_tInfo.fX - 110, m_tInfo.fY + 110);
	LineTo(_DC, m_tInfo.fX - 100, m_tInfo.fY + 100);
	MoveToEx(_DC, m_tInfo.fX - 110, m_tInfo.fY + 110, nullptr);
	LineTo(_DC, Leg1, m_tInfo.fY + 150);
	MoveToEx(_DC, m_tInfo.fX , m_tInfo.fY +110, nullptr);
	LineTo(_DC, Leg2, m_tInfo.fY + 150);
	MoveToEx(_DC, m_tInfo.fX + 110, m_tInfo.fY + 110, nullptr);
	LineTo(_DC, Leg3, m_tInfo.fY + 150);
	for (int i = 0; i < iMaxHp; ++i)
	{
		Rectangle(_DC, rec[i].left, rec[i].top, rec[i].right, rec[i].bottom);
	}
	//Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	
	//Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBoss::Release()
{
	DeleteObject(m_pBrush);
}
