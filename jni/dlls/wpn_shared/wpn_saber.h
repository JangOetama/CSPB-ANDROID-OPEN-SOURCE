#ifndef WPN_KNIFE_H
#define WPN_KNIFE_H
#ifdef _WIN32
#pragma once
#endif

//knife
#define KNIFE_BODYHIT_VOLUME		128
#define KNIFE_WALLHIT_VOLUME		512
#define KNIFE_MAX_SPEED			200
#define KNIFE_MAX_SPEED_SHIELD		180

class CSaber : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL CanDrop() override { return FALSE; }
	BOOL Deploy() override;
	void Holster(int skiplocal) override;
	float GetMaxSpeed() override { return KNIFE_SPEED; }
	int iItemSlot() override { return KNIFE_SLOT; }
	void PrimaryAttack() override;
void QuickDeploy() override;


void SecondaryAttack() override;
void ResetRunIdle();
void start();
void walk();
void end();
void idle();
void slash();
void stab();
	BOOL UseDecrement() override {
#ifdef CLIENT_WEAPONS
		return TRUE;
#else
		return FALSE;
#endif
	}
	void WeaponIdle() override;

public:
	void EXPORT SwingAgain();
	void EXPORT Smack();

	NOXREF void WeaponAnimation(int iAnimation);
	int Stab(int fFirst);
	int Swing(int fFirst);

void DelayedPrimaryAttack();
	void DelayedSecondaryAttack();
void DelayedSecondaryAttack2();
	float GetPrimaryAttackDamage() const
	{
		float flDamage = 100;

		return flDamage;
	}
	float GetSecondaryAttackDamage() const
	{
		float flDamage = 100;

		return flDamage;
	}

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();

float m_flNextRunIdle;
float m_tPreTime;
	float m_flNextRunEnd;

public:
	TraceResult m_trHit;
	unsigned short m_usCombat;
};

#endif
