#ifndef _POTION_H_
#define _POTION_H_

#include "subject.h"
#include "potiontype.h"
#include <string>

class PotionType;

class Potion: public Subject{
 std::shared_ptr<PotionType> pot;
 bool known; 

 public:
  Potion(int type); //CTOR: numbers are assigned to potions ( check file )
  std::string effectDescribe(); //returns string of name
  bool isKnown();
  void setKnown(bool k);

  char effectTo(); //returns which stat affected A-atk, H-hlth, D-def
  int effectAmount(); //returns amount changes stat
};

#endif
