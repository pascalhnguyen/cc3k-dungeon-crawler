#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "character.h"

class Potion;
class Enemy;

class Player: public Character {
 int gold;

 protected:
  bool alive;
  int curHP, atk, def;

  virtual void gainHP(int amnt); //inc HP by amnt, doesn't exceed max
  void usePotionAmount(const std::shared_ptr<Potion>, int);

 public:
  Player(int hp, int atk, int def);

  int getWealth() const; //returns current wealth
  int gainWealth(int amnt); //adds wealth and returns current

  int getCurHP() const override;
  int getAtk() const override;
  int getDef() const override;
  virtual void resetStats() = 0;
  virtual int getMaxHP() const = 0;
  virtual int getBaseAtk() const = 0;
  virtual int getBaseDef() const = 0;
  bool getAlive() const;

  //when player is attacked by en, returns damage done to player
  //if player dies, damage is returned as negative
  virtual int Attacked(std::shared_ptr<Enemy> en);

  virtual int getScore() const; //returns score
  virtual void newTurn() {}//call at the end of each turn

  virtual void usePotion(const std::shared_ptr<Potion>); //uses potion
  virtual ~Player() = 0;
};

#endif
