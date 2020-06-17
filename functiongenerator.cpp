#include "functiongenerator.h"
#include <vector>
#include <iostream>
#include <QString>
#include <QVariant>
#include <QBitArray>
#include <QSet>

using namespace std;

FunctionGenerator::FunctionGenerator(Register rg, int n, int p){
    this->n = n;
    this->p = p;
    this->reg = rg;
}

FunctionGenerator::~FunctionGenerator(){

}

void FunctionGenerator::SetFunc(QBitArray f, int oper){
    reg.SetFunc(f,oper);
}

QBitArray FunctionGenerator::GetFunc(){
    return reg.GetFunc();
}

QBitArray FunctionGenerator::IncFunction(QBitArray vect){
    int i = 1;
    while(i<=n && vect[n-i]==true){
        i++;
    }
    if(i<=n){
        vect [n-i] = 1;
        i--;
        while(i>0){
            vect[n-i]=false;
            i--;
        }
    }
    return vect;
}

vector<QBitArray> FunctionGenerator::GetAndFuncs(){
//    std::vector<vector<bool>> funcs;
    vector<QBitArray> functions;
    int count = reg.GetCountVectors();
    QBitArray vectfirst(n);
    for(int i=0;i<n-p;i++){
        vectfirst[i] = 0;
    }
    for(int i=n-p;i<n;i++){
        vectfirst[i] = 1;
    }

    QBitArray function(n);
    QBitArray flast(n);
    for(int i=0;i<n;i++){
        function[i] = 0;
        flast[i] = 1;
    }

    QBitArray vect(n);
    while(function!=flast){
        vect = vectfirst;
        int c = 1;
        bool funcvalue = true;
        for(int i = 0; i<n; i++){
            if(function[i]){
                funcvalue &= vect[i];
            }
        }
        vect = reg.ShiftRight(vect, funcvalue);
        QSet<QBitArray> set;
        set <<  vectfirst;
        while(c<count && !set.contains(vect)){
            set<<vect;
            c++;
            //*******************
            //ADD OpNot-CHECK
            //*******************
            funcvalue = true;
            for(int i = 0; i<n; i++){
                if(function[i]==true){
                    funcvalue &=vect[i];
                }
            }
            vect = reg.ShiftRight(vect, funcvalue);
        }
        if(c==count){
            functions.push_back(function);
        }
        function = FunctionGenerator::IncFunction(function);
    }

    return functions;
}

vector<QBitArray> FunctionGenerator::GetOrFuncs(){
    vector<QBitArray> functions;
        int count = reg.GetCountVectors();
        QBitArray vectfirst(n);
        for(int i=0;i<n-p;i++){
            vectfirst[i] = 0;
        }
        for(int i=n-p;i<n;i++){
            vectfirst[i] = 1;
        }

        QBitArray function(n);
        QBitArray flast(n);
        for(int i=0;i<n;i++){
            function[i] = 0;
            flast[i] = 1;
        }

        QBitArray vect(n);
        while(function!=flast){
            vect = vectfirst;
            int c = 1;
            bool funcvalue = false;
            for(int i = 0; i<n; i++){
                if(function[i]){
                    funcvalue |= vect[i];
                }
            }
            vect = reg.ShiftRight(vect, funcvalue);
            QSet<QBitArray> set;
            set <<  vectfirst;
            while(c<count && !set.contains(vect)){
                set<<vect;
                c++;
                //*******************
                //ADD OpNot-CHECK
                //*******************
                funcvalue = false;
                for(int i = 0; i<n; i++){
                    if(function[i] == true){
                        funcvalue |= vect[i];
                    }
                }
                vect = reg.ShiftRight(vect, funcvalue);
            }
            if(c==count){
                functions.push_back(function);
            }
            function = FunctionGenerator::IncFunction(function);
        }
    return functions;
}

vector<QBitArray> FunctionGenerator::GetXorFuncs(){
    vector<QBitArray> functions;
        int count = reg.GetCountVectors();
        QBitArray vectfirst(n);
        for(int i=0;i<n-p;i++){
            vectfirst[i] = 0;
        }
        for(int i=n-p;i<n;i++){
            vectfirst[i] = 1;
        }

        QBitArray function(n);
        QBitArray flast(n);
        for(int i=0;i<n;i++){
            function[i] = 0;
            flast[i] = 1;
        }

        QBitArray vect(n);
        while(function!=flast){
            vect = vectfirst;
            int c = 1;
            bool funcvalue = false;
            for(int i = 0; i<n; i++){
                if(function[i]){
                    funcvalue ^= vect[i];
                }
            }
            vect = reg.ShiftRight(vect, funcvalue);
            QSet<QBitArray> set;
            set <<  vectfirst;
            while(c<count && !set.contains(vect)){
                set<<vect;
                c++;
                //*******************
                //ADD OpNot-CHECK
                //*******************
                funcvalue = false;
                for(int i = 0; i<n; i++){
                    if(function[i] == false){
                        funcvalue ^= vect[i];
                    }
                }
                vect = reg.ShiftRight(vect, funcvalue);
            }
            if(c==count){
                functions.push_back(function);
            }
            function = FunctionGenerator::IncFunction(function);
        }
    return functions;
}

vector<QBitArray> FunctionGenerator::GetNotAndFuncs(){
    std::vector<vector<bool>> funcs;
    vector<QBitArray> functions;
        int count = reg.GetCountVectors();
        QBitArray vectfirst(n);
        for(int i=0;i<n-p;i++){
            vectfirst[i] = 0;
        }
        for(int i=n-p;i<n;i++){
            vectfirst[i] = 1;
        }

        QBitArray function(n);
        QBitArray flast(n);
        for(int i=0;i<n;i++){
            function[i] = 0;
            flast[i] = 1;
        }

        QBitArray vect(n);
        while(function!=flast){
            vect = vectfirst;
            int c = 1;
            bool funcvalue = true;
            for(int i = 0; i<n; i++){
                if(function[i]){
                    funcvalue &= !vect[i];
                }
            }
            vect = reg.ShiftRight(vect, funcvalue);
            QSet<QBitArray> set;
            set <<  vectfirst;
            while(c<count && !set.contains(vect)){
                set<<vect;
                c++;
                //*******************
                //ADD OpNot-CHECK
                //*******************
                funcvalue = true;
                for(int i = 0; i<n; i++){
                    if(function[i]==true){
                        funcvalue &= !vect[i];
                    }
                }
                vect = reg.ShiftRight(vect, funcvalue);
            }
            if(c==count){
                functions.push_back(function);
            }
            function = FunctionGenerator::IncFunction(function);
        }

    return functions;
}

vector<QBitArray> FunctionGenerator::GetNotOrFuncs(){
    vector<QBitArray> functions;
    int count = reg.GetCountVectors();
    QBitArray vectfirst(n);
    for(int i=0;i<n-p;i++){
        vectfirst[i] = 0;
    }
    for(int i=n-p;i<n;i++){
        vectfirst[i] = 1;
    }

    QBitArray function(n);
    QBitArray flast(n);
    for(int i=0;i<n;i++){
        function[i] = 0;
        flast[i] = 1;
    }

    QBitArray vect(n);
    while(function!=flast){
        vect = vectfirst;
        int c = 1;
        bool funcvalue = false;
        for(int i = 0; i<n; i++){
            if(function[i]){
                funcvalue |= !vect[i];
            }
        }
        vect = reg.ShiftRight(vect, funcvalue);
        QSet<QBitArray> set;
        set <<  vectfirst;
        while(c<count && !set.contains(vect)){
            set<<vect;
            c++;
            //*******************
            //ADD OpNot-CHECK
            //*******************
            funcvalue = false;
            for(int i = 0; i<n; i++){
                if(function[i] == true){
                    funcvalue |= !vect[i];
                }
            }
            vect = reg.ShiftRight(vect, funcvalue);
        }
        if(c==count){
            functions.push_back(function);
        }
        function = FunctionGenerator::IncFunction(function);
    }
    return functions;
}

vector<QBitArray> FunctionGenerator::GetNotXorFuncs(){
    vector<QBitArray> functions;
    int count = reg.GetCountVectors();
    QBitArray vectfirst(n);
    for(int i=0;i<n-p;i++){
        vectfirst[i] = 0;
    }
    for(int i=n-p;i<n;i++){
        vectfirst[i] = 1;
    }

    QBitArray function(n);
    QBitArray flast(n);
    for(int i=0;i<n;i++){
        function[i] = 0;
        flast[i] = 1;
    }

    QBitArray vect(n);
    while(function!=flast){
        vect = vectfirst;
        int c = 1;
        bool funcvalue = false;
        for(int i = 0; i<n; i++){
            if(function[i]){
                funcvalue ^= !vect[i];
            }
        }
        vect =reg.ShiftRight(vect, funcvalue);
        QSet<QBitArray> set;
        set <<  vectfirst;
        while(c<count && !set.contains(vect)){
            set<<vect;
            c++;
            //*******************
            //ADD OpNot-CHECK
            //*******************
            funcvalue = false;
            for(int i = 0; i<n; i++){
                if(function[i] == false){
                    funcvalue ^= !vect[i];
                }
            }
            vect = reg.ShiftRight(vect, funcvalue);
        }
        if(c==count){
            functions.push_back(function);
        }
        function = FunctionGenerator::IncFunction(function);
    }
    return functions;
}

vector<vector<int>> FunctionGenerator::GetFuncs(bool opAnd, bool opOr, bool opXor, bool opNot){
    //0 - nothing
    //1 - and
    //2 - or
    //3 - xor
    //4 - andnot
    //5 - ornot
    //6 - xornot
    vector<vector<int>> functions;
    //double count = 0;
    for(double i = 1; i < pow(10,n);i++){
        vector<int> f;
        double buf = i;
        for(int j = 0; j<n; j++){
            f.push_back(int(fmod(buf,10)));
            buf = buf/10;
        }
        bool isAllFunc = true;
        for(int j=0;j<n;j++){
            if(!IsFunc(f[j],opAnd, opOr, opXor, opNot)){
                isAllFunc = false;
            }
        }
        if(isAllFunc){
            if(reg.CheckFunc(f)){
                functions.push_back(f);
            }
        }
    }
    return functions;
}

bool FunctionGenerator::IsFunc(int f, bool opAnd, bool opOr, bool opXor, bool opNot){
    bool res = false;
    switch (f){
    case 0:
        res = true;
        break;
    case 1:
        res = opAnd;
        break;
    case 2:
        res = opOr;
        break;
    case 3:
        res = opXor;
        break;
    case 4:
        res = opAnd&&opNot;
        break;
    case 5:
        res = opOr&&opNot;
        break;
    case 6:
        res = opXor&&opNot;
        break;
    }
    return res;
}
