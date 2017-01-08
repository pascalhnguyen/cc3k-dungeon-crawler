#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "notifytype.h"

class Subject;

class Observer {

 public:
  virtual void notify(Subject *, int row, int col, NotifyType) = 0;

};

#endif
