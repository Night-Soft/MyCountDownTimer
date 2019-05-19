#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QDialog>
#include <QComboBox>
#include <QWidget>
#include <QSpinBox>
#include <string>
#include <ctime>
#include <QDateTime>
#include <QFrame>
#include <QPropertyAnimation>
#include <QSettings>
#include <QTime>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QPoint>
#include <QMouseEvent>
#include <QAction>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QDialogButtonBox>

class Dialog1;
class SettingWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

private slots:
    void on_buttonODialog_clicked();
    void on_setting_windowTitleChanged(const QString &title);
    void on_spinBoxMin_valueChanged(int arg1);
    void on_spinBoxHour_valueChanged(int arg1);
    void on_spinBoxSec_valueChanged(int arg1);
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBoxTime_currentIndexChanged(int index);
    void on_about_clicked();

public slots:
    void on_pushButton_clicked();
    void updateTime();
    void updateCurrentTime();
    void updateDialogTimeBox();
    void shutDown();
    void actionsClose();
    void setting_cliked();
    void dialogShow();
    void frameAnim();
    void saveSetting();
    void readSettings();
    void messageClickedd();
    void dialogRejected();
    void acceptDialog();
    void dialogClose();
    void settingCheckboxComand();
    void actionShow();
    void actionsUse();
    void actionsShutdown();
    void actionsReboot();
    void actionsSleep();
    void actionsHide();
    void timeStop();
    void settingWindowSpin();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_label_linkActivated(const QString &link);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

protected:
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject *pObject, QEvent *pEvent);
    void closeEvent(QCloseEvent *event);


private:
    bool mIsClickable = false;
    bool kostyl2 = false;
    bool timerIsRun = false;
    bool timerIsStart0 = false;
    bool timerIsStart1 = false;

public:
    Ui::MainWindow *ui;
    QPushButton *mbutton;
    QPushButton *mOpenDialBtn;
    QLabel *mlabel;
    QLabel * labelCurrentTime;
    QMainWindow *mWindow;
    QString *mString;
    QDialogButtonBox * mButtonBox;
    QTimer *tmr;
    QTimer *tmrCurrent;
    QComboBox * comboBox;
    QComboBox * comboboxTime;
    QSpinBox * spinBoxSec;
    QSpinBox * spinBoxMin;
    QSpinBox * spinBoxHour;
    QWidget * setting;
    QWidget * widgetTop;
    QWidget * widgetBottom;
    QWidget * widgetClose;
    QWidget * widgetMinDrop;
    Dialog1 *mdDialog1;
    QDateTime * dt;
    QFrame * frameGreen;
    QFrame *frameHourGlass;
    QPropertyAnimation *frameGreenAnim;
    QPropertyAnimation *framePinkAnim;
    QPropertyAnimation *widgetTopAnim;
    QPropertyAnimation *widgetBottomAnim;
    QPropertyAnimation *widgetMinDropAnim;
    QPropertyAnimation *hourAnimRotation;
    QTime *qCurrenttimer;
    QSystemTrayIcon *trayIcon;
    QMenu *qMenu;
    QPoint *qPointMouse;
    QMouseEvent *qMouseEvent;
    QAction * actClose;
    QAction * actShow;
    QAction * actShutdown;
    QAction * actReboot;
    QAction * actSleep;
    QAction * actHide;
    QMessageBox * messageBox;
    QDialogButtonBox * buttonbox;
    QSettings * settingsSave;
    QString spinBack;

    SettingWindow *settingWindow;
    Dialog1 * mDialog1;

    int ii = 0;
    int sum = 0;
    int hor = 0;
    int horDouble = 0;
    int min = 0;
    int minDouble = 0;
    int sec = 0;
    int kostyl = 1;
    int currentHour = 0;
    int currentMin = 0;
    int currentSec = 0;
    int sumCurrent = 0;
    int sixty = 60;
    int one = 1;
    int secB = 0;
    int minB = 0;
    int hourB = 0;
    int xPosition = 234;
    int yPosition = 235;
};

#endif // MAINWINDOW_H
