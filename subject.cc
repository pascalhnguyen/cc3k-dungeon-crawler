#include "subject.h"
#include "observer.h"
#include <memory>

Subject::Subject(char marker): marker{marker} {}

void Subject::notifyObservers(NotifyType nt, int row, int col)
{
 for(auto &x : observers) x->notify(this, row, col, nt);
}

void Subject::attachObservers(std::shared_ptr<Observer> ob)
{
 observers.emplace_back(ob);
}

int Subject::getRow() const { return r; }

int Subject::getCol() const { return c; }

void Subject::setRowCol(int new_r, int new_c)
{
  int old_r = r;
  int old_c = c;
  r = new_r;
  c = new_c;
  this->notifyObservers(NotifyType::moveFrom, old_r, old_c);
  this->notifyObservers(NotifyType::moveTo, new_r, new_c);
}

char Subject::getMarker() const { return marker; }

Subject::~Subject() {}
