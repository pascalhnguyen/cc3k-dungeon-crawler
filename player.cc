#include "player.h"
#include "potion.h"
#include "enemy.h"

Player::Player(int hp, int atk, int def): Character{'@'}, gold{0}, alive{true}, curHP{hp}, atk{atk}, def{def} {}

void Player::gainHP(int amnt)
{
 curHP += amnt;

 if(curHP > this->getMaxHP())
 {
  curHP = this->getMaxHP();
 }
}

int Player::getCurHP() const { return curHP; }
int Player::getAtk() const { return atk; }
int Player::getDef() const { return def; }
int Player::getWealth() const { return gold; }
bool Player::getAlive() const { return alive; }

int Player::gainWealth(int amnt)
{
 gold += amnt;
 return this->getWealth();
}

Player::~Player() {}

int Player::Attacked(std::shared_ptr<Enemy> en)
{
 int success = rand() % 2; //since they have a 50% chance of missing
 int success_elf = rand() % 2; //elves get two attacks

 int damage = success*(100 * en->getAtk()) / (100 + this->getDef());
 if(en->getMarker() == 'E') 
  damage=(success+success_elf)*(100 * en->getAtk()) / (100 + this->getDef());

 curHP -= damage;
 if(curHP<=0)
 {
  alive = false;
  return -damage;
 }

 return damage;
}

int Player::getScore() const { return this->getWealth(); }

void Player::usePotion(const std::shared_ptr<Potion> pt)
{
 int amnt = pt->effectAmount();
 this->usePotionAmount(pt, amnt);
}

void Player::usePotionAmount(const std::shared_ptr<Potion> pt, int amnt)
{
 char stat = pt->effectTo();

 if(stat == 'H')
 {
  this->gainHP(amnt);
  if(curHP < 0) { curHP = 0; }
  if(curHP == 0) { alive = false; }
 }
 else if (stat == 'A')
 {
  atk += amnt;
  if(atk<0) { atk = 0; }
 }
 else if (stat == 'D')
 {
  def += amnt;
  if(def<0) { def = 0; }
 }

}
