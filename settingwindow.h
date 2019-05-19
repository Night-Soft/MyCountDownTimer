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
#include <dialog.h>

class MainWindow;
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
    void setImageSettin1Clickable();
    void setImageSettin2Clickable();
    void animSlideRight();
    void animSlideLeft();
    void dialogLeftClick();
    void autoRun();
    void dialogStyle();
    void saveSetting();
    void readSettings();

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
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

private:
    bool mIsClickable = true;
    bool kostyl = false;

protected:
    bool eventFilter(QObject *pObject, QEvent *pEvent);

public:
    Ui::SettingWindow *ui;
    QCheckBox * checkBoxDelay;
    QCheckBox * checkBoxCommand;
    QCheckBox * checkBoxTopLevel;
    QCheckBox * checkBoxAutoRun;

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
    QProcess *m_process;
    QString * stringBackDelay;
    QSpinBox * spinBoxDelay;
    QLabel * label;
    QLineEdit * textComand;
    QVector <QWidget*> vectorMassive;

    QFrame * frame;
    QFrame * frame2;
    QPropertyAnimation *animation;
    QPropertyAnimation *animation2;
    QSettings * settingsSave;
    MainWindow * mainWindow;
    Dialog1 * dDialog1;

    int enabled1 = 0;
    int enabled2 = 1;
    int delay = 0;
    int iWindow = 1;

};

#endif // SETTINGWINDOW_H
