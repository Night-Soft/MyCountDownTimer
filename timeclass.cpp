#include <QTime>
#include <QTimer>
#include <QDialog>
#include <dialog.h>
#include <QMainWindow>
#include <mainwindow.h>


void startTimer(QTimer qtimer)
{
   //qtimer = new QTimer();
    QDialog *di = new Dialog1();
    QMainWindow *qma = new MainWindow();

   qtimer.start(1000);
   qtimer.start();
}
