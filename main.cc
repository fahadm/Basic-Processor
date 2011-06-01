#include "Headers.h"
extern Memory Mem;
extern Registers Reg;

int main (int argc,char * argv[])
{
  DecodeExec CPU;
  Fetch Fet;
  if ( argc>1)
   {

    if (Fet.Open(argv[1])==false)
      {
        std::cerr<<"\nERROR :: File not loaded/not present";
        return 1;
      }
   }
  else
  {
      if (Fet.Open("test.txt")==false)
      {
          std::cerr<<"\nERROR :: File not loaded/not present";
        return 1;

      }

  }
    if (Fet.loadupmemory()==false)
    return 2;
  while (1)
    {

      CPU.QueryIR();
      CPU.ResolveOPC();
      if ( Reg.S == 1)
        break;
    }
  //system("pause");
  std::cout<<"\nPress Enter to Continue. . ."<<std::endl;
  cin.get();
  return 0;
}

