#include "shortestPath.h"
#include "readGraph.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <sys/time.h>

using namespace std;

int main(int argc, char** argv)
{
   ifstream fin(argv[1]);
   ofstream fout(argv[2]);
   string source(argv[3]);
   string dest(argv[4]);

   
   double** matrix;
   string* vLabels;
   string** eLabels;
   int numV = readGraph(fin, matrix, vLabels, eLabels);

   int sourceIndex = -1;
   int destIndex = -1;
   for(int i = 0; i < numV; i++)
   {
      if(vLabels[i] == source)
      {
	 sourceIndex = i;
      }
      if(vLabels[i] == dest)
      {
	 destIndex = i;
      }
   }

   if(sourceIndex < 0 || destIndex < 0)
   {
      cout << "Vertex not found!" << endl;
      exit(1);
   }

   double* dist;
   int* prev;
   double ** weights;
   int* lengths;
   auto start = chrono::system_clock::now();
   auto startCPU = clock();
   bellmanFord(matrix,weights,lengths, numV, sourceIndex, dist, prev);
   auto end = chrono::system_clock::now();
   auto endCPU = clock();
   auto dur = end - start;
   auto durCPU = (endCPU - startCPU);
   auto durMS = chrono::duration_cast<chrono::microseconds>(dur);
   
   
   int* path;
   int pathLength = getPath(sourceIndex, destIndex, prev, path);

   fout << numV << " " << pathLength-1 << endl;
   for(int i = 0; i < numV; i++)
   {
      fout << vLabels[i] << endl;
   }
   
   double totalWeight = 0;
   for(int i = 0; i < pathLength-1; i++)
   {
      int s = path[i];
      int d = path[i+1];
      totalWeight += matrix[s][d];
      fout << s << " " << d << " " << matrix[s][d] << " " << eLabels[s][d] << endl;
   }
   
   cout << "Total weight: " << totalWeight << endl;
   cout << "CPU time: " << durCPU*1000000/CLOCKS_PER_SEC << " microseconds" << endl;
   cout << "Wall clock time: " << durMS.count() << " microseconds" << endl;

   for(int i = 0; i < numV; i++)
   {
      delete[] matrix[i];
      delete[] eLabels[i];
   }
   delete[] matrix;
   delete[] eLabels;
   delete[] vLabels;

   delete[] dist;
   delete[] prev;

   //delete[] path;
}
