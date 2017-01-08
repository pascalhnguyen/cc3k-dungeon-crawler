#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "notifytype.h"
#include <vector>
#include <memory>

class Observer;

class Subject {
 std::vector < std::shared_ptr<Observer> > observers;

 int r=-1; //default until set
 int c=-1;
 char marker;

 public:
  Subject(char marker);

  void notifyObservers(NotifyType, int row, int col);
  void attachObservers(std::shared_ptr<Observer>); //note: attach and then set location

  int getRow() const;
  int getCol() const;
  void setRowCol(int new_r, int new_c); //notifies observers

  char getMarker() const;

  virtual ~Subject() = 0;

};




#endif
