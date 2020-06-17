#ifndef FUNCTIONGENERATOR_H
#define FUNCTIONGENERATOR_H
#include <vector>
#include <QBitArray>
#include <register.h>
using namespace std;

class FunctionGenerator // имя класса
{
private:
    int n;
    int p;
    Register reg = Register(0,0);
//    QBitArray func;
//    int funcop;
public:
    FunctionGenerator(Register reg, int n, int p);
    ~FunctionGenerator();
    void SetFunc(QBitArray f, int oper);//1-and, 2 - or, 3 - xor; -n - !op
    QBitArray GetFunc();
    QBitArray IncFunction(QBitArray vect);
    vector<QBitArray> GetAndFuncs();
    vector<QBitArray> GetOrFuncs();
    vector<QBitArray> GetXorFuncs();
    vector<QBitArray> GetNotAndFuncs();
    vector<QBitArray> GetNotOrFuncs();
    vector<QBitArray> GetNotXorFuncs();
    bool IsFunc(int f, bool opAnd, bool opOr, bool opXor, bool opNot);
    vector<vector<int>> GetFuncs(bool opAnd, bool opOr, bool opXor, bool opNot);

};

#endif // FUNCTIONGENERATOR_H
