#include "Registers.h"
#include "bus.h"
#include "fetch.h"
extern Registers Reg;
extern Memory Mem;
extern DataBus DBus;
extern ArithematicLogic ALU;
extern int SC;
extern bool Halt;
class DecodeExec
{
  unsigned int I:1;
  struct Dec
  {
    unsigned int Data:8;
    Dec():Data(0) {}} Dx;
  unsigned int address:12;
public:
  DecodeExec():I(0),Dx(),address(0)
  {

  }
  void QueryIR()
  {
      I =0;
      Dx.Data=0;
      address=0;

    DBus.RWfromlocation(PC);
    Reg.Ar.ld =true;  //  AR <- PC
    DBus.RWfromlocation(AR);

    Mem.read=true;
    DBus.RWfromlocation(MEMORY);
    Reg.Ir.ld= true;   // IR <- M[AR]
    DBus.RWfromlocation(IR);
    Reg.Pc.inc(); //pc <- pc +1

    address = Reg.Ir.Data&0x0FFF;  //
    Reg.Ar.Data = address; // ar <- ir(11-0)
//    while (SC <2) {}
    I=(Reg.Ir.Data>>15);
    switch((Reg.Ir.Data&0x7000)>>12) // DECODE D0 D7
      {

      case 0:
        Dx.Data |=D0;
        break;
      case 1:
        Dx.Data |=D1;
        break;
      case 2:
        Dx.Data |=D2;
        break;
      case 3:
        Dx.Data |=D3;
        break;
      case 4:
        Dx.Data |=D4;
        break;
      case 5:
        Dx.Data |=D5;
        break;
      case 6:
        Dx.Data |=D6;
        break;
         case 7:
        Dx.Data |=D7;
        break;

      }


  }

  void ResolveOPC()
  {
    //First Determine Type of Opcode
    switch(Dx.Data>>7) // D7 ? 0 :1
      {

      case 1:
        switch(I)
        {
            case 1:
            ExecuteIO();
            break;
            case 0:
             ExecuteRR();
            break;

        }

        break;

      case 0://memory reference
        switch(I)
          {
          case 0:
       /*     while(SC <4)
              {
                //do nothing and wait
              }
        */
            ExecuteMR();

            break;
          case 1:
        /*    while(SC <3)
              {

                //do nothing and wait
              }
              */
            Mem.read=true;
            DBus.RWfromlocation(MEMORY);
            ExecuteMR();        // ar = m[ar]
            Reg.Ar.ld=true;
            DBus.RWfromlocation(AR);
            ExecuteMR();
            break;

          }

        break;

      }


  }
  void ExecuteMR()
  {
      switch(Dx.Data)
      {             // SEE RTL TABLE FOR Mem REF
          case D0:
            Mem.read=true;
            DBus.RWfromlocation(MEMORY);
            Reg.Dr.ld =true;
            DBus.RWfromlocation(DR);
            ALU.AND();



          break;
          case D1:
            Mem.read=true;
            DBus.RWfromlocation(MEMORY);
            Reg.Dr.ld =true;
            DBus.RWfromlocation(DR);
            ALU.ADD();


          break;
          case D2:

            Mem.read=true;
            DBus.RWfromlocation(MEMORY);
            Reg.Dr.ld =true;
            DBus.RWfromlocation(DR);
            ALU.LDA();
          break;
          case D3:
            DBus.RWfromlocation(AC);
            Mem.write=true;
            DBus.RWfromlocation(MEMORY);
          break;
          case D4:
            DBus.RWfromlocation(AR);
            Reg.Pc.ld= true;
            DBus.RWfromlocation(PC);
          break;
          case D5:
            DBus.RWfromlocation(PC);
            Mem.write=true;
            DBus.RWfromlocation(MEMORY);
            DBus.RWfromlocation(AR);
            Reg.Pc.ld = true;
            Reg.Pc.inc();
          break;
          case D6:
            Mem.read = true;
            DBus.RWfromlocation(MEMORY);
            Reg.Dr.ld =true;
            DBus.RWfromlocation(DR);
            Reg.Dr.inc();
            if (Reg.Dr.Data == 0 )
            {
                Reg.Pc.inc();
            }
            Mem.write= true;
            DBus.RWfromlocation(MEMORY);

          break;



      }

  }

  void ExecuteRR()
  {
      switch(address)
      {// SEE RTL TABLE FOR REG REF
          case B11:
          Reg.Ac.clr();
          break;
          case B10:
            Reg.E =0;
          break;
          case B9:
          #ifdef DEBUG
          cout<<"Debug :: AC"<<Reg.Ac.Data<<endl;
          #endif
          ALU.NOT();
          #ifdef DEBUG
          cout<<"Debug :: AC"<<Reg.Ac.Data<<endl;
          #endif
          break;

          case B8:
          Reg.E =!Reg.E;
          break;
          case B7:
          DBus.RWfromlocation(AC);
          Reg.Tr.ld=true;
          DBus.RWfromlocation(TR);
          Reg.Ac.Data = Reg.Ac.Data>>1;
          Reg.Ac.Data |= Reg.E ==0 ? 0x0:0x8000;

          Reg.E= (Reg.Tr.Data)<<15;

          break;
          case B6:
          DBus.RWfromlocation(AC);
          Reg.Tr.ld=true;
          DBus.RWfromlocation(TR);
          Reg.Ac.Data = Reg.Ac.Data<<1;
          Reg.Ac.Data |= Reg.E ==0 ? 0x0:0x1;

          Reg.E= (Reg.Tr.Data)>>15;
          break;
          case B5:
          if (Reg.Ac.Data == 65535)
          {
              Reg.E=1- Reg.E;
              //cout<<"FF E toggled";
          }
            Reg.Ac.inc();
          break;
          case B4:
          if ((Reg.Ac.Data>>15)==0)
          Reg.Pc.inc();
          break;
          case B3:
          if ((Reg.Ac.Data>>15)==1)
          Reg.Pc.inc();
          break;
          case B2:
          if(Reg.Ac.Data == 0)
          Reg.Pc.inc();
          break;
          case B1:
          if (Reg.E == 0)
          Reg.Pc.inc();
          break;
          case B0:
          Reg.S =1;
          ////err how do i shut it down

          std::cout<<"\nDEBUG :: Termiated";



          break;

      }
  }
  void ExecuteIO()
  {
      switch(address)
      {     // SEE RTL TABLE FOR I/o //Loose Implementation
          case B11:
          if (Reg.IEN ==1 )
          {
            char x;
            //#ifdef INPE
            std::cin.get(x);
            //#endif
            std::cin.get();
            Reg.Inpr = x;
            ALU.INP();
          }
          break;
          case B10:
          if (Reg.IEN ==1 )
          {
            DBus.RWfromlocation(AC);
            Reg.Outr.ld =true;
            DBus.RWfromlocation(OUTR);
            char a= (char)( Reg.Outr.Data);
           // #ifdef INPE
         //  cout<<"Outputting"<<Reg.Ac.Data<<endl;
            std::cout<<a;
            //#endif
            Reg.FGO=0;
          }
          break;
          case B9:
          if ( Reg.FGI == 1)
            Reg.Pc.inc();
          break;
          case B8:
          if ( Reg.FGO == 1)
            Reg.Pc.inc();
          break;
          case B7:
          Reg.IEN = 1;
          break;
          case B6:
          Reg.IEN = 0;
          break;

      }

  }


};

