#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <iostream>
#include <vector>
#include <memory>
#include "cell.h"
#include "observer.h"
#include "enemy.h"
#include "potion.h"
#include "gold.h"
#include "coord.h"

class Floor {
    std::vector<std::vector<std::shared_ptr<Cell>>> board;
    std::shared_ptr<Player> player;
    std::string player_race;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Potion>> potions;
    std::vector<std::shared_ptr<Gold>> golds;
    const int nrow;
    const int ncol;
    int level;
    std::vector<std::vector<std::string>> level_maps;
    std::string actionmsg;
    std::vector<std::string> en_stats; //0 = hp, 1 = atk, 2 = def
    std::vector<std::string> pl_eff; //0 = hp, 1 = atk, 2 = def, 3 = gold
    std::string en_dmg;
    bool pausemode;
    bool end;
public:
    Floor(int nrow, int ncol);
    void restartLevel();
    void restart();
    void loadLevels(std::string floor_file);
    void init(int lvl);
    std::vector<Coord> get_chamber_tiles(int row, int col);
    std::vector<std::vector<Coord>> get_chambers();
    void attach_all_cells(std::shared_ptr<Subject> subj);
    void generate(std::string race, bool newcharacter);

    bool movePlayer(std::string dir);
    bool triggerAggro(std::shared_ptr<Enemy> enemy);
    void enemyAction();
    bool usePotion(std::string dir);
    bool attack(std::string dir);
    void enemyAttack(std::shared_ptr<Enemy> enemy);
    void toggleFreeze();
    void displayFloor();
    void displayPlayerInfo();
    bool alive();
    int getScore();
    bool gameEnd();
    ~Floor();
};

#endif
