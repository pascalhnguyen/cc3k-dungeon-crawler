#ifndef _TROLL_H_
#define _TROLL_H_

#include "player.h"

class Troll: public Player{

 public:
  Troll();

  void resetStats() override;
  int getMaxHP() const override;
  int getBaseAtk() const override;
  int getBaseDef() const override;

  void newTurn() override;
};

#endif
