#ifndef _GOLD_H_
#define _GOLD_H_

#include "observer.h"
#include "subject.h"
#include "notifytype.h"
#include "coord.h"

class Gold : public Subject, public Observer {
  int val;
  bool active;
  Coord guardian_loc;
 public:

  Gold(int type); //numbers are assigned to types of gold ( check doc )
  int worth() const; //returns worth
  bool is_active() const; //check if gold can be picked up or not
  Coord get_GL() const; //returns location of guardian
  void notify(Subject *who, int row, int col, NotifyType t);
};

#endif
