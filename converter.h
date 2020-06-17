#ifndef CONVERTER_H
#define CONVERTER_H
#include <vector>
#include <QBitArray>
#include <register.h>
using namespace std;

class Converter
{
private:
    int n;
    int p;
public:
    Converter(int n, int p);
    ~Converter();
    QString FunctionAndToString(QBitArray vect);
    QString FunctionNotAndToString(QBitArray vect);
    QString FunctionOrToString(QBitArray vect);
    QString FunctionNotOrToString(QBitArray vect);
    QString FunctionXorToString(QBitArray vect);
    QString FunctionNotXorToString(QBitArray vect);
    QString FuncToString(vector<int> f);
};

#endif // CONVERTER_H
