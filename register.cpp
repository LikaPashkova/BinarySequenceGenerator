#include "register.h"
#include <vector>
#include <iostream>
#include <QString>
#include <QVariant>
#include <QBitArray>
#include <QSet>

using namespace std;

Register::Register(int n, int p){
    this->n = n;
    this->p = p;
}

Register::~Register(){

}

void Register::SetFunc(QBitArray f, int oper){
    func = f;
    funcop = oper;
}

QBitArray Register::GetFunc(){
    return func;
}

QBitArray Register::ShiftRight(QBitArray vector, bool delay){
    bool buf = vector[n-1];
    for(int i = n-1;i>0;i--){
        vector[i] = vector[i-1];
    }
    if(delay){
        vector[1] = buf;
    }else{
        vector[0] = buf;
    }
    return vector;
}

int Register::GetCountVectors(){
    int count = 1;
    for(int i = 0; i<p; i++){
        count *= n-i;

    }
    for(int i = 2; i<=p; i++){
        count /= i;

    }
    return count;
}

QString Register::VectToString(QBitArray vect){
    QString str = "";
    for(int i = 0; i<n;i++){
        str += QString::number(vect[i]);
    }
    return str;
}


vector<QString> Register::GetSequence(vector <int> func){
    vector<QString> seq;
    int z = 0;
    bool res = false;
    QBitArray vect(n);
    int count = Register::GetCountVectors();
    QBitArray vectfirst(n);
    for(int i=0;i<n-p;i++){
        vectfirst[i] = 0;
    }
    for(int i=n-p;i<n;i++){
        vectfirst[i] = 1;
    }
    vect = vectfirst;
    int c = 0;
    QSet<QBitArray> set;
    while(c<count && !set.contains(vect)){
        z=0;
        set<<vect;
        seq.push_back(VectToString(vect));
        c++;
        while(z<n&&func[z]==0){
            z++;
        }
        if(z<n){
            switch (func[z]) {
            case 1:
            case 3:
            case 4:
            case 6:
                res = true;
                break;
            case 2:
            case 5:
                res = false;
                break;
            }
            while(z<func.size()){
                int op = func[z];
                switch (op) {
                case 0:
                    break;
                case 1:
                    res&=vect[z];
                    break;
                case 2:
                    res|=vect[z];
                    break;
                case 3:
                    res^=vect[z];
                    break;
                case 4:
                    res&=!vect[z];
                    break;
                case 5:
                    res|=!vect[z];
                    break;
                case 6:
                    res^=!vect[z];
                    break;
                }
                z++;
            }
        }
        vect = Register::ShiftRight(vect, res);

    }
    return seq;


}

bool Register::CheckFunc(vector<int> func){
    //0 - nothing
    //1 - and
    //2 - or
    //3 - xor
    //4 - andnot
    //5 - ornot
    //6 - xornot
    int z = 0;
    bool res = false;
    QBitArray vect(n);
    int count = Register::GetCountVectors();
    QBitArray vectfirst(n);
    for(int i=0;i<n-p;i++){
        vectfirst[i] = 0;
    }
    for(int i=n-p;i<n;i++){
        vectfirst[i] = 1;
    }
    vect = vectfirst;
    int c = 0;
    QSet<QBitArray> set;
    while(c<count && !set.contains(vect)){
        z=0;
        set<<vect;
        c++;
        while(z<n&&func[z]==0){
            z++;
        }
        if(z<n){
            switch (func[z]) {
            case 1:
            case 3:
            case 4:
            case 6:
                res = true;
                break;
            case 2:
            case 5:
                res = false;
                break;
            }
            while(z<func.size()){
                int op = func[z];
                switch (op) {
                case 0:
                    break;
                case 1:
                    res&=vect[z];
                    break;
                case 2:
                    res|=vect[z];
                    break;
                case 3:
                    res^=vect[z];
                    break;
                case 4:
                    res&=!vect[z];
                    break;
                case 5:
                    res|=!vect[z];
                    break;
                case 6:
                    res^=!vect[z];
                    break;
                }
                z++;
            }
        }
        vect = Register::ShiftRight(vect, res);

    }
    if(c==count){
        return true;
    }
    return false;
}
