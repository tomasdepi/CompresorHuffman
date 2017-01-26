#include "ICode.cpp"
#include "Node.h"
#include "../util/UTree.cpp"

#ifndef xITree
#define xITree

struct ITree
{
	Node* root;
	UTree* arbol;

	ITree(){
		root = NULL;
	}

   void setRoot(Node* r)
   {
	   root = r;
   }

   Node* getRoot()
   {
      return root;
   }

   Node* next(ICode* cod)
   {
      string s = cod->code;

        return arbol->next(s);
   }
};

#endif
