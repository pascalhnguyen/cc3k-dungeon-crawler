#include <iostream>
#include <iomanip>
#include <utility>
#include <fstream>
#include <vector>
#include <memory>
#include "debug.h"
#include "floor.h"
#include "cell.h"
#include "shade.h"
#include "sheep.h"
#include "drow.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "human.h"
#include "dwarf.h"
#include "halfling.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"
#include "pot_ba.h"
#include "pot_bd.h"
#include "pot_ph.h"
#include "pot_rh.h"
#include "pot_wa.h"
#include "pot_wd.h"
using namespace std;

//////////////////////
// HELPER FUNCTIONS //
//////////////////////

// checks if character corresponds to wall, tile, or chamber cell
bool is_init_tile(char c) {
    if ((c == '|') || (c == '-') || (c == '+') || (c == '.') ||
        (c == '#') || (c == ' ')) return true;
    return false;
}

// checks if character corresponds to name of an enemy character
bool is_enemy(char c) {
    if ((c == 'D') || (c == 'H') || (c == 'W') || (c == 'E') ||
        (c == 'O') || (c == 'M') || (c == 'L')) return true;
    return false;
}

Coord getloc(shared_ptr<Subject> s) { return Coord{s->getRow(),s->getCol()}; }

// translates directional name (no, sw, etc) into integer for use in fn below
int translate(string s) {
    if (s == "no") return 1;
    else if (s == "ne") return 2;
    else if (s == "ea") return 3;
    else if (s == "se") return 4;
    else if (s == "so") return 5;
    else if (s == "sw") return 6;
    else if (s == "we") return 7;
    else if (s == "nw") return 8;
    else return -9999;
}

// the reverse of above version of translate (overloading)
string translate(int dir) {
    if (dir == 1) return "no";
    else if (dir == 2) return "ne";
    else if (dir == 3) return "ea";
    else if (dir == 4) return "se";
    else if (dir == 5) return "so";
    else if (dir == 6) return "sw";
    else if (dir == 7) return "we";
    else if (dir == 8) return "nw";
    else return "Bad directional command.";
}

// returns full name of race abbreviation
string race_full(string race) {
    if (race == "s") return "Shade";
    else if (race == "v") return "Vampire";
    else if (race == "g") return "Goblin";
    else if (race == "t") return "Troll";
    else if (race == "d") return "Drow";
    else if (race == "h") return "Sheep";
    else return "Undefined Race";
}

Coord move(Coord curr, int dir) {
    // direction 1 is north, 2 is northeast, ... , 8 is northwest
    if (dir == 1) return Coord{curr.row-1,curr.col};
    else if (dir == 2) return Coord{curr.row-1,curr.col+1};
    else if (dir == 3) return Coord{curr.row,curr.col+1};
    else if (dir == 4) return Coord{curr.row+1,curr.col+1};
    else if (dir == 5) return Coord{curr.row+1,curr.col};
    else if (dir == 6) return Coord{curr.row+1,curr.col-1};
    else if (dir == 7) return Coord{curr.row,curr.col-1};
    else if (dir == 8) return Coord{curr.row-1,curr.col-1};
    else cout << "ERROR: Invalid directional number " << dir << endl;
    return Coord{-9999,-9999};
}

// checks if a coordinate is contained in a vector of coordinates
bool is_in(vector<Coord> coords, Coord c) {
    bool result = false;
    for (int i=0; i<coords.size(); i++) {
        if ((c.row == coords[i].row) && (c.col == coords[i].col)) result=true;
    }
    return result;
}

// returns a coordinate appearing least in a vector of coordinates
Coord least_times(vector<Coord> coords) {
    int least_times = 99999999;
    int index = -9999;
    Coord result {-9999,-9999};
    for (int i=0; i<coords.size(); i++) {
        Coord curr = coords[i];
        int times = 0;
        for (int j=0; j<coords.size(); j++) {
            if ((curr.row==coords[j].row)&&(curr.col==coords[j].col)) times++;
        }
        if (times < least_times) {
            least_times = times;
            index = i;
        }
    }
    if (coords.size() != 0) result = coords[index];
    return result;
}

// selects one of the rooms in chambers with equal probability,
// then selects one of the tiles in the room with equal probability
// returns the spawn_row and spawn col values
vector<int> random_loc(vector<vector<Coord>> chambers) {
    vector<int> result;
    int room_dice_faces = chambers.size();
    if (room_dice_faces <= 0) cout << "WARNING: 0 ROOMS FOUND!" << endl; 
    int room_roll = (rand() % room_dice_faces);
    if (chambers[room_roll].size() == 0) 
        cout << "WARNING: NO FREE SPACE IN ROOM " << room_roll << "!" << endl;
    int tile_roll = (rand() % (chambers[room_roll].size()));
    int spawn_row = chambers[room_roll][tile_roll].row;
    int spawn_col = chambers[room_roll][tile_roll].col;
    result.push_back(room_roll);
    result.push_back(tile_roll);
    result.push_back(spawn_row);
    result.push_back(spawn_col);
    return result;
}

string random_name(int faces, vector<string> names, vector<int> prob) {
    int n = names.size();
    if (prob.size() != n) cout << "WARNING: # of probs != # of names" << endl;
    int spinner = (rand() % faces);
    int counter = 0;
    for (int i=0; i<n; i++) {
        counter = counter + prob[i];
    }
    if (counter != faces) cout << "ERROR: PROBS DO NOT SUM TO 1" << endl;
    int spinner_land = spinner;
    for (int i=0; i<n; i++) {
        spinner_land = spinner_land - prob[i];
        if (spinner_land < 0) return names[i];
    }
    return "ERROR: Something bad happened. It shouldn't get to here.";
}

vector<vector<Coord>> remove(vector<vector<Coord>> chambers,Coord c,
bool removeall = false) {
    vector<vector<Coord>> result = chambers;
    for (int i=0; i<result.size(); i++) {
        for (int j=0; j<result[i].size(); j++) {
            if ((c.row == result[i][j].row) && (c.col == result[i][j].col)) {
                    result[i].erase(result[i].begin() + j);
                    if (!removeall) return result;
                }
        }
    }
    if (!removeall) cout << "REMOVE UNSUCCESSFUL: (" << c.row << "," << 
        c.col << ")" << endl;
    return result;
}

shared_ptr<Potion> generate_pot(int r, int c,string name="",bool rng=true) {
    const int potion_dice_faces = 6;
    vector<string> p_names = {"0","1","2","3","4","5"};
    vector<int> p_prob = {1,1,1,1,1,1};
    string sym = "";
    if (rng) sym = random_name(potion_dice_faces, p_names, p_prob);
    else sym = name;

    shared_ptr<Potion> pot = shared_ptr<Potion>{new Potion(stoi(sym))};
    return pot;
}

shared_ptr<Enemy> generate_enemy(int r,int c,string name="",bool rng=true) {
    const int monster_dice_faces = 18;
    vector<string> m_names = {"H","W","L","E","O","M"};
    vector<int> m_prob = {4,3,5,2,2,2};
    string sym = "";
    if (rng) sym = random_name(monster_dice_faces, m_names, m_prob);
    else sym = name;

    shared_ptr<Enemy> enemy;
    if (sym == "H") enemy = shared_ptr<Enemy>{new Human()};
    else if (sym == "W") enemy = shared_ptr<Enemy>{new Dwarf()};
    else if (sym == "L") enemy = shared_ptr<Enemy>{new Halfling()};
    else if (sym == "E") enemy = shared_ptr<Enemy>{new Elf()};
    else if (sym == "O") enemy = shared_ptr<Enemy>{new Orc()};
    else if (sym == "M") enemy = shared_ptr<Enemy>{new Merchant()};
    else cout << "ERROR: BAD NAME USED FOR MONSTER GENERATION" << endl;

    return enemy;
}

template <class T>
int get_index(vector<T> v, int row, int col, bool printerr = true) {
    int v_index = -9999;
    for (int i=0; i<v.size(); i++) {
        if ((v[i]->getRow() == row) && (v[i]->getCol() == col)) {
            v_index = i;
        }
    }
    if ((v_index == -9999) && (printerr))
        cout << "ERROR: CAN'T FIND OBJECT AT " << row << "," << col << endl;
    return v_index;
}

/////////////////////////////
// END OF HELPER FUNCTIONS //
/////////////////////////////

Floor::Floor(int nrow, int ncol): 
    board{},player{shared_ptr<Player>(new Shade())},player_race{"s"},enemies{},
    potions{},golds{},nrow{nrow},ncol{ncol},level{0},level_maps{},actionmsg{""},
    en_stats{"","",""},pl_eff{"","","",""},en_dmg{""},pausemode{false},
    end{false}
{
    // initialize an nrow x ncol array of blank cells
    for (int row=0; row<nrow; row++) {
        vector<shared_ptr<Cell>> floor_row;
        for (int col=0; col<ncol; col++) {
            shared_ptr<Cell> blank_cell(new Cell());
            blank_cell->setCoords(row,col);
            floor_row.push_back(blank_cell);
        }
        board.push_back(floor_row);
    }
}

// restarts the current level only.
void Floor::restartLevel() {
    enemies.clear();
    potions.clear();
    golds.clear();
    actionmsg = "";
    en_stats = {"","",""};
    pl_eff = {"","","",""};
    en_dmg = "";
    player->resetStats();
    init(level);
}

// restarts the whole game from level 1.
void Floor::restart() {
    player = shared_ptr<Player>(new Shade());
    player_race = "s";
    enemies.clear();
    potions.clear();
    golds.clear();
    actionmsg = 
        "Select race: 1=Shade, 2=Drow, 3=Vampire, 4=Goblin, 5=Troll, 6=Sheep";
    en_stats = {"","",""};
    pl_eff = {"","","",""};
    en_dmg = "";
    pausemode = false;
    level = 0;
    init(0);
}

void Floor::loadLevels(std::string floor_file) {
    string line;
    string default_map = "cc3kfloor.txt";
    ifstream try_open (floor_file);
    vector<string> level_map;
    // setting seed here because load levels is only called once
    srand(time(NULL));    

    if (!try_open.is_open()) {
        if (floor_file!="") actionmsg = "Error opening file "+floor_file+". ";
        actionmsg = actionmsg +"Using default map: "+default_map+ ".";
        floor_file = default_map;
    }
    else try_open.close();

    ifstream myfile (floor_file);

    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            if (nrow <= 0) {
                cout << "Number of rows is " << nrow << ". Exiting..." << endl;
                break; 
            }
            if (ncol != line.length()) {
                cout << "Warning: Initialized " << ncol << " columns but " << 
                "read length " << line.length() << " string in file." << endl;
            }
            level_map.push_back(line);
            if (level_map.size() >= nrow) {
                level_maps.push_back(level_map);
                level_map.clear();
            }
        }
        myfile.close();
    }
    init(0);
}

void Floor::init(int lvl) {
    // initialize board to the level n+1 layout, minus objects and monsters
    for (int row=0; row<nrow; row++) {
        for (int col=0; col<ncol; col++) {
            board[row][col]->clear();
            if (is_init_tile(level_maps[lvl][row][col]))
                board[row][col]->setType(level_maps[lvl][row][col]);
            else board[row][col]->setType('.');
        }
    }
}

vector<Coord> Floor::get_chamber_tiles(int row, int col) {
    vector<Coord> tiles;
    // first check if the given location is not a wall, chamber, or blank
    if (is_init_tile(board[row][col]->getType()) && 
        (board[row][col]->getType() != '.')) return tiles;
    
    Coord first_tile{row,col};
    tiles.push_back(first_tile);
    
    while (true) {
        vector<Coord> tiles_to_add;
        for (int i=0; i<tiles.size(); i++) {
            Coord curr_tile = tiles[i];
            for (int dir=1; dir<=8; dir++) {
                Coord tile_to_add = move(curr_tile,dir);
                if ((!(is_in(tiles, tile_to_add))) && 
                    (!(is_in(tiles_to_add,tile_to_add))) &&
                    (board[tile_to_add.row][tile_to_add.col]->getType()=='.'))
                    tiles_to_add.push_back(tile_to_add);
            }
        }
        if (tiles_to_add.size() == 0) break;
        tiles.insert(tiles.end(),tiles_to_add.begin(),tiles_to_add.end());
    }
    // delete the first tile if it was not a '.' (floor tile)
    if (board[row][col]->getType() != '.') tiles.erase(tiles.begin());
    return tiles;
}

vector<vector<Coord>> Floor::get_chambers() {
    vector<vector<Coord>> result;
    vector<Coord> tiles_added;
    for (int row=0; row<nrow; row++) {
        for (int col=0; col<ncol; col++) {
            Coord this_tile{row,col};
            if (!(is_in(tiles_added,this_tile))) {
                vector<Coord> chamber_to_add = get_chamber_tiles(row, col);
                if (chamber_to_add.size() != 0) {
                    result.push_back(chamber_to_add);
                    tiles_added.insert(tiles_added.end(),
                        chamber_to_add.begin(),chamber_to_add.end());
                }
            }
        }
    }
    return result;
}

void Floor::attach_all_cells(shared_ptr<Subject> subj) {
    for (int row = 0; row<nrow; row++) {
        for (int col = 0; col<ncol; col++) {
            subj->attachObservers(board[row][col]);
        }
    } 
}

void Floor::generate(string race, bool newcharacter) {
    restartLevel();
    vector<vector<Coord>> spawn_locs = get_chambers();
    
    // load stuff from level_maps into the actual floor
    Coord player_loc{-9999,-9999};
    bool player_created = false;
    int stairs_created = 0;
    int pots_created = 0;
    int enemies_created = 0;
    int dragons_created = 0;
    int golds_created = 0;

    // identify where the dragons and hoards are to properly assign them
    vector<Coord> dragons;
    vector<Coord> hoards;
    for (int row=0; row<nrow; row++) {
        for (int col=0; col<ncol; col++) {
            char marker = level_maps[level][row][col];
            if (marker == 'D') dragons.push_back(Coord{row,col});
            if (marker == '9') hoards.push_back(Coord{row,col});
        }
    }
    if (dragons.size()!=hoards.size()) cout<<"ERROR: DRAGONS != HOARDS"<<endl;
    vector<vector<Coord>> dragsaround;
    for (int i=0; i<hoards.size(); i++) {
        Coord curr_hoard = hoards[i];
        vector<Coord> around;
        for (int dir=1; dir<=8; dir++) {
            Coord neighbour = move(curr_hoard,dir);
            if (is_in(dragons,neighbour)) around.push_back(neighbour);
        }
        if (around.size() == 0) cout << "ERROR: No Dragon near hoard." << endl;
        dragsaround.push_back(around);
    }

    // assigns drags to hoards: 0 = dragons, 1 = hoards
    vector<Coord> dragons_new;
    vector<Coord> hoards_new;
    vector<vector<Coord>> assign_drags;
    int drags_unassigned = 1;

    while (drags_unassigned > 0) {
        // first check if any hoars only have one dragon beside them
        bool onedraghoards = true;
        while (onedraghoards) {
            onedraghoards = false;
            for (int i=0; i<dragsaround.size(); i++) {
                if (dragsaround[i].size() == 1) {
                    onedraghoards = true;
                    hoards_new.push_back(hoards[i]);
                    dragons_new.push_back(dragsaround[i][0]);
                }
            }
            
            for (int i=0; i<dragons_new.size(); i++) {
                dragsaround = remove(dragsaround,dragons_new[i],true);
            }
        }
        // otherwise, unassociate a dragon associated to least # of hoards
        Coord dr_least_hoards;
        vector<Coord> unstack_da;

        for (int i=0; i<dragsaround.size(); i++) {
            unstack_da.insert(unstack_da.end(),dragsaround[i].begin(),
                                dragsaround[i].end());
        }

        dr_least_hoards = least_times(unstack_da);

        for (int i=0; i<dragsaround.size(); i++) {
            if (is_in(dragsaround[i],dr_least_hoards)) {
                dragsaround[i].clear();
                dragsaround[i].push_back(dr_least_hoards);
                break;
            }
        }
        
        for (int i=0; i<dragons_new.size(); i++) {
            dragsaround = remove(dragsaround,dragons_new[i],true);
        }
        // check for end condition
        drags_unassigned = 0;
        for (int i=0; i<dragsaround.size(); i++) {
            drags_unassigned = drags_unassigned + dragsaround[i].size();
        }
    }

    assign_drags.push_back(dragons_new);
    assign_drags.push_back(hoards_new);

    for (int row=0; row<nrow; row++) {
        for (int col=0; col<ncol; col++) {
            char marker = level_maps[level][row][col];
            if ((marker >= '0') && (marker <= '5')) {
                shared_ptr<Potion> pot{new Potion(marker-'0')};
                potions.push_back(pot);
                attach_all_cells(potions.back());
                potions.back()->setRowCol(row,col);
                spawn_locs = remove(spawn_locs, Coord{row,col});
                pots_created++;
            }
            if ((marker >= '6') && (marker <= '9')) {
                shared_ptr<Gold> gold{new Gold(marker-'0')};
                if (marker == '9') {
                    int hoard_ind = -9999;
                    for (int i=0; i<assign_drags[1].size(); i++) {
                        if (assign_drags[1][i] == Coord{row,col}) hoard_ind=i;
                    }
                    if (hoard_ind < 0) cout<<"ERROR: HOARD NOT FOUND!"<<endl;
                    // assign dragons to gold
                    int dr_row = assign_drags[0][hoard_ind].row;
                    int dr_col = assign_drags[0][hoard_ind].col;
                    shared_ptr<Enemy> dragon = shared_ptr<Enemy>{new Dragon()};
                    enemies.push_back(dragon);
                    attach_all_cells(enemies.back());
                    // attach gold as an observer of its dragon
                    enemies.back()->attachObservers(gold);
                    enemies.back()->setRowCol(dr_row,dr_col);
                    spawn_locs = remove(spawn_locs, Coord{dr_row,dr_col});
                    dragons_created++;
                }
                golds.push_back(gold);
                attach_all_cells(golds.back());
                golds.back()->setRowCol(row,col);
                spawn_locs = remove(spawn_locs, Coord{row,col});
                golds_created++;
            }
            if (marker == '@') {
                player_loc = Coord{row,col};
                player_created = true;
            }
            if (marker == '\\') { 
                board[row][col]->setType('\\');
                spawn_locs = remove(spawn_locs, Coord{row,col});
                stairs_created++;
            }
            if ((marker == 'H') || (marker == 'E') || (marker == 'O') ||
                (marker == 'L') || (marker == 'W') || (marker == 'M')) {
                string marker_s = ""; 
                marker_s = marker_s + marker;
                shared_ptr<Enemy> enemy=generate_enemy(row,col,marker_s,false);
        
                enemies.push_back(enemy);
                attach_all_cells(enemies.back());
                enemies.back()->setRowCol(row,col);
                spawn_locs = remove(spawn_locs, Coord{row,col});
                enemies_created++;
            }
        }
    }

    vector<int> player_spawn = random_loc(spawn_locs);
    // spawn character, create new character if specified
    if (newcharacter) {
        if (race == "s") player = shared_ptr<Player>(new Shade());
        if (race == "d") player = shared_ptr<Player>(new Drow());
        if (race == "v") player = shared_ptr<Player>(new Vampire());
        if (race == "g") player = shared_ptr<Player>(new Goblin());
        if (race == "t") player = shared_ptr<Player>(new Troll());
        if (race == "h") player = shared_ptr<Player>(new Sheep());
        player_race = race;
        attach_all_cells(player);
    }

    if (player_created)
        player->setRowCol(player_loc.row, player_loc.col);
    else {
        player_loc = Coord{player_spawn[2],player_spawn[3]};
        player->setRowCol(player_loc.row,player_loc.col);
    }
    spawn_locs = remove(spawn_locs, player_loc);
    actionmsg = "Player character has spawned. ";

    // spawn staircase, if not spawned already
    vector<vector<Coord>> stair_locs = spawn_locs;
    if (stairs_created == 0) {
        // ensure that staircase does not spawn in same room as player
        vector<Coord> pl_room=get_chamber_tiles(player_loc.row,player_loc.col);
        for (int i=0; i<pl_room.size(); i++) {
            Coord pl_room_tile = Coord{pl_room[i].row,pl_room[i].col};
            for (int j=0; j<stair_locs.size(); j++) {
                if (is_in(stair_locs[j],pl_room_tile))
                    stair_locs.erase(stair_locs.begin()+j);
            }
        }
        vector<int> stair_spawn = random_loc(stair_locs);
        board[stair_spawn[2]][stair_spawn[3]]->setType('\\');
        spawn_locs = remove(spawn_locs, Coord{stair_spawn[2],stair_spawn[3]});
    }

  // if either stairs or player were not in file, generate ALL missing objects
  if ((stairs_created == 0) || !(player_created)) {

    // spawn potions
    for (int i=0; i<10-pots_created; i++) {
        shared_ptr<Potion> pot;
        vector<int> pot_spawn = random_loc(spawn_locs);
        
        pot = generate_pot(pot_spawn[2],pot_spawn[3]); 
        potions.push_back(pot);
        attach_all_cells(potions.back());
        potions.back()->setRowCol(pot_spawn[2],pot_spawn[3]);
        spawn_locs = remove(spawn_locs, Coord{pot_spawn[2],pot_spawn[3]});
    }

    // spawn gold
    const int gold_dice_faces = 8;
    vector<string> g_names = {"small","normal","dragon"};
    vector<int> g_prob = {2,5,1};

    for (int i=0; i<10-golds_created; i++) {
        vector<int> gold_spawn = random_loc(spawn_locs);
        string sym = random_name(gold_dice_faces, g_names, g_prob);
        shared_ptr<Gold> gold;
        if (sym == "small") gold = shared_ptr<Gold>{new Gold(6)};
        if (sym == "normal") gold = shared_ptr<Gold>{new Gold(7)};
        if (sym == "dragon") {
            gold = shared_ptr<Gold>{new Gold(9)};
            // if dragon hoard is spawned, spawn dragon beside it
            vector<vector<Coord>> drag_tiles;
            vector<Coord> drag_tiles_vec;
            while (true) {
                for (int dir=1; dir<=8; dir++) {
                    Coord curr_tile{gold_spawn[2],gold_spawn[3]};
                    Coord drag_tile = move(curr_tile,dir);
                    if (board[drag_tile.row][drag_tile.col]->getType() == '.')
                        drag_tiles_vec.push_back(drag_tile);
                }
                if (drag_tiles_vec.size() == 0) 
                    cout << "NO SPOTS FOR DRAGON! RESIMULATING" << endl;
                else {
                    drag_tiles.push_back(drag_tiles_vec);
                    break;
                }
            }
            vector<int> dr_spawn = random_loc(drag_tiles);
            shared_ptr<Enemy> dragon = shared_ptr<Enemy>{new Dragon()};
            enemies.push_back(dragon);
            attach_all_cells(enemies.back());
            // attaches gold as an observer of its defending dragon
            enemies.back()->attachObservers(gold);
            enemies.back()->setRowCol(dr_spawn[2],dr_spawn[3]);
            spawn_locs = remove(spawn_locs, Coord{dr_spawn[2],dr_spawn[3]});
        }
        golds.push_back(gold);
        attach_all_cells(golds.back());
        golds.back()->setRowCol(gold_spawn[2],gold_spawn[3]);
        spawn_locs = remove(spawn_locs, Coord{gold_spawn[2],gold_spawn[3]});
    }

    // spawn monsters
    for (int i=0; i<20-enemies_created; i++) {
        vector<int> enemy_spawn = random_loc(spawn_locs);
        shared_ptr<Enemy> enemy;
        enemy = generate_enemy(enemy_spawn[2],enemy_spawn[3]);
        enemies.push_back(enemy);
        attach_all_cells(enemies.back());
        enemies.back()->setRowCol(enemy_spawn[2],enemy_spawn[3]);
        spawn_locs = remove(spawn_locs, Coord{enemy_spawn[2],enemy_spawn[3]});
    }
  }
}

bool Floor::movePlayer(string dir) {
    Coord player_tile = getloc(player);
    if (translate(dir) < 0) {
        actionmsg = "Bad directional command. Please try again.";
        return false;
    }
    Coord move_to = move(player_tile, translate(dir));
    char dest_type = board[move_to.row][move_to.col]->getType();
    pl_eff = {"","","",""};
    en_dmg = "";
    en_stats = {"","",""};

    // checks if destination square is a legit location
    if ((dest_type == '.') || (dest_type == '+') || (dest_type == '#')) {
        player->setRowCol(move_to.row,move_to.col);
        actionmsg = "";
        bool pot_near = false;
        // check if there is a potion nearby, and identify if possible
        for (int d=1; d<=8; d++) {
            Coord surround = move(move_to, d);
            if (board[surround.row][surround.col]->getType() == 'P') {
                if (!pot_near) actionmsg += "You see some potions nearby: ";
                pot_near = true;
                int pot_index = get_index<shared_ptr<Potion>>(potions,
                    surround.row,surround.col);
                char stat = potions[pot_index]->effectTo();
                int effect_amt = potions[pot_index]->effectAmount();
                if (potions[pot_index]->isKnown()) 
                    actionmsg = actionmsg + to_string(effect_amt) + stat + 
                        " (" + translate(d) + ") ";
                else actionmsg = actionmsg + "Unknown (" + translate(d) + ") ";
            }
        }
    }
    else if (dest_type == 'G') {
        // determine if the gold is a dragon hoard or not
        int gold_index = 
            get_index<shared_ptr<Gold>>(golds,move_to.row,move_to.col);
        int gold_val = golds[gold_index]->worth();
        bool gold_active = golds[gold_index]->is_active();

        if (gold_index == -9999) actionmsg = "404: GOLD NOT FOUND! ";
        // now determine what to do with the gold
        else if (gold_active) {
            int before_gold = player->getWealth();
            player->gainWealth(gold_val);
            int after_gold = player->getWealth();
            pl_eff[3]=pl_eff[3]+"("+to_string(after_gold-before_gold)+") ";

            actionmsg = "You found " + to_string(gold_val) + " coins! ";
            golds[gold_index]->notifyObservers(NotifyType::remove,
                    golds[gold_index]->getRow(),golds[gold_index]->getCol());
            golds.erase(golds.begin()+gold_index);
            player->setRowCol(move_to.row,move_to.col);
        }
        else if (!gold_active) {
            player->setRowCol(move_to.row,move_to.col);
            actionmsg = "Gold chest is locked. ";
        }
    }
    else if (dest_type == '\\') {
        if (level+1 >= level_maps.size()) {
            actionmsg = "Congratulations! You have completed level ";
            actionmsg = actionmsg + to_string(level+1) + ".";
            end = true;
            return false;
        }
        level++;
        player->setRowCol(-1,-1);
        generate(player_race, false);
        player->newTurn();
        // returns "unsuccessful move" to prevent monsters attacking on spawn
        return false;
    }

    else {
        actionmsg = "Invalid move destination. Please try again.";
        return false;
    }
    player->newTurn();
    return true;
}

bool Floor::triggerAggro(shared_ptr<Enemy> enemy) {
    char marker = enemy->getMarker();
    Coord en_loc{enemy->getRow(),enemy->getCol()};
    // if not dragon, check if hostile and player is beside the monster
    if (is_enemy(marker) && (marker != 'D') && (enemy->isHostile())) {
        for (int dir=1; dir<=8; dir++) {
            Coord nb = move(en_loc,dir);
            if (board[nb.row][nb.col]->getType() == '@') return true;
        }
    }
    if ((marker == 'D') && (enemy->isHostile())) {
        enemy->notifyObservers(NotifyType::pingGuardian,
                                enemy->getRow(),enemy->getCol());
        // find the gold associated with that dragon
        Coord gold_loc{-9999,-9999};
        for (int i=0; i<golds.size(); i++) {
            if (golds[i]->get_GL() == en_loc)
                gold_loc = Coord{golds[i]->getRow(),golds[i]->getCol()};
        }
        
        for (int dir=1; dir<=8; dir++) {
            Coord nb_en = move(en_loc,dir);;
            Coord nb_gold = move(gold_loc,dir);
            if ((board[nb_gold.row][nb_gold.col]->getType() == '@') ||
                (board[gold_loc.row][gold_loc.col]->getType() == '@') ||
                (board[nb_en.row][nb_en.col]->getType() == '@')) return true;
        }
    }
    return false;
}

void Floor::enemyAction() {
  // keep track of the monsters that already moved so they don't move again
  vector<Coord> already_moved;
  if (!pausemode) {

    for (int row=0; row<nrow; row++) {
        for (int col=0; col<ncol; col++) {
            char marker = board[row][col]->getType();

            if (is_enemy(marker)) {
                int enemy_index=get_index<shared_ptr<Enemy>>(enemies,row,col);
                // if enemy already moved, then can't aggro since turn ends
                bool aggro = (triggerAggro(enemies[enemy_index]) &&
                                (!is_in(already_moved,Coord{row,col})));

                vector<Coord> dest_vec;
                for (int dir=1; dir<=8; dir++) {
                    Coord move_to = move(Coord{row,col}, dir);
                    if (board[move_to.row][move_to.col]->getType() == '.') {
                        dest_vec.push_back(move_to);
                    }
                }
                // if no free space or enemy is dragon or enemy already moved 
                // or aggro is triggered, then don't move
                if ((dest_vec.size() > 0) && (marker != 'D') && (!aggro) &&
                    (!is_in(already_moved,Coord{row,col}))) {
                    int spinner = (rand() % dest_vec.size());
                    Coord dest = dest_vec[spinner];
                    enemies[enemy_index]->setRowCol(dest.row,dest.col);
                    already_moved.push_back(dest);
                }
                else if ((aggro)&&(alive())) enemyAttack(enemies[enemy_index]);
            }
        }
    }
  }
}

bool Floor::usePotion(string dir) {
    pl_eff = {"","","",""};
    en_dmg = "";

    Coord current{player->getRow(),player->getCol()};
    if (translate(dir) < 0) {
        actionmsg = "Bad directional command. Try again.";
        return false;
    }
    Coord pot_loc = move(current,translate(dir));
    if (board[pot_loc.row][pot_loc.col]->getType() != 'P') {
        actionmsg = "No potion at destination. Try again.";
        return false;
    }
    else {
        int pot_index=get_index<shared_ptr<Potion>>(
                                            potions,pot_loc.row,pot_loc.col);
        char stat_aff = potions[pot_index]->effectTo();
        int before_hp = player->getCurHP();
        int before_atk = player->getAtk();
        int before_def = player->getDef();
        player->usePotion(potions[pot_index]);
        int after_hp = player->getCurHP();
        int after_atk = player->getAtk();
        int after_def = player->getDef();
        if (stat_aff == 'H') 
            pl_eff[0]=pl_eff[0]+"("+to_string(after_hp-before_hp)+") ";
        if (stat_aff == 'A') 
            pl_eff[1]=pl_eff[1]+"("+to_string(after_atk-before_atk)+") ";
        if (stat_aff == 'D') 
            pl_eff[2]=pl_eff[2]+"("+to_string(after_def-before_def)+") ";
        string eff = potions[pot_index]->effectDescribe();
        // update action message, known potions, and clean up
        actionmsg = "You find and drink the potion. Effect: " + eff;
        potions[pot_index]->notifyObservers(NotifyType::remove,
                potions[pot_index]->getRow(),potions[pot_index]->getCol());
        potions.erase(potions.begin()+pot_index);
        for (int i=0; i<potions.size(); i++) {
            if (potions[i]->effectDescribe()==eff) potions[i]->setKnown(true);
        }
    }
    return true;
}

bool Floor::attack(string dir) {
    pl_eff = {"","","",""};
    en_dmg = "";
    Coord current{player->getRow(),player->getCol()};
    if (translate(dir) < 0) {
        actionmsg = "Bad directional command. Try again.";
        return false;
    }
    Coord enemy_loc = move(current,translate(dir));
    if (!(is_enemy(board[enemy_loc.row][enemy_loc.col]->getType()))) {
        actionmsg = "No enemy at destination. Try again.";
        return false;
    }
    else {
        int enemy_index=get_index<shared_ptr<Enemy>>(
                                        enemies,enemy_loc.row,enemy_loc.col);
        int dmg_dealt = enemies[enemy_index]->Attacked(player);
        char marker = enemies[enemy_index]->getMarker();
        // enemies automatically become aggressive when attacked
        enemies[enemy_index]->setHostile(true);
        // output combat information
        actionmsg = "PC attacks " + string(1,marker) + ". ";
        en_dmg = en_dmg + "(" + to_string(abs(dmg_dealt)) + ") ";
        en_stats[0] = to_string(enemies[enemy_index]->getCurHP());
        en_stats[1] = to_string(enemies[enemy_index]->getAtk());
        en_stats[2] = to_string(enemies[enemy_index]->getDef());
        // if enemy dies, perform necessary cleanup
        if (dmg_dealt<0) {
            int loot_amt = enemies[enemy_index]->getDrop()->worth(); 
            actionmsg = actionmsg + "You kill " + marker + " and loot ";
            actionmsg = actionmsg + to_string(loot_amt) + " gold. ";
            
            int before_gold = player->getWealth();
            player->gainWealth(loot_amt);
            int after_gold = player->getWealth();
            pl_eff[3]=pl_eff[3]+"("+to_string(after_gold-before_gold)+") ";

            enemies.erase(enemies.begin()+enemy_index);
            // if merchant dies though, trigger all other merchants on floor
            if (marker == 'M') {
                for (int i=0; i<enemies.size(); i++) {
                    if (enemies[i]->getMarker() == 'M')
                        enemies[i]->setHostile(true); 
                }
                actionmsg += "You've angered all remaining merchants! ";
            }
        }
    }
    player->newTurn();
    return true;
}

void Floor::enemyAttack(std::shared_ptr<Enemy> enemy) {
    char marker = enemy->getMarker();
    int dmg_taken = player->Attacked(enemy);
    pl_eff[0] = pl_eff[0] + marker + "(" + to_string(abs(dmg_taken)) + ") ";
    if (dmg_taken < 0) actionmsg = actionmsg + "You are dead! ";
}

void Floor::toggleFreeze() { 
    if (pausemode) pausemode = false;
    else pausemode = true;
}

void Floor::displayFloor() {
    for (int row=0; row<nrow; row++) {
        for (int col=0; col<ncol; col++) {
            cout << *(board[row][col]);
        }
        cout << '\n';
    }
    displayPlayerInfo();
}

void Floor::displayPlayerInfo() {
    if (player == nullptr) cout << "No player initialized." << endl;
    else {
        string HP = to_string(player->getCurHP()) + "/" + 
                    to_string(player->getMaxHP());
        string ATK = to_string(player->getAtk()) + "/" +
                    to_string(player->getBaseAtk());
        string DEF = to_string(player->getDef()) + "/" +
                    to_string(player->getBaseDef());
        cout << "Race: " << right << setw(8) << race_full(player_race) <<
                " " << left << setw(11) << setfill(' ') << " " << "Wealth: " <<
                right << setw(3) << player->getWealth() << " " << left << 
                setw(12) << setfill(' ') << pl_eff[3] << "Level: " << right << 
                setw(5) << level+1 << endl;
        cout << "HP: " << right << setw(10) << HP << " " << left << setw(35) << 
                setfill(' ') << pl_eff[0] << "Enemy: " << right << setw(5) << 
                en_stats[0] << " " << left << setw(10) << setfill(' ') <<
                en_dmg << endl;
        cout << "Atk: " << right << setw(9) << ATK << " " << left << setw(35)<<
                setfill(' ') << pl_eff[1] << "Atk: " << right << setw(7) << 
                en_stats[1] << endl;
        cout << "Def: " << right << setw(9) << DEF << " " << left << setw(35)<<
                setfill(' ') << pl_eff[2] << "Def: " << right << setw(7) << 
                en_stats[2] << endl;
        cout << "Action: " << actionmsg << endl;
    }
}

bool Floor::alive() { return player->getAlive(); }
int Floor::getScore() { return player->getScore(); }
bool Floor::gameEnd() { return end; }

Floor::~Floor() {}
