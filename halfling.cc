#include "halfling.h"
#include "gold.h"
#include "player.h"
#include <cstdlib>

Halfling::Halfling(): Enemy{'L', 6, 100, 15, 20, true} {}

int Halfling::Attacked(std::shared_ptr<Player> pl)
{
 int success = rand() % 2; //since they have a 50% chance of missing
 if(success) { return 0; }
 return this->Enemy::Attacked(pl);
}
