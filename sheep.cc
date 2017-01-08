#include "sheep.h"
#include "potion.h"

const int dHP = 250;
const int dAtk = 20;
const int dDef = 100;

Sheep::Sheep(): Player{dHP, dAtk, dDef} {}

void Sheep::successKill()
{
  atk += 5;
  ++def;
}

void Sheep::resetStats(){ atk = dAtk; def = dDef; }

int Sheep::getBaseAtk() const { return dAtk; }
int Sheep::getBaseDef() const { return dDef; }
int Sheep::getMaxHP() const { return dHP; }

void Sheep::usePotion(const std::shared_ptr<Potion> pt)
{
 if(pt->effectAmount() < 0) {  this->usePotionAmount(pt, 0); }
 else { this->usePotionAmount(pt, pt->effectAmount()); }
};
