#ifndef _SHADE_H_
#define _SHADE_H_

#include "player.h"

class Shade: public Player{

 public:
  Shade();

  void resetStats() override;
  int getMaxHP() const override;
  int getBaseAtk() const override;
  int getBaseDef() const override;

  int getScore() const override;
};

#endif
