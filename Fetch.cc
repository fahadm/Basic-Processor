#include "Fetch.h"
#include "Registers.h"

#define FON 1
extern Memory Mem;

#ifdef FON
Fetch::Fetch()
{

}
bool Fetch::Open(std::string name )
{
  Fin.open(name.c_str(),std::ios::in);
  if (!Fin)
    {
      return false;
    }
  std::cout<<"DEBUG :: File Opened Successfully";
  return true;
}
bool Fetch::loadupmemory()
{
  //start loading from 100
  char * file;
  Fin.seekg(0,std::ios::end);
  int size =0;
  size = Fin.tellg();
  Fin.seekg(0,std::ios::beg);
  file = new char[size +1];
  Fin.getline(file,size+1,EOF);

  //parse file and kill comments

  for ( int i =0 ; i <size +1 ; i ++)
  {
      if ( file[i]== '/')
      {
          while ( file [i] != '\n')
          {
           file[i] = ' '; //white space the worse kind of space there is :P
           i++;
          }
      }

  }
  std::istringstream iss(file);

  std::string Segname;
  int TotalVariables;
  iss>>Segname;
  if ( Segname == "DATA")
    {
      iss>>TotalVariables;
      for ( int i =0 ; i <TotalVariables ; i++)
        {
          short int x=0;
          iss>>x;
          iss>>Mem.mem[x];
          std::cout<<"\nDEBUG :: Stored  "<<Mem.mem[x]<<" to @0x"<<std::hex<<x<<std::endl;
        }
    }
    iss>>Segname;
   if (Segname == "MAIN")
    {
      int i=0;
      for( i =100 ; Mem.mem[i-1] != 0x7001  ; i ++)
        {
          iss>>std::hex>>Mem.mem[i];
          if ( i >4096)
          {
              std::cerr<<"ERROR :: Program Not ended with 0x7001";
              return false;
          }

        }
    }
  std::cout<<"\nDEBUG :: Successfully Loaded"<<std::endl;
  delete [] file;
  return true;

}
#endif
