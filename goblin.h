#ifndef _GOBLIN_H_
#define _GOBLIN_H_

#include "player.h"

class Goblin: public Player{

 public:
  Goblin();

  void resetStats() override;
  int getMaxHP() const override;
  int getBaseAtk() const override;
  int getBaseDef() const override;

  int Attacked(std::shared_ptr<Enemy>) override;

  void successKill() override;
};

#endif
