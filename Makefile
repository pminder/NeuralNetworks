main: main.o network.o DataMnist.o functions.o
	g++ main.o network.o DataMnist.o functions.o -o main

main.o: main.cpp
	g++ -c main.cpp

network.o: network.cpp
	g++ -c network.cpp

functions.o: functions.cpp
	g++ -c functions.cpp

DataMnist.o: DataMnist.cpp
	g++ -c DataMnist.cpp