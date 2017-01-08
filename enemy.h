#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "character.h"

class Player;
class Gold;

class Enemy: public Character {
 int drop;

 protected:
  int curHP, atk, def;
  bool hostile;

 public:
  Enemy(char marker, int drop, int hp, int atk, int def, bool hostile);

  int getCurHP() const override;
  int getAtk() const override;
  int getDef() const override;
  bool isHostile() const;
  //sets whether or not enemy is hostile to player
  void setHostile(bool h);

  std::shared_ptr<Gold> getDrop() const; //returns gold dropped

  //enemy attacked by player. returns damage.
  //if enemy dies, damage is returned as negative and observers are notified
  virtual int Attacked(std::shared_ptr<Player>);

  virtual ~Enemy()= 0;
};

#endif
