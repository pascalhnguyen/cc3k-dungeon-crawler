CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -Wno-sign-compare
EXEC = cc3k
OBJECTS = floor.o cell.o subject.o main.o player.o enemy.o potion.o gold.o sheep.o shade.o drow.o vampire.o troll.o goblin.o pot_ba.o pot_bd.o pot_ph.o pot_rh.o pot_wa.o pot_wd.o human.o dwarf.o halfling.o elf.o orc.o merchant.o dragon.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -lncurses

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
