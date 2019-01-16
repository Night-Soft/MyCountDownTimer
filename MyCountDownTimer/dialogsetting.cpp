#include "dialogsetting.h"

DialogSettings::DialogSettings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DialogSettings)
{

    //ui->setupUi(this);


}

DialogSettings::~DialogSettings()
{
    delete ui;
}
