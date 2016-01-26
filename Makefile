main: main.o network.o DataMnist.o functions.o
	g++ -I /usr/include/eigen3 main.o network.o DataMnist.o functions.o -o main

main.o: main.cpp
	g++ -I /usr/include/eigen3 -c main.cpp

network.o: network.cpp
	g++ -I /usr/include/eigen3 -c network.cpp

functions.o: functions.cpp
	g++ -I /usr/include/eigen3 -c functions.cpp

DataMnist.o: DataMnist.cpp
	g++ -I /usr/include/eigen3 -c DataMnist.cpp

clean:
	rm -f main *.o
