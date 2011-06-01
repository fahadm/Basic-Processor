#include "Registers.h"

extern Registers Reg;
extern  Memory Mem;

Memory::Memory():read(false),write(false),mem(false)
{
  mem = new unsigned short int [4096];
}
bool Memory::putdata(short int X)
{
  write  =false;
  mem[Reg.Ar.Data] = X;
  return true;
}
short int Memory::GetData()
{
  read = false;
  return mem[Reg.Ar.Data];
}
Memory::~Memory()
{
  delete [] mem;
}
void  mandatafrom(int R,short int &DataonBus)
{
  switch(R)
    {
    case AR:
      if (Reg.Ar.ld==true)
        {
          Reg.Ar.Data=DataonBus;
          Reg.Ar.ld=false;
        }
      else
        DataonBus = Reg.Ar.Data;

      break;
    case PC:
      if (Reg.Pc.ld==true)
        {
          Reg.Pc.Data=DataonBus;
          Reg.Pc.ld=false;
        }
      else
        DataonBus = Reg.Pc.Data;
      break;
      case AC:
      if (Reg.Ac.ld==true)
        {
          Reg.Ac.Data=DataonBus;
          Reg.Ac.ld=false;
        }
      else
        DataonBus = Reg.Ac.Data;
      break;
    case IR:
      if (Reg.Ir.ld==true)
        {
          Reg.Ir.Data=DataonBus;
          Reg.Ir.ld=false;
        }
      else
        DataonBus = Reg.Ir.Data;
      break;
    case DR:
      if (Reg.Dr.ld==true)
        {
          Reg.Dr.Data=DataonBus;
          Reg.Dr.ld=false;

        }
      else
        DataonBus = Reg.Dr.Data;
      break;
    case TR:
      if (Reg.Tr.ld==true)
        {
          Reg.Tr.Data=DataonBus;
          Reg.Tr.ld=false;
        }
      else
        DataonBus = Reg.Tr.Data;
      break;
    case MEMORY:
      if (Mem.write== true)
        {
          Mem.putdata(DataonBus);

        }
      else if (Mem.read==true)
        {
          DataonBus = Mem.GetData();
        }

      break;
      case OUTR:
      if (Reg.Outr.ld == true)
      {
          Reg.Outr.Data=DataonBus;
          Reg.Outr.ld = false;
      }
    }

}
void ArithematicLogic::ADD()
{
    if ( (Reg.Ac.Data + Reg.Dr.Data ) > 65535)
        Reg.E= 1;
    Reg.Ac.Data = Reg.Ac.Data + Reg.Dr.Data;

}
void ArithematicLogic::AND()
{
    Reg.Ac.Data = Reg.Ac.Data & Reg.Dr.Data;
}
void ArithematicLogic::OR()
{
    Reg.Ac.Data = Reg.Ac.Data | Reg.Dr.Data;
}

void ArithematicLogic::NOT()
{
    Reg.Ac.Data = 0xFFFF - Reg.Ac.Data;
}
void ArithematicLogic::LDA()
{
    Reg.Ac.Data = Reg.Dr.Data;

}
void ArithematicLogic::INP()
{
    Reg.Ac.Data = Reg.Inpr;
    Reg.FGI=0;
}
void ArithematicLogic::SUB()
{
    Reg.Ac.Data = Reg.Ac.Data-Reg.Dr.Data;
}
ArithematicLogic ALU;
