#include "shortestPath.h"
#include "BinaryHeap.h"

#include <limits>
#include <iostream>
#include <vector>
#include <thread>

#include <chrono>
#include <ctime>

using namespace std;

void dijkstra(const int* const * adj, const double* const * weights, const int* lengths, int numVertices, int source, double*& dist, int*& prev)
{
   dist = new double[numVertices];
   prev = new int[numVertices];
   for(int i = 0; i < numVertices; i++)
   {
      dist[i] = numeric_limits<double>::infinity();
      prev[i] = -1;
   }
   dist[source] = 0;
   BinaryHeap h(dist, numVertices);

   int curNode = h.getMin();
   h.popMin();

   for(int i = 1; i < numVertices; i++)
   {
      for(int j = 0; j < lengths[curNode]; j++)
      {
	 int node = adj[curNode][j];
	 if(h.contains(node) && h.getPriority(curNode) + weights[curNode][j] < h.getPriority(node))
	 {
	    h.decreasePriority(node, h.getPriority(curNode) + weights[curNode][j]);
	    prev[node] = curNode;
	 }
      }

      curNode = h.getMin();
      dist[curNode] = h.getPriority(curNode);
      h.popMin();
   }
}

void dijkstra(const double* const * matrix, int numVertices, int source, double*& dist, int*& prev)
{
   dist = new double[numVertices];
   prev = new int[numVertices];
   bool* inTree = new bool[numVertices];
   for(int i = 0; i < numVertices; i++)
   {
      dist[i] = numeric_limits<double>::infinity();
      prev[i] = -1;
      inTree[i] = false;
   }
   dist[source] = 0;
   inTree[source] = true;
   int curNode = source;

   for(int i = 1; i < numVertices; i++)
   {
      for(int node = 0; node < numVertices; node++)
      {
	 if(!inTree[node] && dist[curNode] + matrix[curNode][node] < dist[node])
	 {
	    dist[node] = dist[curNode] + matrix[curNode][node];
	    prev[node] = curNode;
	 }
      }

      double minWeight = numeric_limits<double>::infinity();
      for(int node = 0; node < numVertices; node++)
      {
	 if(!inTree[node] && dist[node] < minWeight)
	 {
	    curNode = node;
	    minWeight = dist[node];
	 }
      }
      inTree[curNode] = true;
   }
   delete[] inTree;
}

int bellmanFord(const int* const * edges, const double* weights,int numVertices, int numEdges, int source, double*& dist, int*& prev)
{
  for (int x = 0; x < numVertices; x++)
    {
      dist[x] = numeric_limits<double>::infinity();
      prev[x] = -1;  
    }
  int e1;
  int e2;
  dist[source] = 0;
  for (int i = 1; i < numVertices; i++)
  {
    dist[i] = dist[i-1];
    for (int y = 0; y <numEdges; y++)
      {
	e1 = edges[y][0];
	e2 = edges[y][1];
      
	if (dist[e1]+ weights[i] < dist[y])
	  {
	    dist[e2]=dist[e1]+weights[i];
	    prev[e2] = e1;
	  }
      }
  }
  // vspace
  for (int i = 0; i < numVertices; i++)
  {
    dist[i] = numeric_limits<double>::infinity();
    prev[i] = -1;
  }
 
  dist[source] = 0;
  int x;
  int y;
  int acc= 0 ;
  for (int i = 0; i < numVertices; i++)
  {
    for (int h = 0; h <numEdges; y++)
      {
	x = edges[i][0];
	y = edges[i][1];
	if (dist[x]+ weights[i] < dist[y])
	  {
	    dist[y] = dist[x] + weights[i];
	    prev[y] = x;
	    acc ++;
	  }
      }
  }
  if (acc >1)
    {
      return acc;
    }
  
  return -1;

}


void initialize(int start, int end, double* dist, int* prev, bool* inTree, int numThreads)
{
   if(end == start + 1)
   {
      dist[start] = numeric_limits<double>::infinity();
      prev[start] = -1;
      inTree[start] = false;
   }
   else
   {
      if(numThreads == 1)
      {
	 int midway = (start + end)/2;
	 initialize(start, midway, dist, prev, inTree, 1);
	 initialize(midway, end, dist, prev, inTree, 1);
      }
      else
      {
	 int halfNumThreads = numThreads/2;
	 int mid = start + halfNumThreads*((end - start)/numThreads);
	 
	 thread leftThread(initialize, start, mid, dist, prev, inTree, halfNumThreads);
	 
	 initialize(mid, end, dist, prev, inTree, numThreads - halfNumThreads);
	 
	 leftThread.join();
      }	 
   }   
}

void getMinVertex(int start, int end, const double* dist, const bool* inTree, int numThreads, int* minVert)
{
   if(end == start + 1)
   {
      if(!inTree[start])
      {
	 *minVert = start;
      }
      else
      {
	 *minVert = -1;
      }
   }
   else
   {
      int leftVert;
      int rightVert;
      if(numThreads == 1)
      {
	 int midway = (start + end)/2;	 
	 getMinVertex(start, midway, dist, inTree, 1, &leftVert);
	 getMinVertex(midway, end, dist, inTree, 1, &rightVert);
      }
      else
      {
	 int halfNumThreads = numThreads/2;
	 int mid = start + halfNumThreads*((end - start)/numThreads);
	 
	 thread leftThread(getMinVertex, start, mid, dist, inTree, halfNumThreads, &leftVert);
	 
	 getMinVertex(mid, end, dist, inTree, numThreads - halfNumThreads, &rightVert);
	 
	 leftThread.join();
      }	 

      *minVert = leftVert;
      if(leftVert == -1)
      {
	 *minVert = rightVert;
      }
      else if(rightVert != -1 && dist[rightVert] < dist[leftVert])
      {
	 *minVert = rightVert;
      }
   }   
}

void updateDistances(int start, int end, const double* const * adjMatrix, int vert, double* dist, int* prev, const bool* inTree, int numThreads)
{
   if(end == start + 1)
   {
      if(!inTree[start] && dist[start] > dist[vert] + adjMatrix[vert][start])
      {
	 dist[start] = dist[vert] + adjMatrix[vert][start];
	 prev[start] = vert;
      }
   }
   else
   {
      if(numThreads == 1)
      {
	 int midway = (start + end)/2;
	 updateDistances(start, midway, adjMatrix, vert, dist, prev, inTree, 1);
	 updateDistances(midway, end, adjMatrix, vert, dist, prev, inTree, 1);
      }
      else
      {
	 int halfNumThreads = numThreads/2;
	 int mid = start + halfNumThreads*((end - start)/numThreads);
	 
	 thread leftThread(updateDistances, start, mid, adjMatrix, vert, dist, prev, inTree, halfNumThreads);
	 
	 updateDistances(mid, end, adjMatrix, vert, dist, prev, inTree, numThreads - halfNumThreads);
	 
	 leftThread.join();
      }	 
   }   
}

void dijkstra(const double* const * adjMatrix, int numVertices, int source, double*& dist, int*& prev, int numThreads)
{
   dist = new double[numVertices];
   prev = new int[numVertices];
   bool* inTree = new bool[numVertices];
   initialize(0, numVertices, dist, prev, inTree, numThreads);
   dist[source] = 0;
   for(int i = 1; i < numVertices; i++)
   {
      int vert = -1;
      getMinVertex(0, numVertices, dist, inTree, numThreads, &vert);
      inTree[vert] = true;
      updateDistances(0, numVertices, adjMatrix, vert, dist, prev, inTree, numThreads);
   }
   delete[] inTree;
}

int getPath(int source, int dest, const int* prev, int*& path)
{
   vector<int> reversePath;
   int v = dest;
   while(v != source && v != -1)
   {
      reversePath.push_back(v);
      v = prev[v];
   }

   if(v == -1)
     {
       //printf("No Path Exists\n");
     }
  

   path = new int[reversePath.size()+1];
   path[0] = source;
   for(unsigned i = 1; i <= reversePath.size(); i++)
   {
      path[i] = reversePath[reversePath.size() - i];
   }

   return reversePath.size()+1;
}
int getCycle(int vertex, const int* prev, int numVertices, int*& cycle)
{
  cycle = new int[numVertices]; 
  int dest;
  bool* isPath = new bool[numVertices];
  
  for (int x = 0; x <numVertices; x++)
    {
      isPath[x] = false;
    }
  int cur = 0;
  while (isPath[cur]==false)
    {
      dest = prev[dest];
      cycle[cur] = dest;
      isPath[cur]= true;
      cur ++;
    }
  
  return cur;

  
}
