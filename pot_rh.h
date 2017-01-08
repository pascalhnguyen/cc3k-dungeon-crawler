#ifndef _POT_RH_H_
#define _POT_RH_H_

#include "potiontype.h"

class Pot_RH: public PotionType{

 public:
  std::string typeDescribe() const override;
  char typeTo() const override;
  int typeAmount() const override;
};

#endif

