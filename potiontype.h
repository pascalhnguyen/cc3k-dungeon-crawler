#ifndef _POTIONTYPE_H_
#define _POTIONTYPE_H_

#include <string>

class PotionType {

 public:
  virtual std::string typeDescribe() const = 0;
  virtual char typeTo() const = 0;
  virtual int typeAmount() const = 0;
};

#endif
