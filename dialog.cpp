#include <QDialog>
#include <QTime>
#include <QTimer>
#include <QApplication>

#include "dialog.h"
#include "ui_dialog.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1){
    ui->setupUi(this);
    labelText = ui->label;
    labelText2 = ui->label_2;
    progresBar = ui->progressBar;
    comboBoxStitching = ui->comboBoxStitching;

}
Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::on_buttonBox_accepted()
{

}

void Dialog1::on_buttonBox_rejected()
{
    this->close();
}
void Dialog1::closeEvent(QCloseEvent * event){
    this->close();
    sigClose();
}
void Dialog1::mousePressEvent(QMouseEvent *event){

}

