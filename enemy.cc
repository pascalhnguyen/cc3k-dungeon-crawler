#include "enemy.h"
#include "gold.h"
#include "player.h"

Enemy::Enemy(char marker, int drop, int hp, int atk, int def, bool hostile): 
Character{marker}, drop{drop}, curHP{hp}, atk{atk}, def{def}, hostile{hostile} {}

int Enemy::getCurHP() const { return curHP; }
int Enemy::getAtk() const { return atk; }
int Enemy::getDef() const { return def; }
bool Enemy::isHostile() const { return hostile; }
void Enemy::setHostile(bool h) { hostile = h; }

Enemy::~Enemy() {}

std::shared_ptr<Gold> Enemy::getDrop() const
{
 return std::make_shared<Gold>(drop);
}

int Enemy::Attacked(std::shared_ptr<Player> pl)
{
 pl->successAttack(this->getMarker());

 int damage = (100 * pl->getAtk()) / (100 + this->getDef());
 curHP -= damage;
 if(curHP<=0)
 {
  this->notifyObservers(NotifyType::remove, this->getRow(), this->getCol());
  pl->successKill();
  return -damage;
 }

 return damage;
}
