/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "weapons.h"
#include "game.h"
#include "wpn_pindad_ss2_v5.h"

enum augblitz_e
{
	AUG_IDLE1,
	AUG_RELOAD,
	AUG_DRAW,
	AUG_SHOOT1,
	AUG_SHOOT2,
	AUG_SHOOT3, 
OFF,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};

LINK_ENTITY_TO_CLASS(weapon_pindad_ss2_v5, CPindad_ss2_v5)

void CPindad_ss2_v5::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_pindad_ss2_v5");

	Precache();
	m_iId = WEAPON_GALIL;

	SET_MODEL(ENT(pev), "models/w_aug_a3_blitz.mdl");

	m_iDefaultAmmo = AUG_DEFAULT_GIVE;
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;

	FallInit();
}

void CPindad_ss2_v5::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_pindad_ss2_v5.mdl");

	PRECACHE_MODEL("models/p_pindad_ss2_v5.mdl");
PRECACHE_MODEL("models/sight/v_muzzle_bottom.mdl");



	PRECACHE_SOUND("weapons/pindad_ss2_v5-1.wav");
	PRECACHE_SOUND("weapons/aug_clipout.wav");
	PRECACHE_SOUND("weapons/aug_clipin.wav");
	PRECACHE_SOUND("weapons/aug_boltpull.wav");
	PRECACHE_SOUND("weapons/aug_boltslap.wav");
	PRECACHE_SOUND("weapons/aug_forearm.wav");
PRECACHE_SOUND("weapons/zoom_generic_in.wav");
PRECACHE_SOUND("weapons/zoom_generic_out.wav");
	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFirePindad_ss2_v5 = PRECACHE_EVENT(1, "events/ak47.sc");
}

int CPindad_ss2_v5::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = AUG_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 17;
	p->iId = WEAPON_GALIL;
	p->iFlags = 0;
	p->iWeight = 25;

	return 1;
}


BOOL CPindad_ss2_v5::Deploy(void)
{
m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	iShellOn = 1;

return DefaultDeploy("models/billflx/v_pindad_ss2_v5.mdl", "models/p_pindad_ss2_v5_mdl", AUG_DRAW, "rifle", 0);

}

void CPindad_ss2_v5::QuickDeploy()
{
SendWeaponAnim(ANIM4, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}


void CPindad_ss2_v5::SecondaryAttack(void)
{

switch (m_pPlayer->m_iFOV)
	{
		case 90:

SetThink(&CPindad_ss2_v5::Fov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;

		default:
SetThink(&CPindad_ss2_v5::offFov2);
	pev->nextthink = gpGlobals->time + 0.0000009;



 break;
	}

	m_pPlayer->ResetMaxSpeed();
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}


void CPindad_ss2_v5::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 

SetThink(&CPindad_ss2_v5::Fov3);
	pev->nextthink = gpGlobals->time + 0.0000009;


#ifndef CLIENT_DLL
if (weapon_sight_pindad_ss2_v5.value == 0)
CLIENT_COMMAND(m_pPlayer->edict(), "reddot_scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 1) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 1; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 2) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 2; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 3) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 3; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 4) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 4; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 5) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 5; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 6) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 6; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 7) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 7; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 8) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 8; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 9) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 9; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 10) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 10; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 11) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 11; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 12) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 12; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 13) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 13; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 14) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 14; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 15) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 15; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 16) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 16; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 17) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 17; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 18) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 18; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 19) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 19; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 20) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 20; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 21) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 21; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 22) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 22; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 23) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 23; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 24) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 24; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 25) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 25; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 26) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 26; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 27) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 27; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 28) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 28; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 29) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 29; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 30) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 30; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 31) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 31; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 32) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 32; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 33) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 33; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 34) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 34; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 35) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 35; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 36) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 36; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 37) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 37; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 38) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 38; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 39) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 39; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 40) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 40; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 41) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 41; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 42) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 42; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 43) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 43; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 44) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 44; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 45) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 45; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 46) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 46; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 47) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 47; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 48) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 48; Custom_Scope\n");
else if (weapon_sight_pindad_ss2_v5.value == 49) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 49; Custom_Scope\n");
#endif
}

void CPindad_ss2_v5::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CPindad_ss2_v5::Fov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CPindad_ss2_v5::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CPindad_ss2_v5::Fov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CPindad_ss2_v5::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 65; 

SetThink(&CPindad_ss2_v5::Fov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CPindad_ss2_v5::Fov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 55; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_in.wav", 0.2, 2.4);

m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_muzzle_bottom.mdl");
SendWeaponAnim(AUG_IDLE1, UseDecrement() != FALSE);
}

//offfov

void CPindad_ss2_v5::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CPindad_ss2_v5::offFov3);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CPindad_ss2_v5::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CPindad_ss2_v5::offFov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CPindad_ss2_v5::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CPindad_ss2_v5::offFov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}
void CPindad_ss2_v5::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 
SendWeaponAnim(AUG_IDLE1, 0);
SetThink(&CPindad_ss2_v5::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CPindad_ss2_v5::offFov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_out.wav", 0.2, 2.4);


m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/v_pindad_ss2_v5.mdl");



}


void CPindad_ss2_v5::PrimaryAttack(void)
{
		Pindad_ss2_v5Fire((0.0) * m_flAccuracy, 0.0825, FALSE);
}

void CPindad_ss2_v5::Pindad_ss2_v5Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	m_bDelayFire = true;
	m_iShotsFired++;
	m_flAccuracy = ((float)(m_iShotsFired * m_iShotsFired * m_iShotsFired) / 215.0) + 0.3;

	if (m_flAccuracy > 1)
		m_flAccuracy = 1;

	if (m_iClip <= 0)
	{
		if (m_fFireOnEmpty)
		{
			PlayEmptySound();
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.2;
		}

		return;
	}

	m_iClip--;
	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 8192, 2, BULLET_PLAYER_556MM, 20, 0.96, m_pPlayer->pev, FALSE, m_pPlayer->random_seed);

//Vector vecSrc = m_pPlayer->GetGunPosition();

if (m_iClip > 0)
{
SendWeaponAnim(AUG_SHOOT1, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(AUG_IDLE1, 0);
}
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/pindad_ss2_v5-1.wav", VOL_NORM, ATTN_NORM);


	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(),m_usFirePindad_ss2_v5, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;

#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.9;

	if (m_pPlayer->pev->velocity.Length2D() > 0)
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	else if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	else
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);

}

void CPindad_ss2_v5::Reload(void)
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == AUG_MAX_CLIP)
return;
	if (DefaultReload(AUG_MAX_CLIP, NULL, 2))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
			SetThink(&CPindad_ss2_v5::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 2;


		
		
	}
SendWeaponAnim(AUG_RELOAD, 0);
}

void CPindad_ss2_v5::QuickReload()
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == AUG_MAX_CLIP)
return;
	if (DefaultReloadQuick(AUG_MAX_CLIP, NULL, 2))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
			SetThink(&CPindad_ss2_v5::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 2;


	}
SendWeaponAnim(ANIM5, 0);
}

void CPindad_ss2_v5::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(AUG_IDLE1, UseDecrement() != FALSE);
}
