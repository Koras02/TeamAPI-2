#pragma once
#include "Obj.h"
class BossBullet2 : public CObj
{
public:
	BossBullet2();
	virtual ~BossBullet2();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
private:
	POINT	m_tCenterPos;
	float	m_fCenterAngle;
	float	m_fCenterSpeed;
	float	m_fMisale;
	bool	m_bStart;
};

