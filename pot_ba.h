#ifndef _POT_BA_H_
#define _POT_BA_H_

#include "potiontype.h"

class Pot_BA: public PotionType{

 public:
  std::string typeDescribe() const override;
  char typeTo() const override;
  int typeAmount() const override;
};

#endif
