
#include "IList.cpp"
#include "ICode.cpp"
#include "ITree.cpp"

#ifndef xITable
#define xITable

#define cantBytes 256

struct tabla{

    int c; //caracter
    long n; //ocurrencias
    ICode cod;
    int nCod; //longitud del ICode

};


struct ITable
{

	tabla Tabla[256];

	ITable(){

		for(int i=0; i<256; i++){
		    Tabla[i].c = i;
		    Tabla[i].n = 0;
		    Tabla[i].nCod = 0; //no inicializo cod porque lo hace el constructor de ICode
		}

	}


   void addCount(int c)
   {
	   Tabla[c].n++;
   }

   long getCount(int c)
   {
      return Tabla[c].n;
   }

   IList* createSortedList()
   {
	   IList* lista = new IList();
	   Node* aux = new Node();

	   for(int i=0; i<256; i++){

		   if(Tabla[i].n != 0)
		   {
			   aux->c = i;	//cargo datos en el nodo
			   aux->n = getCount(i);
			   lista->insertNode(aux);   //inserto nodo
		   }

	   }

      return lista;
   }

   void loadHuffmanCodes(ITree* root)
   {
        ICode icode;
	    UTree* utree = new UTree(root->root);
	    string cod="";

	    Node* hoja = utree->next(cod); //me guarda en cod el codigo de hoffman
	    while( hoja!=NULL )
	    {
	        icode.code = cod;
            Tabla[hoja->c].cod = icode;

            hoja = utree->next(cod);
	    }
   }

   ICode* getCode(int c)
   {
       ICode* aux = new ICode();

       aux->code = Tabla[c].cod.code;

      return aux;
   }
};

#endif
