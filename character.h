#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "subject.h"

class Character: public Subject {

  virtual void successAttack(char) {}
  virtual void successKill() {}

 public:
  Character(char marker): Subject{marker} {}

  //accessor functions
  virtual int getCurHP() const = 0;
  virtual int getDef() const = 0;
  virtual int getAtk() const = 0;


  friend class Enemy;
};

#endif
