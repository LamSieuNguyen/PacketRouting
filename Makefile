OPTS = -Wall -g -std=c++11 -pthread

all: parallelDijkstra matrixDijkstra listDijkstras bellmanFord

parallelDijsktra: parallelDijkstra.cc shortestPath.o BinaryHeap.o readGraph.o
	g++ ${OPTS} -o parallelDijkstra parallelDijkstra.cc shortestPath.o BinaryHeap.o readGraph.o
matrixDijkstra: matrixDijkstra.cc shortestPath.o BinaryHeap.o readGraph.o
	g++ ${OPTS} -o matrixDijkstra matrixDijkstra.cc shortestPath.o BinaryHeap.o readGraph.o

listDijkstra: listDijkstra.cc shortestPath.o BinaryHeap.o readGraph.o
	g++ ${OPTS} -o listDijkstra matrixDijkstra.cc shortestPath.o BinaryHeap.o readGraph.o

bellmanFord.cc: bellmanFord.cc shortestPath.o BinaryHeap.o readGraph.o
	g++ ${OPTS} -o bellmanFord bellmanFord.cc shortestPath.o BinaryHeap.o readGraph.o

readGraph_Test: readGraph_Test.cc shortestPath.o BinaryHeap.o
	g++ ${OPTS} -c readGraph_Test readGraph_Test.cc shortestPath.o BinaryHeap.o

readGraph.o: readGraph.cc readGraph.h
	g++ ${OPTS} -c readGraph.cc

shortestPath.o: shortestPath.cc shortestPath.h BinaryHeap.h
	g++ ${OPTS} -c shortestPath.cc


BinaryHeap.o: BinaryHeap.cc BinaryHeap.h
	g++ ${OPTS} -c BinaryHeap.cc

clean:
	rm *.o parallelDijstra matrixDijsktra listDijsktra bellmanFord 


