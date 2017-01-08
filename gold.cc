#include "gold.h"
#include "notifytype.h"
#include "subject.h"
#include "observer.h"
#include "coord.h"

Gold::Gold(int type): Subject{'G'}, val{0}, active{false}, guardian_loc{-1,-1}
{
 if(type==6) { val = 1; active = true; }
 else if(type==7) { val = 2; active = true; }
 else if(type==8) { val = 4; active = true; }
 else if(type==9) { val = 6; active = false; }
 else { val = 0; active = true; }
}

int Gold::worth() const { return val; }

bool Gold::is_active() const { return active; }

Coord Gold::get_GL() const { return guardian_loc; }

void Gold::notify(Subject *who, int row, int col, NotifyType t) {
    // Indicates dragon has been slain
    if ((t == NotifyType::remove) && (val == 6)) { active = true; }
    // Get coordinates of guardian (dragon) when needed
    if ((t==NotifyType::pingGuardian)&&(val==6)) guardian_loc = Coord{row,col};
} 
