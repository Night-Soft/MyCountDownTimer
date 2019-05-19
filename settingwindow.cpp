#include <QEvent>
#include <QPropertyAnimation>
#include <QStyle>
#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QMessageBox>
#include <QtGui>
#include <QTextEdit>
#include <QtCore>

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>


SettingWindow::SettingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    checkBoxDelay = ui->checkBoxDelay;
    checkBoxCommand = ui->checkBoxCommand;
    checkBoxTopLevel = ui->checkBoxTopLevel;
    checkBoxAutoRun = ui->checkBoxAutoRun;
    spinBoxDelay = ui->spinBoxDelay;
    textComand = ui->textComand;
    label = ui->label;
    imageSettin1 = ui->imageSettin1;
    imageSettin2 = ui->imageSettin2;

    dialogCenter = ui->wDialogCenter;
    dialogLeft = ui->wDialogLeft;
    dialogRight = ui->wDialogRigth;
    dialogTop = ui->wDialogTop;
    dialogTopLeft = ui->wDialogTopLeft;
    dialogTopRight = ui->wDialogTopRigt;
    dialogBottom = ui->wDialogBottom;
    dialogBottomLeft = ui->wDialogBottomLeft;
    dialogBottomRight = ui->wDialogBottomReight;

    vectorMassive.append(dialogTopLeft);
    vectorMassive.append(dialogTop);
    vectorMassive.append(dialogTopRight);
    vectorMassive.append(dialogLeft);
    vectorMassive.append(dialogCenter);
    vectorMassive.append(dialogRight);
    vectorMassive.append(dialogBottomLeft);
    vectorMassive.append(dialogBottom);
    vectorMassive.append(dialogBottomRight);

    dDialog1 = new Dialog1();

    frame = ui->frame;
    frame2 = ui->frame_2;    frame2->hide();

    animation = new QPropertyAnimation(frame, "geometry");
    animation2 = new QPropertyAnimation(frame2, "geometry");

    settingsSave = new QSettings("settings.conf",QSettings::NativeFormat);

    imageSettin1->installEventFilter(this);
    imageSettin2->installEventFilter(this);
    dialogCenter->installEventFilter(this);
    dialogLeft->installEventFilter(this);
    dialogRight->installEventFilter(this);
    dialogTop->installEventFilter(this);
    dialogTopLeft->installEventFilter(this);
    dialogTopRight->installEventFilter(this);
    dialogBottom->installEventFilter(this);
    dialogBottomLeft->installEventFilter(this);
    dialogBottomRight->installEventFilter(this);
    imageSettin1->setStyleSheet("image: url(:/resources/other/settingList.png);"
                                "background-color: rgb(76, 92, 114);");
    imageSettin2->setEnabled(true);

    this->setWindowTitle(tr("Settings"));
    readSettings();
    kostyl =true;
    dialogStyle();
    on_checkBoxTopLevel_stateChanged();

}

SettingWindow::~SettingWindow()
{
    delete ui;
}


char *comandChar = "";

void SettingWindow::autoRun(){
    // Path to autostart dir
        QString autostartPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0) + QLatin1String("/autostart");
        // Check is there a directory in which the startup file will be stored
        QDir autorunDir(autostartPath);
        if(!autorunDir.exists()){
            // if not exsists, then creat
            autorunDir.mkpath(autostartPath);
        }
        QFile autorunFile(autostartPath + QLatin1String("/MyCountDownTimer.desktop"));
        if(checkBoxAutoRun->isChecked()) {
                if(!autorunFile.exists()){
                    if(autorunFile.open(QFile::WriteOnly)){
                        QString autorunContent("[Desktop Entry]\n"
                                               "Exec=" + QCoreApplication::applicationFilePath() + "\n"
                                               "Hidden=false\n"
                                               "NoDisplay=false\n"
                                               "Icon=MyCountDownTimer\n"
                                               "Categories=Utility;Accessibility;\n"
                                               "X-GNOME-Autostart-enabled=true\n"
                                               "Name[en_GB]=MyCountDownTimer\n"
                                               "Name=MyCountDownTimer\n"
                                               "Comment[en_GB]=MyCountDownTimer\n"
                                               "Comment=MyCountDownTimer\n"
                                               "Type=Application\n");

                        QTextStream outStream(&autorunFile);
                        outStream << autorunContent;
                        // Set permissions, including the execution of the file, otherwise autorun will not work
                        autorunFile.setPermissions(QFileDevice::ExeUser|QFileDevice::ExeOwner|QFileDevice::ExeOther|QFileDevice::ExeGroup|
                                               QFileDevice::WriteUser|QFileDevice::ReadUser);
                        autorunFile.close();
                    }
                }
            } else {
                // Удаляем файл автозапуска
                if(autorunFile.exists()) autorunFile.remove();
            }
}

void SettingWindow::readSettings(){
    checkBoxAutoRun->setChecked(settingsSave->value("CheckBox/AutoRun", false).toBool());
    checkBoxCommand->setChecked(settingsSave->value("CheckBox/Comand", false).toBool());
    checkBoxDelay->setChecked(settingsSave->value("CheckBox/Delay", true).toBool());
    checkBoxTopLevel->setChecked(settingsSave->value("CheckBox/TopLevel", true).toBool());
    spinBoxDelay->setValue(settingsSave->value("SpinBoxDelay/Delay", 27).toInt());
    iWindow = settingsSave->value("iWindow/iWindow", 4).toInt();
    textComand->setText(settingsSave->value("textComand/textComand", "").toString());




}
void SettingWindow::saveSetting(){
    settingsSave->setValue("CheckBox/Delay", checkBoxDelay->isChecked());
    settingsSave->setValue("CheckBox/AutoRun", checkBoxAutoRun->isChecked());
    settingsSave->setValue("CheckBox/Comand", checkBoxCommand->isChecked());
    settingsSave->setValue("CheckBox/TopLevel", checkBoxTopLevel->isChecked());
    settingsSave->setValue("SpinBoxDelay/Delay", spinBoxDelay->value());
    settingsSave->setValue("iWindow/iWindow", iWindow);
    settingsSave->setValue("textComand/textComand", textComand->text());


}
void SettingWindow::on_buttonBox_accepted()
{
    autoRun();
}
void SettingWindow::userComand(){
    QString strCommand;
    strCommand += textComand->text();
    m_process = new QProcess(this);
    qDebug() << "Execute command -> "+strCommand;
    m_process->start(strCommand);
    m_process->waitForFinished(-1);
    QString processStdout = m_process->readAllStandardOutput();
    QMessageBox::about(this, tr("Команда"), tr("Консольная команда выполнена!") + ("\n") + processStdout);
}

void SettingWindow::on_buttonBox_rejected()
{
    MainWindow w;
    w.spinBoxHour->setValue(21);
    w.show();
}
void SettingWindow::dialogStyle(){
    for(int i = 0; i <= 8; i++){
        if(i==iWindow){
            vectorMassive[iWindow]->setStyleSheet("image: url(:/resources/other/screenPos.png);"
                                                  "background-color: rgb(112, 126, 142);");
        }
        else{
            vectorMassive[i]->setStyleSheet("QWidget{"
                                            "background-color: rgb(76, 93, 114);}"
                                            "QWidget :hover{"
                                            "background-color: rgb(76, 93, 114);"
                                            "image: url(:/resources/other/screenPos.png);"
                                            "padding: 10px;}");
        }
    }
    saveSetting();
}

bool SettingWindow::eventFilter(QObject *pObject, QEvent *pEvent){
    if(mIsClickable){
        if(pObject == imageSettin1 && pEvent->type() == QEvent::MouseButtonPress && enabled1 == 1){
            emit setImageSettin1Clickable();
            imageSettin2->setStyleSheet("QWidget{image: url(:/resources/other/settingChoice.png);}"
                                        "QWidget :hover{"
                                        "image: url(:/resources/other/settingChoice.png);"
                                        "padding: 3px;}");
            imageSettin1->setStyleSheet("QWidget{image: url(:/resources/other/settingList.png);"
                                        "background-color: rgb(76, 92, 114);}"
                                        "QWidget :hover{"
                                        "image: url(:/resources/other/settingList.png);"
                                        "padding: 3px;}");
            imageSettin2->setEnabled(true);
            imageSettin1->setEnabled(false);
            enabled1 = 0;
            enabled2 = 1;
        }
        if(pObject == imageSettin2 && pEvent->type() == QEvent::MouseButtonPress && enabled2 == 1){
            emit setImageSettin2Clickable();
            imageSettin2->setStyleSheet("QWidget{image: url(:/resources/other/settingChoice.png);"
                                        "background-color: rgb(76, 92, 114);}"
                                        "QWidget :hover{"
                                        "image: url(:/resources/other/settingChoice.png);"
                                        "padding: 3px;}");
            imageSettin1->setStyleSheet("QWidget{image: url(:/resources/other/settingList.png);}"
                                        "QWidget :hover{"
                                        "image: url(:/resources/other/settingList.png);"
                                        "padding: 3px;}");

            imageSettin1->setEnabled(true);
            imageSettin2->setEnabled(false);
            enabled2 = 0;
            enabled1 = 1;
        }
        if(pObject == dialogLeft && pEvent->type() == QEvent::MouseButtonPress){
            emit dialogLeftClick();
        }
        if(pObject == dialogRight && pEvent->type() == QEvent::MouseButtonPress){
            iWindow = 5;
            dialogStyle();

        }
        if(pObject == dialogCenter && pEvent->type() == QEvent::MouseButtonPress){
            iWindow = 4;
            dialogStyle();

        }
        if(pObject == dialogTop && pEvent->type() == QEvent::MouseButtonPress){
            iWindow = 1;
            dialogStyle();

        }
        if(pObject == dialogTopLeft && pEvent->type() == QEvent::MouseButtonPress){
            iWindow = 0;
            dialogStyle();

        }
        if(pObject == dialogTopRight && pEvent->type() == QEvent::MouseButtonPress){
            iWindow = 2;
            dialogStyle();

        }
        if(pObject == dialogBottom && pEvent->type() == QEvent::MouseButtonPress){
            iWindow = 7;
            dialogStyle();

        }
        if(pObject == dialogBottomLeft && pEvent->type() == QEvent::MouseButtonPress){
            iWindow = 6;
            dialogStyle();

        }
        if(pObject == dialogBottomRight && pEvent->type() == QEvent::MouseButtonPress){
            iWindow = 8;
            dialogStyle();

        }
        return false;
    } else {
        return true;
    }
    kostyl = true;

}
void SettingWindow::dialogLeftClick(){
    iWindow = 3;
    dialogStyle();
}
void SettingWindow::setImageSettin1Clickable(){

    animSlideLeft();


    if(frame->isVisible()){

    } else {
        frame->show();
    }
}
void SettingWindow::setImageSettin2Clickable(){
    frame2->setGeometry(frame2->geometry().width(), 40, frame2->geometry().width(), frame2->geometry().height());
    frame2->show();
    animSlideRight();


}
void SettingWindow::animSlideRight(){
    // animation for frame to right
    animation->setDuration(500);
    animation->setStartValue(QRect(0, 40, frame->geometry().width(), frame->geometry().height()));
    animation->setEndValue(QRect(frame2->geometry().width(), frame->geometry().y(), frame->geometry().width(), frame->geometry().height()));
    animation->start();
    //animation for frame2 to left
    animation2->setDuration(500);
    animation2->setStartValue(QRect(frame2->geometry().width(), 40, frame2->geometry().width(), frame2->geometry().height()));
    animation2->setEndValue(QRect(0, 40, frame2->geometry().width(), frame2->geometry().height()));
    animation2->start();

}
void SettingWindow::animSlideLeft(){
    //animation for frame to left
    animation->setDuration(500);
    animation->setStartValue(QRect(frame->geometry().x(), frame->geometry().y(), frame->geometry().width(), frame->geometry().height()));
    animation->setEndValue(QRect(0, 40, frame->geometry().width(), frame->geometry().height()));
    animation->start();
    // animation for frame2 to right
    animation2->setDuration(500);
    animation2->setStartValue(QRect(0, 40, frame2->geometry().width(), frame2->geometry().height()));
    animation2->setEndValue(QRect(frame2->geometry().width(), 40, frame2->geometry().width(), frame2->geometry().height()));
    animation2->start();
}

void SettingWindow::on_checkBoxDelay_stateChanged(int arg1){
    if(kostyl) saveSetting();

}

void SettingWindow::on_checkBoxAutoRun_stateChanged(int arg1){
    if(kostyl){
        autoRun();
        saveSetting();
 }
}

void SettingWindow::on_checkBoxCommand_stateChanged(int arg1){
    if(kostyl) saveSetting();

}

void SettingWindow::on_spinBoxDelay_valueChanged(int arg1){
    if(kostyl) saveSetting();
    dDialog1->labelText->setText(QString::number(spinBoxDelay->value()));
    dDialog1->progresBar->setValue(spinBoxDelay->value());


}

void SettingWindow::on_checkBoxTopLevel_stateChanged(){
    if(kostyl) saveSetting();

}

void SettingWindow::on_textComand_textChanged(const QString &arg1){
    if(kostyl) saveSetting();

}
