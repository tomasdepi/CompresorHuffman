#include <iostream>
#include "ITable.cpp"
#include <stdio.h>
#include "../util/UFile.cpp"
using namespace std;

#ifndef xIFileCode
#define xIFileCode

struct IFileCode
{

    string file;

    IFileCode(){

        file = "";
    }

   void setFilename(string f)
   {
        file = f;
   }

   void save(ITable* table)
   {
        FILE* arCod = fopen(file.c_str(), "w+b");
        UFile* ufile = new UFile (arCod);
        ICode* s = new ICode();

        for(int i=0; i<256; i++)
        {
            if(table->getCount(i) !=0 )
            {

                fwrite(&i, sizeof(char), 1, arCod);
                s = table->getCode(i); //consigo el ICode
                char len = s->getLength();
                fwrite(&len, sizeof(char), 1, arCod);

                for(int t=0; t < len; t++)
                {
                    ufile->writeBit(s->getBitAt(t)); //imprimo el string del ICode bit a bit
                }

                ufile->flush();
            }
        }



        fclose(arCod);
   }

    Node* createNode(){

        Node* node = new Node();
        node->c=0;
        node->n=0;
        node->izq=NULL;
        node->der=NULL;
        node->sig=NULL;

        return node;
    }

   ITree* load()
   {
       FILE* arCod = fopen(file.c_str(), "r+b");
       UFile* ufile = new UFile(arCod);

       int c;
       int bit, len;

       ITree* arbol = new ITree();
       arbol->setRoot(createNode());
       Node* aux = arbol->getRoot();

        while(!feof(arCod))
        {
            aux = arbol->getRoot();

            ufile = new UFile(arCod);

            fread(&c, sizeof(char), 1, arCod);
            fread(&len, sizeof(char), 1, arCod);

            for(int i=0; i<len; i++)
            {
                bit = ufile->readBit();

                if(bit == 1)
                {
                    if(aux->der == NULL){ aux->der = createNode(); }
                    if(i == len-1 ){ aux->der->c = c;}

                    aux = aux->der;
                }

                if(bit == 0)
                {
                    if(aux->izq == NULL){ aux->izq = createNode(); }
                    if(i == len-1 ){ aux->izq->c = c;}

                    aux = aux->izq;
                }


            }


        }

       fclose(arCod);


      return arbol;
   }
};

#endif
