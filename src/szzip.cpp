//============================================================================
// Name        : TP_HuffmanCPP_dist.cpp
// Authors     : Tomas De Pietro  (Depi)
//               Melisa Gomez
//               Nicole Tobal
//               Leandro Dragani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "tad/ICode.cpp"
#include "tad/IFileCode.cpp"
#include "tad/IFileCompressed.cpp"
#include "tad/IList.cpp"
#include "tad/ITable.cpp"
#include "tad/ITree.cpp"
#include "tad/Node.h"
#include "util/UFile.cpp"
#include "util/UTree.cpp"

#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void unzip(string filename)
{
   // abro el archivo de codigos
   IFileCode* codeFile = new IFileCode();
   codeFile->setFilename(filename+".szcod");

   // leo el archivo y genero la lista
   ITree* tree = codeFile->load();

   // abro el archivo comprimido
   IFileCompressed* compressFile = new IFileCompressed();
   compressFile->setFilename(filename + ".szdat");

   // abro el archivo
   IFileInput* fi = new IFileInput();
   fi->setFilename(filename);

   // recupera el archivo original
   compressFile->restore(fi,tree);

   // libero la memoria
   //delete fi;
   delete tree;
   delete codeFile;
   delete compressFile;

   cout << "Archivo recuperado con exito." << endl;
}

void zip(string filename)
{
   // abro el archivo
   IFileInput* fi = new IFileInput();
   fi->setFilename(filename);

   // obtengo la tabla de ocurrencias
   ITable* table = fi->createTable();

    /*for(int i=0; i<256; i++){

        if(table->getCount(i) !=0){

            cout << (char)i << "   " << table->getCount(i)<< endl;

        }

    }*/


   // obtengo la lista enlazada
   IList* lista = table->createSortedList();

   // convierto la lista en arbol
   ITree* tree = lista->toTree();

   // asigno los codigos en la tabla
   table->loadHuffmanCodes(tree);

   // abro el archivo de codigo
   IFileCode* codeFile = new IFileCode();
   codeFile->setFilename(filename + ".szcod");

   // grabo el archivo tomando los codigos del arbol
   codeFile->save(table);

   // abro el archivo comprimido
   IFileCompressed* compressFile = new IFileCompressed();
   compressFile->setFilename(filename+".szdat");

   // grabo el archivo comprimido
   compressFile->save(fi,table);


   // libero la memoria
   delete fi;
   delete table;
   delete lista;
   delete tree;
   delete codeFile;
  delete compressFile;

    cout << "Archivo Comprimido" << endl;
}

int main(int argc, char **argv)
{
   if(argc<3)
   {
      cout << "Usage: "<< argv[0]<<" zip/unzip filename"<<endl;
      return 0;
   }

   if( strcmp(argv[1],"zip")==0 )
   {
      zip(argv[2]);
   }
   else
   {
      unzip(argv[2]);
   }

   return 0;

}
