#include "bus.h"
DataBus DBus;
//mandatafrom Manipulate Data from mandatafrom(DWord REGISTER,Word &DATAONBUS)
void DataBus::RWfromlocation(int l)
{
  Lines.lines=l;//lame
  switch(Lines.lines)
    {
    case 1:

      mandatafrom(AR,DataonBus);
      break;
    case 2:
      mandatafrom(PC,DataonBus);

      break;
    case 3:
      mandatafrom(DR,DataonBus);

      break;
    case 4:
      mandatafrom(AC,DataonBus);

      break;
    case 5:
      mandatafrom(IR,DataonBus);

      break;
    case 6:
      mandatafrom(TR,DataonBus);

      break;
    case 7:
      mandatafrom(MEMORY,DataonBus);

      break;
    case 8:
    mandatafrom(OUTR,DataonBus);


    }
}

