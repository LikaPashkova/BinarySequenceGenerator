#include "converter.h"
#include <vector>
#include <iostream>
#include <QString>
#include <QVariant>
#include <QBitArray>
#include <QSet>

Converter::Converter(int n, int p)
{
    this->n = n;
    this->p = p;
}
Converter::~Converter(){}

QString Converter::FunctionAndToString(QBitArray vect){
    QString str = "";
    int i = 0;
    while(i<n&&!vect[i]){
        i++;
    }
    if(i<n){
        str += "X"+QString::number(i+1);
        i++;
    }
    while(i<n){
        if(vect[i]){
            str += "•X"+QString::number(i+1);
        }
        i++;
    }
    return str;
}

QString Converter::FunctionNotAndToString(QBitArray vect){
    QString str = "";
    int i = 0;
    while(i<n&&!vect[i]){
        i++;
    }
    if(i<n){
        str += "!X"+QString::number(i+1);
        i++;
    }
    while(i<n){
        if(vect[i]){
            str += "•!X"+QString::number(i+1);
        }
        i++;
    }
    return str;
}

QString Converter::FunctionOrToString(QBitArray vect){
    QString str = "";
    int i = 0;
    while(i<n&&!vect[i]){
        i++;
    }
    if(i<n){
        str += "X"+QString::number(i+1);
        i++;
    }
    while(i<n){
        if(vect[i]){
            str += "+X"+QString::number(i+1);
        }
        i++;
    }
    return str;
}

QString Converter::FunctionNotOrToString(QBitArray vect){
    QString str = "";
    int i = 0;
    while(i<n&&!vect[i]){
        i++;
    }
    if(i<n){
        str += "!X"+QString::number(i+1);
        i++;
    }
    while(i<n){
        if(vect[i]){
            str += "+!X"+QString::number(i+1);
        }
        i++;
    }
    return str;
}

QString Converter::FunctionXorToString(QBitArray vect){
    QString str = "";
    int i = 0;
    while(i<n&&!vect[i]){
        i++;
    }
    if(i<n){
        str += "X"+QString::number(i+1);
        i++;
    }
    while(i<n){
        if(vect[i]){
            str += "⊕X"+QString::number(i+1);
        }
        i++;
    }
    return str;
}

QString Converter::FunctionNotXorToString(QBitArray vect){
    QString str = "";
    int i = 0;
    while(i<n&&!vect[i]){
        i++;
    }
    if(i<n){
        str += "!X"+QString::number(i+1);
        i++;
    }
    while(i<n){
        if(vect[i]){
            str += "⊕!X"+QString::number(i+1);
        }
        i++;
    }
    return str;
}

QString Converter::FuncToString(vector<int> f){
    QString str = "";
    if(!f.empty()){
        for(int i=1; i<n; i++){
            if(str.length()==0){
                switch (f[i]) {
                case 1:
                case 2:
                case 3:
                    str += "X"+QString::number(i+1);
                    break;
                case 4:
                case 5:
                case 6:
                    str += "!X"+QString::number(i+1);
                    break;
                }
            }else{
                switch (f[i]) {
                case 1:
                    str += "•X"+QString::number(i+1);
                    break;
                case 2:
                    str = "("+str+"+X"+QString::number(i+1)+")";
                    break;
                case 3:
                    str += "⊕X"+QString::number(i+1);
                    break;
                case 4:
                    str += "•!X"+QString::number(i+1);
                    break;
                case 5:
                    str = "("+str+ "+!X"+QString::number(i+1)+")";
                    break;
                case 6:
                    str += "⊕!X"+QString::number(i+1);
                    break;
                }
            }

        }
    }
    return str;
}

