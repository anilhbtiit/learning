#ifndef _HEADER_TEMPLATE_
#define _HEADER_TEMPLATE_

#include <stdio.h>
#include <iostream>

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
      void setNextNode(list* nxt) { next = nxt; } 
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
