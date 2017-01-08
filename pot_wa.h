#ifndef _POT_WA_H_
#define _POT_WA_H_

#include "potiontype.h"

class Pot_WA: public PotionType{

 public:
  std::string typeDescribe() const override;
  char typeTo() const override;
  int typeAmount() const override;
};

#endif

