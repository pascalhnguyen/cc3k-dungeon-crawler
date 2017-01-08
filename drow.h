#ifndef _DROW_H_
#define _DROW_H_

#include "player.h"

class Drow: public Player {

 public:
  Drow();

  void resetStats() override;
  int getMaxHP() const override;
  int getBaseAtk() const override;
  int getBaseDef() const override;

  void usePotion(const std::shared_ptr<Potion>) override;

  int Attacked(std::shared_ptr<Enemy>) override;
};

#endif
