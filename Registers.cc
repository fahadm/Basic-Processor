#include "Registers.h"
Registers::Registers():Ar(),Pc(),Dr(),Ac(),Ir(),Tr(),Inpr(0),Outr(),E(0),S(0),I(0),IEN(0),FGI(0),FGO(0),SC(0),R(0)
{
Pc.Data=100;
}
Registers::GenReg16::GenReg16():Data(0),ld(false)
{
}
void Registers::GenReg16::inc()
{
  Data++;
}
void Registers::GenReg16::clr()
{
  Data = 0;
}

Registers::GenReg12::GenReg12():Data(0),ld(false)
{

}
void Registers::GenReg12::inc()
{

  Data++;

}
void Registers::GenReg12::clr()
{
  Data = 0;
}


Registers Reg;
Memory Mem;


/////////////////////////////////////////
////
//Seqeunce Counter Was never implemented.
// It was going to be a waste of time anyway
// You have your own CPU clock for this very reason
