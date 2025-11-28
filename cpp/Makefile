main : main.o Trajet.o TrajetSimple.o TrajetCompose.o ListeDeTrajet.o
	g++ -o main main.o Trajet.o TrajetSimple.o TrajetCompose.o ListeDeTrajet.o

main.o : main.cpp ListeDeTrajet.h
	g++ main.cpp -c main.o -ansi -pedantic -Wall -std=c++11

Trajet.o : Trajet.cpp Trajet.h
	g++ Trajet.cpp -c Trajet.o -ansi -pedantic -Wall -std=c++11

TrajetSimple.o : TrajetSimple.cpp TrajetSimple.h Trajet.h ListeDeTrajet.h
	g++ TrajetSimple.cpp -c TrajetSimple.o -ansi -pedantic -Wall -std=c++11

TrajetCompose.o : TrajetCompose.cpp TrajetCompose.h Trajet.h ListeDeTrajet.h
	g++ TrajetCompose.cpp -c TrajetCompose.o -ansi -pedantic -Wall -std=c++11

ListeDeTrajet.o : ListeDeTrajet.cpp ListeDeTrajet.h Trajet.h
	g++ ListeDeTrajet.cpp -c ListeDeTrajet.o -ansi -pedantic -Wall -std=c++11