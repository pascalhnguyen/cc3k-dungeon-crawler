#include "potion.h"
#include "potiontype.h"
#include "pot_rh.h"
#include "pot_ba.h"
#include "pot_bd.h"
#include "pot_ph.h"
#include "pot_wa.h"
#include "pot_wd.h"

Potion::Potion(int type): Subject{'P'},known{false}
{
 if(type==0)
 {
  pot = std::make_shared<Pot_RH>();
 }
 else if(type==1)
 {
  pot = std::make_shared<Pot_BA>();
 }
 else if(type==2)
 {
  pot = std::make_shared<Pot_BD>();
 }
 else if(type==3)
 {
  pot = std::make_shared<Pot_PH>();
 }
 else if(type==4)
 {
  pot = std::make_shared<Pot_WA>();
 }
 else //type == 5
 {
  pot = std::make_shared<Pot_WD>();
 }
}

std::string Potion::effectDescribe() { return pot->typeDescribe(); }
bool Potion::isKnown() { return known; }
void Potion::setKnown(bool k) { known = k; }
char Potion::effectTo() { return pot->typeTo(); }
int Potion::effectAmount() { return pot->typeAmount(); }
