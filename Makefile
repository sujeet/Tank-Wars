# CFLAGS = -D N=50
CFLAGS = -Wall -pedantic -g -DNUMBER=51  # -DMOVE_DEBUG=5   COUT_DEBUG=TRUE

TankWars.exe: Arena.o Tank.o TankWars.o
	g++ -o $@ Arena.o Tank.o TankWars.o $(CFLAGS)

Arena.o: Arena.cpp Arena.h Tank.h
	g++ -o $@ -c $< $(CFLAGS)

Tank.o: Tank.cpp Tank.h
	g++ -o $@ -c $< $(CFLAGS)

TankWars.o: TankWars.cpp Arena.h Tank.h
	g++ -o $@ -c $< $(CFLAGS)

clean:
	rm TankWars.exe *.o *~ -f

run_and_display : 
	make
	./TankWars.exe > Tank-log-file
	python log-file-reader.py

zip-file:
	tar zcvf TankWars.tar.gz *
