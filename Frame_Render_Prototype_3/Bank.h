#ifndef __BANK_H__
#define __BANK_H__

#include "ArmorBank.h"
#include "EntityBank.h"
#include "SkillBank.h"
#include "WeaponBank.h"

namespace Bank {
static EntityBank* _EntityBank = EntityBank::getEntityBank();
static SkillBank* _SkillBank = SkillBank::getSkillBank();
static ArmorBank* _ArmorBank = ArmorBank::getArmorBank();
static WeaponBank* _WeaponBank = WeaponBank::getWeaponBank();
}  // namespace Bank

#endif