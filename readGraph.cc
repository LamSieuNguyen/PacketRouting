

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int readGraph(ifstream& fin, double**& matrix, string*& vLabels, string**& eLabels)
{
   int numVertices;
   fin >> numVertices;
   int numEdges;
   fin >> numEdges;
   
   vLabels = new string[numVertices];
   for(int i = 0; i < numVertices; i++)
   {
      fin >> vLabels[i];
   }
   
   matrix = new double*[numVertices];
   eLabels = new string*[numVertices];
   for(int i = 0; i < numVertices; i++)
   {
      matrix[i] = new double[numVertices];
      eLabels[i] = new string[numVertices];
      for(int j = 0; j < numVertices; j++)
      {
	 matrix[i][j] = numeric_limits<double>::infinity();
      }
   }
   for(int i = 0; i < numVertices; i++)
   {
      matrix[i][i] = 0;
   }

   for(int i = 0; i < numEdges; i++)
   {	 
      int sourceV;
      fin >> sourceV;
      int destV;
      fin >> destV;
      double w;
      fin >> w;
      string l;
      fin >> l;
      
      matrix[sourceV][destV] = w;
      eLabels[sourceV][destV] = l;
   }

   return numVertices;
}

int readGraph(ifstream& fin, int**& adj, double**& weights, int*& lengths, string*& vLabels, string**& eLabels)
{
   int numVertices;
   fin >> numVertices;
   int numEdges;
   fin >> numEdges;
   
   vLabels = new string[numVertices];
   for(int i = 0; i < numVertices; i++)
   {
      fin >> vLabels[i];
   }
   
   adj = new int*[numVertices];
   weights = new double*[numVertices];
   lengths = new int[numVertices];
   eLabels = new string*[numVertices];

   int sourceV;
   fin >> sourceV;
   for(int i = 0; i < numVertices; i++)
   {
      vector<int> tmpAdj;
      vector<double> tmpWeights;
      vector<string> tmpLabels;
   
      lengths[i] = 0;
      while(!fin.eof() && sourceV == i)
      {
	 int destV;
	 fin >> destV;
	 tmpAdj.push_back(destV);
	 double w;
	 fin >> w;
	 tmpWeights.push_back(w);
	 string label;
	 fin >> label;
	 tmpLabels.push_back(label);
	 lengths[i]++;
	 fin >> sourceV;
      }

      adj[i] = new int[lengths[i]];
      weights[i] = new double[lengths[i]];
      eLabels[i] = new string[lengths[i]];
      for(int j = 0; j < lengths[i]; j++)
      {
	 adj[i][j] = tmpAdj[j];
	 weights[i][j] = tmpWeights[j];
	 eLabels[i][j] = tmpLabels[j];
      }
   }

   return numVertices;
}

int readGraph(ifstream& fin, int**& edgeList, double*& weights, int& numEdges, string*& vLabels, string*& eLabels)
{
   int numVertices;
   fin >> numVertices;
   fin >> numEdges;

   vLabels = new string[numVertices];
   for(int i = 0; i < numVertices; i++)
   {
      fin >> vLabels[i];
   }

   edgeList = new int*[numEdges];
   weights = new double[numEdges];
   eLabels = new string[numEdges];

   for(int i = 0; i < numEdges; i++)
   {
      int sourceV;
      fin >> sourceV;
      int destV;
      fin >> destV;
      double w;
      fin >> w;
      string l;
      fin >> l;
      
      edgeList[i] = new int[2];
      edgeList[i][0] = sourceV;
      edgeList[i][1] = destV;
      weights[i] = w;
      eLabels[i] = l;
   }

   return numVertices;
}

