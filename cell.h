#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <vector>
#include <utility>
#include "subject.h"
#include "observer.h"

class Cell : public Observer {

    std::vector<char> cellType;  // to handle multiple objs in same space
    char origType;  // the tile that the cell would be if nothing's on it
    int r, c;

  public:
    Cell();                         // Default constructor
    char getType() const;           // returns type of the top object in stack
    void setType(char type);        // sets cell to desired type
    void removeTop();               // pops top object off of stack
    void setCoords(int r, int c);   // Tells me my row and column number.
    void clear();                   // changes non-initial tiles to floor tiles
    void notify(Subject *who, int row, int col, NotifyType t);
};

std::ostream &operator<<(std::ostream &out, const Cell &c);

#endif
