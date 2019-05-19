#include <QApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QScreen>
#include <QDesktopWidget>
#include <QPoint>
#include <QTranslator>
#include "mainwindow.h"
#include "screenrect.h"
#include "ui_mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load(":/languages/" + QLocale::system().name());
    a.installTranslator(&translator);
    MainWindow *w = new MainWindow();
    screenrect *rect = new screenrect();
    rect->windowCenter(w);
    return a.exec();
}
