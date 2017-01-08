#ifndef _SHEEP_H_
#define _SHEEP_H_

#include "player.h"

class Sheep: public Player{

 protected:
  void successKill() override;

 public:
  Sheep();

  void resetStats() override;
  int getBaseAtk() const override;
  int getBaseDef() const override;
  int getMaxHP() const override;

  void usePotion(const std::shared_ptr<Potion>) override;
};

#endif
