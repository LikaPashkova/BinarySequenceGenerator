#ifndef REGISTER_H
#define REGISTER_H
#include <vector>
#include <QBitArray>
using namespace std;

class Register // имя класса
{
private:
    int n;
    int p;

    QBitArray func;
    int funcop;
public:
    Register(int n, int p);
    ~Register();
    void SetFunc(QBitArray f, int oper);//1-and, 2 - or, 3 - xor; -n - !op
    QBitArray GetFunc();
    QBitArray ShiftRight(QBitArray vector, bool delay);
    int GetCountVectors();
    QString VectToString(QBitArray vect);
    vector<QString> GetSequence(vector <int> func);
    bool CheckFunc(vector<int> func);

};

#endif // REGISTER_H
