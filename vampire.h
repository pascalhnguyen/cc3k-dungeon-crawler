#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_

#include "player.h"

class Vampire: public Player{
  void gainHP(int amnt) override;

 public:
  Vampire();

  void resetStats() override;
  int getMaxHP() const override;
  int getBaseAtk() const override;
  int getBaseDef() const override;

  void successAttack(char marker) override;
};

#endif
