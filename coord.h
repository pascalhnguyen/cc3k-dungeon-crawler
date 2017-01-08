#ifndef __COORD_H__
#define __COORD_H__

struct Coord { 
    int row, col; 
    bool operator == (const Coord & c) const {
        return ((row == c.row) && (col == c.col));
    }
};

#endif
