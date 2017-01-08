#ifndef _POT_PH_H_
#define _POT_PH_H_

#include "potiontype.h"

class Pot_PH: public PotionType{

 public:
  std::string typeDescribe() const override;
  char typeTo() const override;
  int typeAmount() const override;
};

#endif
