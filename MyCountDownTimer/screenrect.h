#ifndef SCREENRECT_H
#define SCREENRECT_H
#include <QMainWindow>
#include <QScreen>
#include <QDesktopWidget>
#include <QPoint>


class screenrect
{
public slots:
    void windowCenter(QMainWindow *qMainWindow);
public:
    screenrect();
};

#endif // SCREENRECT_H
