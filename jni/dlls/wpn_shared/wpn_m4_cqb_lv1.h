#ifndef WPN_MAC10_H
#define WPN_MAC10_H
#ifdef _WIN32
#pragma once
#endif

//mac10
#define MAC10_MAX_SPEED			190
#define MAC10_DAMAGE			29
#define MAC10_RANGE_MODIFER		0.82
#define MAC10_RELOAD_TIME		3.15

class CM4_cqb_lv1 : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL Deploy() override;
	float GetMaxSpeed() override { return ASSAULT_SPEED; }
	int iItemSlot() override { return PRIMARY_WEAPON_SLOT; }
	void PrimaryAttack() override;
void QuickDeploy() override;

void QuickReload() override;
void Fov2();
void Fov3();
void Fov4();
void Fov5();
void Fov6();


void offFov2();
void offFov3();
void offFov4();
void offFov5();
void offFov6();
void SecondaryAttack() override;
	void Reload() override;
	void WeaponIdle() override;
	BOOL UseDecrement() override {
#ifdef CLIENT_WEAPONS
		return TRUE;
#else
		return FALSE;
#endif
	}
	KnockbackData GetKnockBackData() override { return { 250.0f, 200.0f, 250.0f, 90.0f, 0.7f }; }

public:
	void M4_cqb_lv1Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireM4_cqb_lv1;
};

#endif
