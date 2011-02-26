# CFLAGS = -D N=50
CFLAGS = -Wall -pedantic -g
MACROS = -DMAP_FILE=\"map.txt\" -DLOG_FILE=\"log.txt\" -DMAP_SIZE=51 -DHTML_FILE=\"tank_video_player.html\"

all: TankWars.exe log_to_html.exe
	echo "Done!"

TankWars.exe: Arena.o Tank.o TankWars.o Map.o Misc_Classes.o Info.o Decision_Maker.o
	g++ -o $@ $^ $(CFLAGS) $(MACROS)

Arena.o: Arena.cpp Arena.h Tank.h Map.h Info.h Decision_Maker.h
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

Tank.o: Tank.cpp Tank.h Map.h Info.h Decision_Maker.h
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

TankWars.o: TankWars.cpp Arena.h Tank.h
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

Decision_Maker.o: Decision_Maker.cpp Info.h Map.h Misc_Classes.h
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

Map.o: Map.cpp Map.h Misc_Classes.h
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

Misc_Classes.o: Misc_Classes.cpp Misc_Classes.h
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

Info.o: Info.cpp Info.h Misc_Classes.h Map.h
	g++ -o $@ -c $< $(CFLAGS) $(MACROS)

log_to_html.exe: log_to_html.cpp
	g++ -o $@ $< $(CFLAGS) $(MACROS)

play: all
	./TankWars.exe
	./log_to_html.exe

display:
	firefox tank_video_player.html

clean:
	rm *.o *~ -f

run_and_display : 
	make
	./TankWars.exe > Tank-log-file
	python log-file-reader.py

zip-file:
	tar zcvf TankWars.tar.gz *
