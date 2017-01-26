
#include "Node.h"
#include "ITree.cpp"

#ifndef xIList
#define xIList

struct IList
{
	Node* primero;

	IList(){
		primero = NULL;
	}

   Node* removeFirstNode()
   {

       Node* aux = primero;

       primero = primero->sig;

       return aux;

   }

   bool condicion(Node* nuevo, Node* aux){

	   if(nuevo->n < aux->n)
       {
           return false;
	   }
	   if(nuevo->n == aux->n)
	   {
           (nuevo->c < aux->c)?0:1;
	   }

	   return true;

   }

   void insertNode(Node* nuevoNodo) //antes se llamaba n
   {
        Node* n = new Node();
        n->c = nuevoNodo->c;
        n->n = nuevoNodo->n;
        n->der = nuevoNodo->der;
        n->izq = nuevoNodo->izq;

        Node* ant = NULL;

        Node* aux = primero;

        while( aux!=NULL && condicion(n, aux) )
        {
            ant = aux;
            aux = aux->sig;
        }

        if( ant==NULL )
        {
            primero = n;
        }
        else
        {
            ant->sig = n;
        }

        n->sig = aux;

   }

   ITree* toTree()
   {
	   ITree* arbol = new ITree();
	   Node* n1 = new Node();
	   Node* n2 = new Node();
	   Node* aux = new Node();

	   while(primero->sig != NULL){

		   n1 = removeFirstNode();
		   n2 = removeFirstNode();
		   aux->c = 300; //fruta
		   aux->n = n1->n + n2->n ;
		   aux->der = n1;
		   aux->izq = n2;
		   insertNode(aux);

	   }

	   arbol->setRoot(primero);

     return arbol;
   }
};

#endif
