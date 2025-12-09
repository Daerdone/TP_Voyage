CXXFLAGS = -ansi -pedantic -Wall -std=c++11

.PHONY: clean MAP

main: clean main.o Trajet.o TrajetSimple.o TrajetCompose.o ListeDeTrajet.o
	g++ -o trajets main.o Trajet.o TrajetSimple.o TrajetCompose.o ListeDeTrajet.o

MAP: CXXFLAGS += -DMAP
MAP: clean main

main.o: main.cpp ListeDeTrajet.h
	g++ -c main.cpp -o main.o $(CXXFLAGS)

Trajet.o: Trajet.cpp Trajet.h
	g++ -c Trajet.cpp -o Trajet.o $(CXXFLAGS)

TrajetSimple.o: TrajetSimple.cpp TrajetSimple.h Trajet.h ListeDeTrajet.h
	g++ -c TrajetSimple.cpp -o TrajetSimple.o $(CXXFLAGS)

TrajetCompose.o: TrajetCompose.cpp TrajetCompose.h Trajet.h ListeDeTrajet.h
	g++ -c TrajetCompose.cpp -o TrajetCompose.o $(CXXFLAGS)

ListeDeTrajet.o: ListeDeTrajet.cpp ListeDeTrajet.h Trajet.h
	g++ -c ListeDeTrajet.cpp -o ListeDeTrajet.o $(CXXFLAGS)

clean:
	rm -f *.o trajets