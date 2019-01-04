#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <QTime>
#include <QTimer>
#include <QPropertyAnimation>
#include <QScreen>
#include <QDesktopWidget>
#include <QPoint>
#include <string>
#include <ctime>
#include <QCloseEvent>
#include <QSettings>
#include <QMessageBox>
#include <QtGui>
#include <QTextEdit>
#include <QSystemTrayIcon>
#include <QList>
#include <QDialog>
#include <QDialogButtonBox>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <dialogsetting.h>
#include <screenrect.h>
#include "dialog.h"
#include "ui_dialog.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mOpenDialBtn = ui->buttonODialog;
    comboBox = ui->comboBox;
    comboboxTime = ui->comboBoxTime;
    mlabel = ui->label;
    labelCurrentTime = ui->labelCurrentTime;
    spinBoxSec = ui->spinBoxSec;
    spinBoxMin = ui->spinBoxMin;
    spinBoxHour = ui->spinBoxHour;
    frameGreen = ui->frameGreen;
    framePink = ui->framePink;
    frameHourGlass =ui->frameHourGlass;
    setting = ui->setting;
    widgetTop = ui->widgetTop;
    widgetBottom = ui->widgetBottom;
    widgetClose = ui->widgetClose;
    widgetMinDrop = ui->widgetMinDrop;
    mbutton = ui->pushButton;
    mlabel = ui->label;
    buttonbox = ui->buttonBox;

    buttonbox->setVisible(false);
    widgetTop->setVisible(false);
    widgetMinDrop->setVisible(false);

    qMenu = new QMenu();
    actClose = new QAction();
    actShow = new QAction();
    actShutdown = new QAction();
    actReboot = new QAction();
    actSleep = new QAction();
    actHide = new QAction();
    actClose->setIcon(QIcon( ":/images/imgActions/close_red.png" ));
    actShow->setIcon(QIcon( ":/images/imgActions/show.png" ));
    actShutdown->setIcon(QIcon( ":/images/imgActions/shutdown.png" ));
    actReboot->setIcon(QIcon( ":/images/imgActions/restart.png" ));
    actSleep->setIcon(QIcon( ":/images/imgActions/sleep.png" ));
    actHide->setIcon(QIcon(":/images/imgActions/hide.png"));
    actShutdown->setText(tr("Shutdown"));
    actReboot->setText(tr("Reboot"));
    actSleep->setText(tr("Suspend"));
    actShow->setText(tr("Show"));
    actHide->setText(tr("Hide to tray"));
    actClose->setText(tr("Exit"));
    connect(actClose, SIGNAL(triggered(bool)), this, SLOT(actionsClose()));
    connect(actShow, SIGNAL(triggered(bool)), this, SLOT(actionShow()));
    connect(actShutdown, SIGNAL(triggered(bool)), this, SLOT(actionsShutdown()));
    connect(actReboot, SIGNAL(triggered(bool)), this, SLOT(actionsReboot()));
    connect(actSleep, SIGNAL(triggered(bool)), this, SLOT(actionsSleep()));
    connect(actHide, SIGNAL(triggered(bool)), this, SLOT(messageClickedd()));
    qMenu->addAction(actShutdown);
    qMenu->addAction(actReboot);
    qMenu->addAction(actSleep);
    qMenu->addSeparator();
    qMenu->addAction(actShow);
    qMenu->addAction(actHide);
    qMenu->addAction(actClose);

    qPointMouse = new QPoint();

    frameGreenAnim = new QPropertyAnimation(frameGreen, "geometry");
    widgetTopAnim = new QPropertyAnimation(widgetTop, "geometry");
    widgetBottomAnim = new QPropertyAnimation(widgetBottom, "geometry");
    widgetMinDropAnim = new QPropertyAnimation(widgetMinDrop, "geometry");

    settingsSave = new QSettings("settings.conf",QSettings::NativeFormat);
    frameGreen->setGeometry(-241, frameGreen->geometry().y(), frameGreen->geometry().width(), frameGreen->geometry().height());

    setting->setAttribute(Qt::WA_Hover);
    setting->installEventFilter(this);
    widgetClose->installEventFilter(this);
    widgetClose->setToolTip(tr("close"));
    mdDialog1 = new Dialog1();
    settingWindow = new SettingWindow();
    connect(mdDialog1->ui->comboBoxStitching, SIGNAL(activated(int)), this, SLOT(updateDialogTimeBox()));
    connect(mdDialog1->ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptDialog()));
    connect(mdDialog1->ui->buttonBox, SIGNAL(rejected()), this, SLOT(dialogRejected()));
    connect(mdDialog1, SIGNAL(sigClose()), this, SLOT(dialogRejected()));
    connect(settingWindow->checkBoxCommand, SIGNAL(stateChanged(int)), this, SLOT(settingCheckboxComand()));
    connect(settingWindow->checkBoxTopLevel, SIGNAL(stateChanged(int)), this, SLOT(settingCheckboxComand()));
    connect(settingWindow->spinBoxDelay, SIGNAL(valueChanged(int)), this, SLOT(settingWindowSpin()));



    trayIcon = new QSystemTrayIcon( QIcon( ":/images/MyCountDownTimer.png" ), this );
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                 this, SLOT(messageClickedd()));

    tmr = new QTimer(this);
    ii = 30;
    qCurrenttimer = new QTime();
    tmrCurrent = new QTimer(this);
    tmrCurrent->start(1000);
    connect(tmrCurrent, SIGNAL(timeout()), this, SLOT(updateCurrentTime()));
    tmrCurrent->start();


    mIsClickable = true;
    trayIcon->show();
    trayIcon->setContextMenu(qMenu);
    settingCheckboxComand();
    messageBox = new QMessageBox();
    readSettings();
    mlabel->setText(QString::number(spinBoxHour->value())+":"+ QString::number(spinBoxMin->value()) +":" +QString::number(spinBoxSec->value()) + " ");
    kostyl = 2;

}

MainWindow::~MainWindow()
{
    delete ui;


}

char *shutDownd = "systemctl poweroff";
char *reboot = "systemctl reboot";
char *waitingMode = "systemctl suspend";
void MainWindow::on_pushButton_clicked()
{
    if (timerIsRun == true){
        timeStop();
        mbutton->setStyleSheet(":hover {"
                               "image: url(:/images/start.png);"
                               "border-style: outset;"
                               "border-width: 2px;"
                               "border-radius: 10px;"
                               "border-color: beige;"
                               "font: bold 14px;"
                               "min-width: 10em;"
                               "padding: 5px;"
                               "border: none;}"
                               "QPushButton{"
                               "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));"
                               "image: url(:/images/start.png);"
                               "border: none;}");
        timerIsRun = false;
        comboboxTime->setEnabled(true);
        comboboxTime->setToolTip(tr("Select"));
    } else {
        timerIsRun = true;
        comboboxTime->setDisabled(true);
        comboboxTime->setToolTip(tr("You can't select while timer is run, stop for change it"));

        mbutton->setStyleSheet(":hover {"
                               "image: url(:/images/hourglass/stop.png);"
                               "border-style: outset;"
                               "border-width: 2px;"
                               "border-radius: 10px;"
                               "border-color: beige;"
                               "font: bold 14px;"
                               "min-width: 10em;"
                               "padding: 10px;"
                               "border: none;}"
                               "QPushButton{"
                               "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));"
                               "image: url(:/images/hourglass/stop.png);"
                               "padding: 5px;"
                               "border: none;}");
        widgetTopAnim->stop();
        widgetBottomAnim->stop();
        hor = ui->spinBoxHour->value();
        min = ui->spinBoxMin->value();
        sec = ui->spinBoxSec->value();

        if(min==0){
            min = ui->spinBoxMin->value();
        }
        minDouble = ui->spinBoxMin->text().toInt();
        horDouble = ui->spinBoxHour->text().toInt();
        if(comboboxTime->currentIndex()==0){
            sum = hor * 3600 + min * 60 + sec;
            ii=sum;
            timerIsStart0 = true;
            timerIsStart1 = false;
        }
        widgetTop->setVisible(true);
        widgetMinDrop->setVisible(true);
        if(comboboxTime->currentIndex()==1){
            currentHour = qCurrenttimer->currentTime().hour();
            currentMin = qCurrenttimer->currentTime().minute();
            currentSec = qCurrenttimer->currentTime().second();
            sum = hor * 3600 + min * 60 + sec;
            sumCurrent = currentHour * 3600 + currentMin * 60 + currentSec;
            timerIsStart0 = false;
            timerIsStart1 = true;
            if(sumCurrent > sum){
                double day = 86400;
                double temporarily = 0;
                double hourD = 0;
                double minD = 0;
                double secD = 0;
                double temporarilyS = 0;
                double temporarilyI = 0;
                day -= sumCurrent;
                temporarily = day + sum;
                sum = static_cast<int>(temporarily);
                // count is ready seconds
                hourD = floor(sum / 3600);
                temporarilyI = sum - 3600 * hourD;
                minD = floor(temporarilyI / 60);
                temporarilyS = minD * 60;
                secD = temporarilyI - temporarilyS;
                hourB = int (hourD);
                minB = int (minD);
                secB = int (secD);
                ii = sum;
//                mlabel->setText(QString::number(hourB)+":"+ QString::number(minB) +":" +QString::number(secB) + " ");
//                mbutton->setText("day");
            } else if(sumCurrent < sum){
                sum = sum - sumCurrent;
                double hourD = 0;
                double minD = 0;
                double secD = 0;
                double temporarilyS = 0;
                double temporarilyI = 0;
                hourD = floor(sum / 3600);
                temporarilyI = sum - 3600 * hourD;
                minD = floor(temporarilyI / 60);
                temporarilyS = minD * 60;
                secD = temporarilyI - temporarilyS;
                hourB = int (hourD);
                minB = int (minD);
                secB = int (secD);
                ii = sum;
//                mlabel->setText(QString::number(hourB)+":"+ QString::number(minB) +":" +QString::number(secB) + " ");
//                mbutton->setText("-");

            }
        }
             frameAnim();
             tmr->start(1000);
             tmr->disconnect();
             connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
             tmr->start();
    }


}
void MainWindow::closeEvent(QCloseEvent *event){
    this->close();
    settingWindow->close();
    if(mdDialog1->isVisible()) mdDialog1->close();
}
void MainWindow::settingWindowSpin(){
    mdDialog1->labelText->setText(QString::number(settingWindow->spinBoxDelay->value()));
    mdDialog1->progresBar->setValue(settingWindow->spinBoxDelay->value());
}

void MainWindow::readSettings(){
    spinBoxHour->setValue(settingsSave->value("time/spinBoxHour", 0).toInt());
    spinBoxMin->setValue(settingsSave->value("time/spinBoxMin", 0).toInt());
    spinBoxSec->setValue(settingsSave->value("time/spinBoxSec", 0).toInt());
    comboBox->setCurrentIndex(settingsSave->value("act/currentIndex", 2).toInt());
    comboboxTime->setCurrentIndex(settingsSave->value("act/comboBoxTime", 1).toInt());


}
void MainWindow::saveSetting(){
    settingsSave->setValue("time/spinBoxHour", spinBoxHour->value());
    settingsSave->setValue("time/spinBoxMin", spinBoxMin->value());
    settingsSave->setValue("time/spinBoxSec", spinBoxSec->value());
    settingsSave->setValue("act/currentIndex", comboBox->currentIndex());
    settingsSave->setValue("act/comboBoxTime", comboboxTime->currentIndex());
    settingsSave->sync();
}

void MainWindow::frameAnim(){
    // animation for frame to right
    widgetTopAnim->setDuration(ii * 1000);
    widgetTopAnim->setStartValue(QRect(widgetTop->geometry().x(), 15, widgetTop->geometry().width(), 150));
    widgetTopAnim->setEndValue(QRect(widgetTop->geometry().x(), 145, widgetTop->geometry().width(), 0));
    widgetTopAnim->start();

    widgetBottomAnim->setDuration(ii * 1000);
    widgetBottomAnim->setStartValue(QRect(30, 345, 210, 0));
    widgetBottomAnim->setEndValue(QRect(30, 225, 211, 121));
    widgetBottomAnim->start();


}
void MainWindow::actionShow(){
    this->setFocus();
    this->activateWindow();
    this->raise();
    this->showNormal();
    this->setVisible(true);
    this->show();



}
void MainWindow::actionsUse(){
}
void MainWindow::actionsShutdown(){
    system(shutDownd);
}
void MainWindow::actionsReboot(){
    system(reboot);
}
void MainWindow::actionsHide(){
    this->hide();
}
void MainWindow::actionsSleep(){
    system(waitingMode);
}
void MainWindow::updateTime(){

    if(ii>0){
    --ii;
}
    if(timerIsRun == true){
        if(comboboxTime->currentIndex()==0 && timerIsStart0 == true){
            if(sec==0 && ii>0){
                sec = 60;
                if(min >= 0 ){
                    if(hor > 0 && min == 0){
                        --hor;
                        min = 60;
                    }
                    --min;
                }
            }
            if(sec>0){
                --sec;
            }
            mlabel->setText(QString::number(hor)+":"+ QString::number(min) +":" +QString::number(sec) + " ");

        }

        if(comboboxTime->currentIndex()==1 && timerIsStart1 == true){
            if(secB==0 && ii>0){
                secB = 60;
                if(minB >=0 ){
                    if (hourB > 0 && minB == 0){
                        --hourB;
                        minB = 60;
                    }
                    --minB;
                }
            }
            if(secB>0){
                --secB;
            }
            mlabel->setText(QString::number(hourB)+":"+ QString::number(minB) +":" +QString::number(secB) + " ");
        }
    }


    widgetMinDropAnim->setDuration(1000);
    widgetMinDropAnim->setStartValue(QRect(124, 100, widgetMinDrop->geometry().width(), 120));
    widgetMinDropAnim->setEndValue(QRect(widgetMinDrop->geometry().x(), 355, widgetMinDrop->geometry().width(), 0));
    widgetMinDropAnim->start();

    if(ii == settingWindow->spinBoxDelay->value() && settingWindow->checkBoxDelay->isChecked()){
        mdDialog1->progresBar->setMaximum(settingWindow->spinBoxDelay->value());
        mdDialog1->labelText2->setText(comboBox->currentText() + '\n' + tr("trough:"));
        mdDialog1->setModal(true);
        dialogShow();
    }
    if(ii < settingWindow->spinBoxDelay->value()){

        if(comboboxTime->currentIndex() == 1){
            mdDialog1->labelText->setText(QString::number(secB));
            mdDialog1->progresBar->setValue(secB);
        } else {
            mdDialog1->labelText->setText(QString::number(sec));
            mdDialog1->progresBar->setValue(sec);
        }


    }
    if(ii==0){
        tmr->disconnect();
        timerIsRun = false;
        comboboxTime->setEnabled(true);
        mbutton->setStyleSheet(":hover {"
                               "image: url(:/images/start.png);"
                               "border-style: outset;"
                               "border-width: 2px;"
                               "border-radius: 10px;"
                               "border-color: beige;"
                               "font: bold 14px;"
                               "min-width: 10em;"
                               "padding: 5px;"
                               "border: none;}"
                               "QPushButton{"
                               "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));"
                               "image: url(:/images/start.png);"
                               "border: none;}");
        timeStop();

        if(settingWindow->checkBoxDelay->isChecked()){
            if(mdDialog1->progresBar->value()==0 && mdDialog1->isActiveWindow()){
                mdDialog1->close();
                shutDown();
            }
        } else {
            shutDown();
        }

    }


}
void MainWindow::updateCurrentTime(){
    labelCurrentTime->setText(QTime::currentTime().toString());

}

void MainWindow::shutDown(){
    if (ii==0){
        if(comboBox->currentIndex()==0){
            system(shutDownd);

        }
        if(comboBox->currentIndex()==1){
            system(reboot);

        }
        if(comboBox->currentIndex()==2){
            mdDialog1->close();
            system(waitingMode);
        }
        if(comboBox->currentIndex()==3){
            settingWindow->userComand();

        }
    }
}
void MainWindow::actionsClose(){
    messageBox->close();
    this->close();
}
void MainWindow::updateDialogTimeBox(){
    tmr->disconnect();
    switch (mdDialog1->comboBoxStitching->currentIndex()) {
    case 0:
        break;
    case 1:
        ii = 300;
        min = 5;
        minB = 5;
        mdDialog1->hide();
        break;
    case 2:
        ii = 600;
        min = 10;
        minB = 10;
        mdDialog1->hide();
        break;
    case 3:
        ii = 900;
        min = 15;
        minB = 15;
        mdDialog1->hide();
        break;
    case 4:
        ii = 1200;
        min = 20;
        minB = 20;
        mdDialog1->hide();
        break;
    case 5:
        ii = 1800;
        min = 30;
        minB = 30;
        mdDialog1->hide();
        break;
    case 6:
        ii = 3000;
        min = 50;
        minB = 50;
        mdDialog1->hide();
        break;
    }
    sec = 0;
    secB = 0;
    hor = 0;
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start(1000);
    tmr->start();
    widgetTopAnim->stop();
    widgetBottomAnim->stop();
    frameAnim();
    mdDialog1->comboBoxStitching->setCurrentIndex(0);

}

void MainWindow::on_label_linkActivated(const QString &link)
{
    switch (mdDialog1->comboBoxStitching->currentIndex()) {
    case 0:
        ii = 0;
        this->close();
        break;
    }
}

void MainWindow::on_buttonBox_rejected()
{
    tmr->stop();
    tmr->disconnect();
    widgetTopAnim->stop();
    widgetBottomAnim->stop();
    updateDialogTimeBox();
    trayIcon->show();
    trayIcon->showMessage("tittle", tr("Time stopped"), QSystemTrayIcon::Information, 3000);
}
void MainWindow::dialogRejected(){
    tmr->stop();
    tmr->disconnect();
    widgetTopAnim->destroyed();
    widgetBottomAnim->destroyed();
    widgetMinDropAnim->destroyed();
    timerIsRun = false;
    comboboxTime->setEnabled(true);
    mbutton->setStyleSheet(":hover {"
                           "image: url(:/images/start.png);"
                           "border-style: outset;"
                           "border-width: 2px;"
                           "border-radius: 10px;"
                           "border-color: beige;"
                           "font: bold 14px;"
                           "min-width: 10em;"
                           "padding: 5px;"
                           "border: none;}"
                           "QPushButton{"
                           "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));"
                           "image: url(:/images/start.png);"
                           "border: none;}");
    timeStop();
}
void MainWindow::acceptDialog(){
    mdDialog1->close();
    ii=0;
    shutDown();

}
void MainWindow::dialogClose(){
    ii=0;
    mlabel->setText("0:0:0");
    trayIcon->show();
    trayIcon->showMessage("MyCountDownTimer", tr("Time stopped DialogClose"), QSystemTrayIcon::Information, 3000);
}
void MainWindow::timeStop(){
    tmr->stop();
    tmr->disconnect();
    widgetTopAnim->destroyed();
    widgetTopAnim->stop();
    widgetBottomAnim->destroyed();
    widgetBottomAnim->stop();
    widgetMinDropAnim->destroyed();
    widgetMinDropAnim->stop();
    widgetMinDrop->setVisible(false);
    widgetTop->setVisible(false);
    ii=0;
    mlabel->setText("0:0:0");
    trayIcon->show();
    trayIcon->showMessage("MyCountDownTimer", tr("Time stopped"), QSystemTrayIcon::Information, 3000);
}
void MainWindow::settingCheckboxComand(){
    if(settingWindow->checkBoxCommand->isChecked()){

    }else{
        comboBox->setCurrentIndex(2);
    }
    if(settingWindow->checkBoxTopLevel->isChecked()){
        this->setWindowFlags(windowFlags () | Qt :: WindowStaysOnTopHint);
        this->show();
        if(kostyl2 == true){
            settingWindow->show();
        }
    } else {
        //this->setWindowFlags(windowFlags () | Qt :: WindowStaysOnBottomHint);
        this->setWindowFlags(windowFlags () & ~ Qt :: WindowStaysOnTopHint);
        this->show();
        if(kostyl2 == true){
            settingWindow->show();
        }
    }

}
void MainWindow::messageClickedd(){
    if(this->isVisible()){
        this->hide();
        trayIcon->showMessage("MyCountDownTimer", tr("App work and hide to tray"), QSystemTrayIcon::NoIcon, 5000);

    } else {
        actionShow();
    }
   // QPoint p = this->mapFromGlobal(QCursor::pos());
    //qMenu->move(p);
   // qMenu->show();


}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason){
    switch (reason) {
         case QSystemTrayIcon::Trigger:
        break;
    }
}

void MainWindow::on_buttonBox_accepted()
{

}



void MainWindow::on_buttonODialog_clicked()
{
    screenrect *rec = new screenrect();
    rec->windowCenter(settingWindow);
    kostyl2 = true;

}
void MainWindow::dialogShow(){
    QDesktopWidget desktop;
    QRect  screenRect = desktop.availableGeometry(desktop.primaryScreen());
    QPoint topLeft = screenRect.topLeft();
    int top = screenRect.top();
    QPoint center = screenRect.center();
    int x = center.x() - (mdDialog1->width()/2);
    int y = center.y() - (mdDialog1->height()/2);
    center.setX(x);
    center.setY(y);
    int right = screenRect.right();
    mdDialog1->setModal(true);

    switch (settingWindow->iWindow) {
    case 0:
        mdDialog1->move(topLeft);
        mdDialog1->show();
        break;
    case 1:
        mdDialog1->move(right/2 - mdDialog1->width()/2, top);
        mdDialog1->show();
        break;
    case 2:
        mdDialog1->move(screenRect.right()-mdDialog1->width(), screenRect.top());
        mdDialog1->show();

        break;
    case 3:
        mdDialog1->move(screenRect.left() - mdDialog1->width(), y);
        mdDialog1->show();

        break;
    case 4:
        mdDialog1->move(center);
        mdDialog1->show();
        break;
    case 5:
        mdDialog1->move(screenRect.right()-mdDialog1->width(), y);
        mdDialog1->show();
        break;

    case 6:
        mdDialog1->move(screenRect.top(), x);
        mdDialog1->show();
        break;
    case 7:
        mdDialog1->move(screenRect.right()/2 - mdDialog1->width()/2, screenRect.bottom()-mdDialog1->height());
        mdDialog1->show();
        break;
    case 8:
        mdDialog1->move(screenRect.right() - mdDialog1->width(), screenRect.bottom()-mdDialog1->height());
        mdDialog1->show();
        break;

    }
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    xPosition = event->x();
    yPosition = event->y();
    qPointMouse->setX(xPosition);
    qPointMouse->setY(yPosition);

}
void MainWindow::setting_cliked(){
    frameGreenAnim->setDuration(400);
    frameGreenAnim->setStartValue(QRect(-241, frameGreen->geometry().y(), frameGreen->geometry().width(), frameGreen->geometry().height()));
    frameGreenAnim->setEndValue(QRect(0, frameGreen->geometry().y(), frameGreen->geometry().width(), frameGreen->geometry().height()));
    frameGreenAnim->start();
}

bool MainWindow::eventFilter(QObject *pObject, QEvent *pEvent){
    if (pObject == setting){
    if (pEvent->type() == QEvent::MouseButtonPress){
            emit setting_cliked();
    }
        return false;
    }
    if (pObject == widgetClose){
    if(pEvent->type() == QEvent::MouseButtonPress){
            frameGreenAnim->setDuration(400);
            frameGreenAnim->setStartValue(QRect(0, frameGreen->geometry().y(), frameGreen->geometry().width(), frameGreen->geometry().height()));
            frameGreenAnim->setEndValue(QRect(-241, frameGreen->geometry().y(), frameGreen->geometry().width(), frameGreen->geometry().height()));
            frameGreenAnim->start();
    }
    return false;
    } else {
        return true;
    }
}


void MainWindow::on_setting_windowTitleChanged(const QString &title)
{

}
void MainWindow::on_spinBoxHour_valueChanged(int arg1)
{
    if(kostyl==2){
        saveSetting();
        mlabel->setText(QString::number(spinBoxHour->value())+":"+ QString::number(spinBoxMin->value()) +":" +QString::number(spinBoxSec->value()) + " ");

    }

}
void MainWindow::on_spinBoxMin_valueChanged(int arg1)
{
    if(kostyl==2){
        saveSetting();
        mlabel->setText(QString::number(spinBoxHour->value())+":"+ QString::number(spinBoxMin->value()) +":" +QString::number(spinBoxSec->value()) + " ");

    }
}
void MainWindow::on_spinBoxSec_valueChanged(int arg1)
{
    if(kostyl==2){
        saveSetting();
        mlabel->setText(QString::number(spinBoxHour->value())+":"+ QString::number(spinBoxMin->value()) +":" +QString::number(spinBoxSec->value()) + " ");

    }
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{

    if(kostyl==2){
        if (comboBox->currentIndex() == 3 && settingWindow->checkBoxCommand->isChecked() == true && settingWindow->textComand->text().isEmpty()){
            comboBox->setCurrentIndex(settingsSave->value("act/currentIndex", 2).toInt());
            QMessageBox::information(this,"Attention", tr("Enter the command in the settings!"));

        }
        if(comboBox->currentIndex() == 3 && settingWindow->checkBoxCommand->isChecked() == false){
            comboBox->setCurrentIndex(settingsSave->value("act/currentIndex", 2).toInt());
            QString strMessagebox = tr("Select the command in the settings!");
            QMessageBox::information(this,"Attention", strMessagebox);
        }


        saveSetting();
    }
}
void MainWindow::on_comboBoxTime_currentIndexChanged(int index){
    if(kostyl==2){
        saveSetting();
    }
}

void MainWindow::on_about_clicked()
{
    QString strAbout = tr("A graphical utility to turn off the device. \n \n"
                          "This program uses Qt version 5.11.0.");
    messageBox->setWindowTitle("About");
    messageBox->setText(tr("MyCountDownTimer 0.0.1."));
    messageBox->setInformativeText(strAbout);
    //messageBox->aboutQt(this, " ");
//    messageBox->setInformativeText("Графическая утилита выключения устройства. \n \n"
//                                   "Эта программа использует Qt версию 5.11.0.");
    messageBox->setIconPixmap(QPixmap(":/images/new/iconMessageBoxQt.png"));
    messageBox->setDefaultButton(QMessageBox::Discard);
    QAbstractButton *aboutQt =
            messageBox->addButton(tr("About Qt"), QMessageBox::ActionRole);
    QAbstractButton *close =
            messageBox->addButton(tr("Close"), QMessageBox::ActionRole);

    messageBox->exec();
    if (messageBox->clickedButton() == close) {
       messageBox->close();
       messageBox->removeButton(aboutQt);
       messageBox->removeButton(close);
    }
    if (messageBox->clickedButton() == aboutQt){
        messageBox->aboutQt(this, "About Qt");
        messageBox->removeButton(aboutQt);
        messageBox->removeButton(close);

    }

}
