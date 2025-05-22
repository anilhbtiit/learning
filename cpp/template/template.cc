#include <stdio.h>
#include <iostream>
#include <ctime>
#include "template.h"
#include "mergeSort.h"

#if 0
namespace N {

template <typename T1, typename T2>
  class add {
    private:
      T1 a;
      T2 b;
      int sum;
    public:
      add() {}; //default
      add(T1 a1, T2 b1) { a = a1; b = b1;} //
      ~add(){}
      T1 getFirst() { return a; }
      T2 getSecond() { return b; }
      T1 getMax() { return (a>b) ? a : b; }
  };

template <typename T1>
  class list {
    private:
      T1 value;
      class list* next;
    public:
      list(T1 val) { value = val; next = NULL; }; //default
      list(list* src) { 
        value = src->getVal() -1;
        next = nullptr;
      }
      ~list(){}
      T1 getVal() { return value; }
      list* getNextNode() { return next; }
      void addNextNode(list* nxt) { next = nxt; }
      void addInTheEnd(list* nxt) { 
        list* curr = this;
        while(curr->getNextNode()) {
          curr = curr->getNextNode();
        }
        curr->addNextNode(nxt);
      }
      list* insertInTheFront(list* nxt) { 
        list* curr = this;
        nxt->addNextNode(curr);
        return nxt;
      }

      void printTheList() {
        list* curr = this;
        while(curr) {
          std::cout << curr->getVal() << "\t";
          curr = curr->getNextNode();
        }
      }
      void sortTheList() {
        list* curr = this;

        //std::sort(curr->begin(), curr->end(), [](const int l1, const int l2) { retun (l1<l2); });
      }
  };
};
#endif

inline unsigned long get_time_in_ms()
{
    return (unsigned long)((double(clock()) / CLOCKS_PER_SEC) * 1000);
}

inline unsigned long get_time_in_micros()
{
    return (unsigned long)((double(clock()) / CLOCKS_PER_SEC) * 1000 *1000);
}


using namespace N;
int main() {
  add<int,int>* obj = new add<int, int>(5,4);
  std::cout << obj->getFirst() << "\n";
  add<int,char>* obj1 = new add<int, char>(5,'d');
  std::cout << obj1->getMax() << "\n";

  delete obj;
  delete obj1;

  int numNodes = 100;
  list<int>* root = nullptr;
  std::time_t start = std::clock();  
  unsigned long startTime = get_time_in_micros();
  for(int i=0; i< numNodes; ++i) {
    int r1 = rand()%100;
    if(!root) {
      root = new list<int>(r1);
    } else {
      list<int>* node1 = new list<int>(r1);
      root->addInTheEnd(node1);
    }
  }
  list<int>* newNode = new list<int>(root);
  root = root->insertInTheFront(newNode);
  //std::cout << "C quick-sort time elapsed: " << static_cast<double>( clock() - start ) / CLOCKS_PER_SEC << "\n";
  mergeSort(&root);
  root->printTheList();
  std::cout << "\nC quick-sort time elapsed: " << (get_time_in_micros() - startTime ) << "\n";
}

