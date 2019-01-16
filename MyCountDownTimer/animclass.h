#ifndef ANIMCLASS_H
#define ANIMCLASS_H
#include <QPropertyAnimation>
#include <settingwindow.h>
#include <mainwindow.h>

class MainWindow;
class SettingWindow;
class AnimClass

{
public:
    AnimClass();
    MainWindow * mMainWindow;


public slots:
    void runMainWindow();

};

#endif // ANIMCLASS_H
