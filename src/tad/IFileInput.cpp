
#include "ITable.cpp"
#include <iostream>
#include <stdio.h>
using namespace std;

#ifndef xIFileInput
#define xIFileInput

struct IFileInput
{

    FILE* arch;
    string file;

   ITable* createTable()
   {
       long len = getLength();

	   ITable* tabla = new ITable();
	   arch = fopen(file.c_str(), "r+b");
	   unsigned char c;

	   for(int i=0; i<len; i++){

		   fread(&c, sizeof(char), 1, arch);
		   tabla->addCount(c);

	   }

	   fclose(arch);

      return tabla;
   }

   void setFilename(string filename)
   {
        file = filename;
   }

   string getFilename()
   {
      return file;
   }

   long getLength()
   {
       arch = fopen(file.c_str(), "r+b");

       long curr = ftell(arch);
       fseek(arch, 0, SEEK_END);
       long len = ftell(arch);
       fseek(arch, curr, SEEK_SET);

       fclose(arch);

      return len;
   }

};

#endif
