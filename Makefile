CXX = g++
INC= inc/
CXXFLAGS = -Wall -MMD -I$(INC)

EXEC = quadris
OBJECTS = multiplier.o main.o game.o level.o textdisplay.o window.o block.o iblock.o  oblock.o lblock.o jblock.o zblock.o sblock.o tblock.o pos.o
DEPENDS = ${OBJECTS:.o=.d}
X11 = -lX11
NCURSES = -lncurses
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${X11} ${NCURSES}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: clean
