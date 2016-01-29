main: main.o network.o DataMnist.o functions.o layer.o
	g++ -g -I /usr/include/eigen3 main.o network.o DataMnist.o functions.o layer.o -o main -lm

main.o: main.cpp
	g++ -g -I /usr/include/eigen3 -c main.cpp

network.o: network.cpp
	g++ -g -I /usr/include/eigen3 -c network.cpp

layer.o: layer.cpp
	g++ -g -std=c++11 -I /usr/include/eigen3 -c layer.cpp

functions.o: functions.cpp
	g++ -g -I /usr/include/eigen3 -c functions.cpp -lm

DataMnist.o: DataMnist.cpp
	g++ -g -I /usr/include/eigen3 -c DataMnist.cpp

clean:
	rm -f main *.o
