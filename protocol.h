#include <stdlib.h>
#include <string.h>

#include "array_t.h"

struct Base4Protocol
{
    char _0[1];
    char _1[1];
    char _2[1];
    char _3[1];
};

Base4Protocol
getProtocol(char* path) {
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

array_t*
constructBaseNProtocol(Base4Protocol protocol, unsigned const int n) 
{
   
    array_t *baseNProtocol = array_string_new(4^n, n);

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
        array_string_set(baseNProtocol, i, seq);
   }
   return baseNProtocol;
}


char* 
getProtocolSummary(array_t *protocol) {
    char* summary = "Buffer pairing protocol:\n";
    int protocol_len = array_string_len(protocol);
    for (int i = 0;i < protocol_len; i++) 
    {
        char* number = (char*) i;
        strcat(summary, number);
        strcat(summary, " --> ");
        char* seq = array_string_get(protocol, i);
        strcat(summary, seq);
        strcat(summary, "\n");
    }
    return summary; 
}