#define AR 1
#define PC 2
#define DR 3
#define AC 4
#define IR 5
#define TR 6
#define MEMORY 7
#define OUTR 8

class DataBus
{
  struct Mux
  {
    unsigned int lines:4;
  } Lines;
  short int DataonBus;
public:

  void RWfromlocation(int l);
};
void mandatafrom(int R,short int &DataonBus);
