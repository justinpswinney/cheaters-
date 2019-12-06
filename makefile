final: cheaters.o
	g++ -oplagiarismCatcher cheaters.o
driver: cheaters.cpp cheaters.h
	g++ -c cheaters.cpp
cheaters.o: cheaters.cpp cheaters.h
	g++ -c cheaters.cpp
