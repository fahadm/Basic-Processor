#include <fstream>
#include <sstream>
#include <iostream>

#define FON 1
#define INPE 1
class Fetch
{
    #ifdef FON
    std::fstream Fin;
    #endif
    public:
    bool Open(std::string);
    bool loadupmemory();

    Fetch();
    //~Fetch();
};

