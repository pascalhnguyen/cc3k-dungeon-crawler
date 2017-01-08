#ifndef _POT_WD_H_
#define _POT_WD_H_

#include "potiontype.h"

class Pot_WD: public PotionType{

 public:
  std::string typeDescribe() const override;
  char typeTo() const override;
  int typeAmount() const override;
};

#endif

