#define AR 1
#define PC 2
#define DR 3
#define AC 4
#define IR 5
#define TR 6
#define MEMORY 7
#define OUTR 8
#define D0 1
#define D1 2
#define D2 4
#define D3 8
#define D4 16
#define D5 32
#define D6 64
#define D7 128
#define B11  0x800
#define B10 0x400
#define B9 0x200
#define B8 0x100
#define B7 0x80
#define B6 0x40
#define B5 0x20
#define B4 0x10
#define B3 0x8
#define B2 0x4
#define B1 0x2
#define B0 0x1

struct Memory
{
    bool read;
    bool write;
   unsigned short int *mem;
    Memory();
    bool putdata(short int );
    short int GetData();
    ~Memory();
};

struct ArithematicLogic
{

    void AND();
    void OR();
    void NOT();
    void ADD();
    void SUB();
    void LDA();
    void INP();


};


