#ifndef _POT_BD_H_
#define _POT_BD_H_

#include "potiontype.h"

class Pot_BD: public PotionType
{

 public:
  std::string typeDescribe() const override;
  char typeTo() const override;
  int typeAmount() const override;

};

#endif
