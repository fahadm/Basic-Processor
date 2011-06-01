
#include "General.h"
struct Registers
    {
        struct GenReg12
        {
            unsigned int Data:12;
            bool ld;
             GenReg12();
             void inc();
             void clr();
        };
        GenReg12 Ar,Pc;
         struct GenReg16
        {
           unsigned int Data:16;
            bool ld;
            GenReg16();
            void inc();
            void clr();
        };
        GenReg16 Dr,Ac,Ir,Tr;
        unsigned int Inpr:8;
        struct GenReg8
        {
            unsigned int Data:8;
            bool ld;

        };
        GenReg8 Outr;
        unsigned int E:1,S:1,I:1,R:1,IEN:1,FGI:1,FGO:1;
        unsigned int SC;
        Registers();
    };

