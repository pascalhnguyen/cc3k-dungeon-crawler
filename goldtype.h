#ifndef _GOLDTYPE_H_
#define _GOLDTYPE_H_

class GoldType {
 int val;

 public:
  int worth() const { return val; }
  virtual ~GoldType() = 0;
};

#endif
