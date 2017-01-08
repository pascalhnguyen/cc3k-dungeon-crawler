#ifndef _HALFLING_H_
#define _HALFLING_H_

#include "enemy.h"

class Halfling: public Enemy{

 public:
  Halfling();
  int Attacked(std::shared_ptr<Player>) override;
};

#endif
