#include "BinaryHeap.h"

using namespace std;

BinaryHeap::BinaryHeap(const double* priorities, int num)
{
   this->num = num;
   heap = new int[num];
   this->priorities = new double[num];
   pos = new int[num];

   for(int i = 0; i < num; i++)
   {
      heap[i] = i;
      pos[i] = i;
      this->priorities[i] = priorities[i];
   }

   for(int i = num/2; i >= 0; i--)
   {
      makeheap(i);
   }
}

BinaryHeap::~BinaryHeap()
{
   delete[] heap;
   delete[] priorities;
   delete[] pos;
}

int BinaryHeap::getMin() const
{
   return heap[0];
}

void BinaryHeap::swap(int p1, int p2)
{
   int tmp = heap[p1];
   heap[p1] = heap[p2];
   heap[p2] = tmp;
   
   pos[heap[p1]] = p1;
   pos[heap[p2]] = p2;
}

void BinaryHeap::makeheap(int pos)
{
   int left = 2*pos + 1;
   int right = 2*pos + 2;
   int small;
   if(right < num and priorities[heap[pos]] > priorities[heap[right]])
   {
      small = right;
   }
   else
   {
      small = pos;
   }

   if(left < num and priorities[heap[small]] > priorities[heap[left]])
   {
      small = left;
   }

   if(small != pos)
   {
      swap(pos, small);      
      makeheap(small);
   }
}

void BinaryHeap::popMin()
{
   pos[heap[0]] = -1;
       
   heap[0] = heap[num - 1];
   pos[heap[0]] = 0;
       
   num--;

   makeheap(0);
}

bool BinaryHeap::contains(int item) const
{
   return pos[item] >= 0;
}

double BinaryHeap::getPriority(int item) const
{
   return priorities[item];
}

void BinaryHeap::decreasePriority(int item, double newPriority)
{
   if(newPriority < priorities[item])
   {
      priorities[item] = newPriority;

      int i = pos[item];
      int parent = (i - 1)/2;
      while(i > 0 && priorities[heap[parent]] > priorities[heap[i]])
      {
	 swap(i, parent);
	 
	 i = parent;
	 parent = (i - 1)/2;
      }   
   }
}
