# CFLAGS = -D N=50
CFLAGS = -Wall -pedantic -g -DMAP_SIZE=51  # -DMOVE_DEBUG=5   COUT_DEBUG=TRUE

TankWars.exe: Arena.o Tank.o TankWars.o Map.o Misc_Classes.o
	g++ -o $@ $^ $(CFLAGS)

Arena.o: Arena.cpp Arena.h Tank.h Map.h
	g++ -o $@ -c $< $(CFLAGS)

Tank.o: Tank.cpp Tank.h Map.h
	g++ -o $@ -c $< $(CFLAGS)

TankWars.o: TankWars.cpp Arena.h Tank.h
	g++ -o $@ -c $< $(CFLAGS)

Map.o: Map.cpp Map.h Misc_Classes.h
	g++ -o $@ -c $< $(CFLAGS)

Misc_Classes.o: Misc_Classes.cpp Misc_Classes.h
	g++ -o $@ -c $< $(CFLAGS)

clean:
	rm TankWars.exe *.o *~ -f

run_and_display : 
	make
	./TankWars.exe > Tank-log-file
	python log-file-reader.py

zip-file:
	tar zcvf TankWars.tar.gz *
