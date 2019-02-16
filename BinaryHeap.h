

#ifndef BINARY_HEAP
#define BINARY_HEAP

class BinaryHeap
{

  protected:
   int* heap;
   int* pos;
   int num;
   double* priorities;
   void makeheap(int pos);
   void swap(int p1, int p2);

  public:
   BinaryHeap(const double* priorities, int numItems);
   virtual ~BinaryHeap();

   virtual int getMin() const;
   virtual void popMin();

   virtual bool contains(int item) const;

   virtual double getPriority(int item) const;
   virtual void decreasePriority(int item, double newPriority);

};

#endif
