#include <stdlib.h>
#include <string.h>

struct Base4Protocol
{
    char _0[1];
    char _1[1];
    char _2[1];
    char _3[1];
};

Base4Protocol getProtocol(char* path) {
   if (1) {
        // default protocol

       struct Base4Protocol protocol;

       strcpy(protocol._0, "A");
       strcpy(protocol._1, "T");
       strcpy(protocol._2, "C");
       strcpy(protocol._3, "G");

       return protocol;

   } else {

    // This can become a thing later

   }
}

char ** constructBaseNProtocol(Base4Protocol protocol, unsigned const int n) 
{
   char** arrProtocol = malloc( (4^n) * sizeof(char[n]) );
   for (int i=0;i<4^n;i++) 
   {
        char seq[n];
        for (int j=0;j<n;j++) 
        {
            int bp = ((4^(i+1)) * j) % 4;
            if (bp == 0) 
            {
                strcat(seq,protocol._0);
            }
            else if (bp ==1)
            {
                strcat(seq,protocol._1);
            }
            else if (bp == 2)
            {
                strcat(seq,protocol._2);
            }
            else
            {
                strcat(seq,protocol._3);
            }
        }
        strcpy(arrProtocol[i], seq);
   }
   return arrProtocol;
}