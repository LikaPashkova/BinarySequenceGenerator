#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <functiongenerator.cpp>
#include <register.cpp>
#include <converter.cpp>
#include <QBitArray>
#include <fstream>
#include <QFile>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_npfunc_button_clicked()
{

}
void MainWindow::on_button_funcs_clicked()
{

    //    ui->listWidget_funcs->addItem(QString::number(fg.GetCountVectors()));
    //        ui->listWidget_funcs->addItem("AND "+ (new QVariant(opAnd))->toString());
    QString strN = ui->line_in_n->text();
    QString strP = ui->line_in_p->text();
    int n = strN.toInt();
    int p = strP.toInt();
    if(n<1||p<=0||p>=n){
        ui->listWidget_funcs->addItem("N або P введені невірно.");
        ui->listWidget_funcs->addItem("N = 1, 2, 3, ...; P =  1, 2, ...;");
        return;
    }
    bool opAnd = ui->checkBox_and->checkState();
    bool opOr = ui->checkBox_or->checkState();
    bool opXor = ui->checkBox_xor->checkState();
    bool opNot = ui->checkBox_not->checkState();
    if(!(opAnd||opOr||opXor||opNot)){
        ui->listWidget_funcs->addItem("Оберіть хоча б одну операцію");
        return;
    }
    ui->listWidget_funcs->clear();
    ui->listWidget_vectors->clear();
    cnv = Converter(n,p);
    rg = Register(n,p);
    fg =  FunctionGenerator(rg,n,p);

    /*
//funcsAnd = fg.GetAndFuncs();
//        funcsNotAnd = fg.GetAndFuncs();
//        funcsOr = fg.GetAndFuncs();
//        funcsNotOr = fg.GetAndFuncs();
//        funcsXor = fg.GetAndFuncs();
//        funcsNotXor = fg.GetAndFuncs();
//    if(opAnd){
//        for(int k = 0; k<funcsAnd.size();k++){
//            ui->listWidget_funcs->addItem(fg.FunctionAndToString(funcsAnd[k]));
//        }
//        if(opNot){
//            funcsNotAnd = fg.GetNotAndFuncs();
//            for(int k = 0; k<funcsNotAnd.size();k++){
//                if(ui->listWidget_funcs->findItems(fg.FunctionNotAndToString(funcsNotAnd[k]), Qt::MatchContains).size()==0)
//                    ui->listWidget_funcs->addItem(fg.FunctionNotAndToString(funcsNotAnd[k]));
//            }
//        }
//    }
//    if(opOr){
//        funcsOr = fg.GetOrFuncs();
//        for(int k = 0; k<funcsOr.size();k++){
//            if(ui->listWidget_funcs->findItems(fg.FunctionOrToString(funcsOr[k]), Qt::MatchContains).size()==0)
//                ui->listWidget_funcs->addItem(fg.FunctionOrToString(funcsOr[k]));
//        }
//        if(opNot){
//            funcsNotOr = fg.GetNotOrFuncs();
//            for(int k = 0; k<funcsNotOr.size();k++){
//                if(ui->listWidget_funcs->findItems(fg.FunctionNotOrToString(funcsNotOr[k]), Qt::MatchContains).size()==0)
//                    ui->listWidget_funcs->addItem(fg.FunctionNotOrToString(funcsNotOr[k]));
//            }
//        }
//    }
//    if(opXor){
//        funcsXor = fg.GetXorFuncs();
//        for(int k = 0; k<funcsXor.size();k++){
//            if(ui->listWidget_funcs->findItems(fg.FunctionXorToString(funcsXor[k]), Qt::MatchContains).size()==0)
//                ui->listWidget_funcs->addItem(fg.FunctionXorToString(funcsXor[k]));
//        }
//        if(opNot){
//            funcsNotXor = fg.GetNotXorFuncs();
//            for(int k = 0; k<funcsNotXor.size();k++){
//                if(ui->listWidget_funcs->findItems(fg.FunctionNotXorToString(funcsNotXor[k]), Qt::MatchContains).size()==0)
//                    ui->listWidget_funcs->addItem(fg.FunctionNotXorToString(funcsNotXor[k]));
//            }
//        }
//    }*/


    allF = fg.GetFuncs(opAnd, opOr, opXor, opNot);
    for(int i = 0; i<allF.size();i++){
        if(ui->listWidget_funcs->findItems(cnv.FuncToString(allF[i]), Qt::MatchContains).size()==0)
            ui->listWidget_funcs->addItem(cnv.FuncToString(allF[i]));
    }
    ui->listWidget_funcs->setSelectionMode( QListWidget::SingleSelection );


}



void MainWindow::on_button_sequence_clicked()
{
    ui->listWidget_vectors->setSelectionMode( QListWidget::MultiSelection );
    ui->listWidget_vectors->clear();
    QList<QListWidgetItem*> ql = ui->listWidget_funcs->selectedItems();
    if(!ql.isEmpty()){
        int i = ui->listWidget_funcs->currentRow();
        if(i>=0){
            vector<QString> s = rg.GetSequence(allF[i]);
            for(int j= 0; j<s.size();j++){
                ui->listWidget_vectors->addItem(s[j]);
            }
        }
    }
}

void MainWindow::on_button_sequence_in_file_clicked()
{

    QFile fileOut("sequence.txt");
    QList<QListWidgetItem*> ql = ui->listWidget_funcs->selectedItems();
    if(!ql.isEmpty()){
        if(fileOut.open(QIODevice::WriteOnly)){
            int i = ui->listWidget_funcs->currentRow();
            i--;
            if(i>=0){
                vector<QString> s = rg.GetSequence(allF[i]);
                for(int j= 0; j<s.size();j++){
                    fileOut.write(s[j].toLocal8Bit().data());
                    fileOut.write("\n");
                }
            }
        }
    }
    fileOut.close();
}
