
#include "ITable.cpp"
#include "IFileInput.cpp"
#include "ITable.cpp"
#include "../util/UFile.cpp"
#include <iostream>
#include <stdio.h>

using namespace std;

#ifndef xIFileCompressed
#define xIFileCompressed

struct IFileCompressed
{

    string file;

    IFileCompressed()
    {
        file = "";
    }

   void setFilename(string filename)
   {
        file = filename;
   }

   void save(IFileInput* fi, ITable* table)
   {
       string nomArch = fi->file;
       ICode* aux;
       int byte;

       FILE* arDat;
       FILE* arInput;
       arDat = fopen(file.c_str(), "w+b");
       arInput = fopen(nomArch.c_str(), "r+b");
       UFile* ufile = new UFile(arDat);

       ufile->writeLength(fi->getLength());

       for(int i=0; i<(fi->getLength()); i++)
       {

            fread(&byte, sizeof(char),1, arInput);

            aux = table->getCode(byte); //obtengo el ICode asociado al carecter que lei

            for(int t=0; t< aux->getLength(); t++)
            {
                ufile->writeBit(aux->getBitAt(t)); //imprimo el string del ICode bit a bit
            }

       }
        ufile->flush();

   }

   string getFilename()
   {
      return file;
   }

   void restore(IFileInput* fi, ITree* tree)
   {
        string nomAr = fi->file;
        Node* nodo = tree->getRoot();
        int bit;
        char c;

        FILE* arInput = fopen(nomAr.c_str(), "w+b");
        FILE* arComp = fopen(file.c_str(), "r+b");

        UFile* ufile = new UFile(arComp);

        long len = ufile->readLength();

        for(int i=0; i<len; i++){

            while(nodo->der != NULL){

                bit = ufile->readBit();

                if(bit == 0){
                    nodo = nodo->izq;
                }else{
                    nodo = nodo->der;
                }

            }

            c = nodo->c;

            fwrite(&c, sizeof(char), 1, arInput);

            nodo = tree->getRoot();

        }

        fclose(arInput);
        fclose(arComp);


   }
};

#endif
