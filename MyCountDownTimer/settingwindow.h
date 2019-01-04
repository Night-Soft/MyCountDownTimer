#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>
#include <QFrame>
#include <QEvent>
#include <QPropertyAnimation>
#include <QVector>
#include <QSettings>
#include <QtCore>

#include <mainwindow.h>
#include <animclass.h>
class MainWindow;
class AnimClass;
class Dialog1;


namespace Ui {
class SettingWindow;
}

class SettingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = 0);
    ~SettingWindow();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void setImageSettin1Clickable();
    void setImageSettin2Clickable();
    void animSlideRight();
    void animSlideLeft();
    void dialogLeftClick();
    void autoRun();
    void dialogStyle();
    void saveSetting();
    void readSettings();

    void on_checkBoxDelay_stateChanged(int arg1);

    void on_checkBoxAutoRun_stateChanged(int arg1);

    void on_checkBoxCommand_stateChanged(int arg1);

    void on_spinBoxDelay_valueChanged(int arg1);

    void on_checkBoxTopLevel_stateChanged();

    void on_textComand_textChanged(const QString &arg1);

public slots:
    void userComand();


signals:
    void clicked();
    //void imagePress();
private:
    bool mIsClickable = true;
    bool kostyl = false;

protected:
    //void mousePressEvent(QMouseEvent* event);
    bool eventFilter(QObject *pObject, QEvent *pEvent);

public:
    Ui::SettingWindow *ui;
    QCheckBox * checkBoxDelay;
    QCheckBox * checkBoxCommand;
    QCheckBox * checkBoxTopLevel;
    QCheckBox * checkBoxAutoRun;
    QLabel * label;
    QLineEdit * textComand;
    QWidget * imageSettin1;
    QWidget * imageSettin2;

    QWidget * dialogCenter;
    QWidget * dialogLeft;
    QWidget * dialogRight;
    QWidget * dialogTop;
    QWidget * dialogTopLeft;
    QWidget * dialogTopRight;
    QWidget * dialogBottom;
    QWidget * dialogBottomLeft;
    QWidget * dialogBottomRight;
    //QWidget * dialogMassive;
    QVector <QWidget*> vectorMassive;
    QProcess *m_process;
    Dialog1 * dDialog1;



    QFrame * frame;
    QFrame * frame2;
    QPropertyAnimation *animation;
    QPropertyAnimation *animation2;
    QSettings * settingsSave;



    QSpinBox * spinBoxDelay;
    MainWindow * mainWindow;
    AnimClass * animClass;
    int enabled1 = 0;
    int enabled2 = 1;
    int delay = 0;
    int iWindow = 1;
    QString * stringBackDelay;

};

#endif // SETTINGWINDOW_H
