#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "functiongenerator.h"
#include "register.h"
#include "converter.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_npfunc_button_clicked();

    void on_button_funcs_clicked();

    void on_button_sequence_clicked();
    
    void on_button_sequence_in_file_clicked();

private:
    Ui::MainWindow *ui;
    vector<QBitArray> funcsAnd;
    vector<QBitArray> funcsNotAnd;
    vector<QBitArray> funcsOr;
    vector<QBitArray> funcsNotOr;
    vector<QBitArray> funcsXor;
    vector<QBitArray> funcsNotXor;
    vector<vector<int>> allF;
    Register rg = Register(0,0);
    FunctionGenerator fg = FunctionGenerator(rg,0,0);
    Converter cnv = Converter(0,0);

};

#endif // MAINWINDOW_H
