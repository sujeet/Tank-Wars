# CFLAGS = -D N=50
CFLAGS = -Wall -pedantic -g -I./include/
MACROS = -DMAP_FILE=\"map.txt\" -DLOG_FILE=\"log.txt\" -DHTML_FILE=\"game_display.html\" -lpthread

all: bin/TankWars.exe bin/log_to_html.exe
	echo "Done!"

bin/TankWars.exe: obj/Arena.o \
                  obj/Tank.o \
                  obj/TankWars.o \
                  obj/Map.o \
                  obj/Misc_Classes.o \
                  obj/Info.o \
                  obj/DecisionMaker1.o \
                  obj/DecisionMaker2.o
	if [ ! -e bin ]; then mkdir bin; fi;
	g++ -o $@ $^ $(CFLAGS) $(MACROS)

bin/log_to_html.exe: src/log_to_html.cpp \
                     include/Constants.h 
	if [ ! -e bin ]; then mkdir bin; fi;
	g++ -o $@ $< $(CFLAGS) $(MACROS)

obj/TankWars.o: src/TankWars.cpp \
                include/Arena.h \
                include/Constants.h
	if [ ! -e obj ]; then mkdir obj; fi;
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

obj/Arena.o: src/Arena.cpp \
             include/Arena.h \
             include/Tank.h \
             include/Map.h \
             include/Constants.h \
             include/DecisionMaker1.h \
             include/DecisionMaker2.h \
             include/Misc_Classes.h
	if [ ! -e obj ]; then mkdir obj; fi;
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

obj/Tank.o: src/Tank.cpp \
            include/Tank.h \
            include/Map.h \
            include/Constants.h
	if [ ! -e obj ]; then mkdir obj; fi;
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

obj/DecisionMaker1.o: DecisionMaker1.cpp \
                      include/DecisionMaker.h \
                      include/Info.h \
                      include/Constants.h \
                      include/Misc_Classes.h
	if [ ! -e obj ]; then mkdir obj; fi;
	g++ -o $@ -c $< $(CFLAGS) $(MACROS) -DDECISION_MAKER=DecisionMaker1

obj/DecisionMaker2.o: DecisionMaker2.cpp \
                      include/DecisionMaker.h \
                      include/Info.h \
                      include/Constants.h \
                      include/Misc_Classes.h
	if [ ! -e obj ]; then mkdir obj; fi;
	g++ -o $@ -c $< $(CFLAGS) $(MACROS) -DDECISION_MAKER=DecisionMaker2

obj/Map.o: src/Map.cpp \
	       include/Map.h \
           include/Misc_Classes.h \
           include/Constants.h
	if [ ! -e obj ]; then mkdir obj; fi;
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

obj/Misc_Classes.o: src/Misc_Classes.cpp \
                    include/Misc_Classes.h \
                    include/Constants.h
	if [ ! -e obj ]; then mkdir obj; fi;
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

obj/Info.o: src/Info.cpp \
            include/Info.h \
            include/Misc_Classes.h \
            include/Map.h \
            include/Tank.h \
            include/Constants.h
	if [ ! -e obj ]; then mkdir obj; fi;
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

# Now the phony targets.-------------------------------------------------
bot1:
	make obj/DecisionMaker1.o

bot2:
	make obj/DecisionMaker2.o

play: all
	./bin/TankWars.exe
	./bin/log_to_html.exe
	if [ ! -e output ]; then mkdir output; fi;
	mv log.txt ./output/log.txt
	mv game_display.html ./output/game_display.html

display:
	firefox ./output/game_display.html

clean:
	rm ./obj/*.o ./src/*~ ./include/*~ -f
