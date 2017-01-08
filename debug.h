#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <iostream>
#include <vector>
#include <memory>
#include "coord.h"
#include "floor.h"

std::ostream& operator << (std::ostream &os, Coord c) { 
    os << '(' << c.row << ',' << c.col << ')';
    return os;
}

Coord getloc(std::shared_ptr<Subject>);

void print (std::vector<std::vector<Coord>> array, bool verbose = false) {
    std::cout << "Length: " << array.size() << std::endl;
    for (int i=0; i<array.size(); i++) {
        std::cout << "Sublength " << i << ": ";
        if (!verbose) std::cout << array[i].size() << std::endl;
        if (verbose) {
            for (int j=0; j<array[i].size(); j++) {
                std::cout << array[i][j];
                if (j<array[i].size()-1) std::cout << " ";
            }
            std::cout << std::endl;
        }
    }
}

void print (std::vector<std::shared_ptr<Enemy>> ens) {
    std::cout << "Enemies: ";
    for (int i=0; i<ens.size(); i++) {
        if (ens[i] == nullptr) std::cout << "Bad enemy initialization." << 
            std::endl;
        else std::cout << ens[i]->getMarker() <<
                    ens[i]->getCurHP() << getloc(ens[i]);
        if (i<ens.size()-1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void print (std::vector<std::shared_ptr<Potion>> ps) {
    std::cout << "Potions: ";
    for (int i=0; i<ps.size(); i++) {
        if (ps[i] == nullptr) std::cout << "Bad potion initialization." << 
            std::endl;
        else {
            char pot_known;
            if (ps[i]->isKnown()) pot_known = 'K';
            else pot_known = 'U';
            std::cout << ps[i]->effectDescribe() << "(" << pot_known << ")" <<
                getloc(ps[i]);
        }
        if (i<ps.size()-1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void print (std::vector<std::shared_ptr<Gold>> gs) {
    std::cout << "Gold: ";
    for (int i=0; i<gs.size(); i++) {
        if (gs[i] == nullptr) std::cout << "Bad gold initialization." << 
            std::endl;
        else std::cout << gs[i]->worth() << getloc(gs[i]);
        if (i<gs.size()-1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void print (std::vector<std::vector<std::string>> levels, int level) {
    for (int j=0; j<levels[level].size(); j++) {
        std::cout << levels[level][j] << std::endl;
    }
}

#endif
