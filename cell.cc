#include <utility>
#include <string>
#include "subject.h"
#include "observer.h"
#include "cell.h"
using namespace std;

Cell::Cell():
    cellType{}, r{0}, c{0} {}

char Cell::getType() const {
    if (cellType.size() == 0) return '!'; // this means an uninitialized cell
    else return cellType.back();
}

void Cell::setType(char type) { cellType.push_back(type); }

void Cell::removeTop() {
    if (cellType.size() <= 1) 
        cout << "ERROR: Attempting to move from empty cell. Location "
            << "(" << r << "," << c << ")" << endl;
    else cellType.pop_back();
}

void Cell::setCoords(int r, int c) { this->r = r; this->c = c; }

void Cell::clear() { cellType.clear(); }

void Cell::notify(Subject *who, int row, int col, NotifyType t) {
    if ((row == r) && (col == c)) {
        char who_type = who->getMarker();
        if (t == NotifyType::moveTo) setType(who_type);
        if ((t == NotifyType::moveFrom) || (t == NotifyType::remove)) {
            if ((row >= 0) && (col >= 0)) removeTop();
        }
    }

}

ostream &operator<<(ostream &out, const Cell &c) {
    out << c.getType();
    return out;
}
