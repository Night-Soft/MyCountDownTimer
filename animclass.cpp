#include "animclass.h"
#include "settingwindow.h"
#include <QScreen>
#include <QDesktopWidget>
#include <QPoint>

AnimClass::AnimClass()
{


}
void AnimClass::runMainWindow(){
 mMainWindow = new MainWindow();
 QDesktopWidget desktop;
     QRect  screenRect = desktop.availableGeometry(desktop.primaryScreen());
     QPoint center = screenRect.center();
     int x = center.x() - (mMainWindow->width()/2);  // учитываем половину ширины окна
     int y = center.y() - (mMainWindow->height()/2); // .. половину высоты
     center.setX(x);
     center.setY(y);
     mMainWindow->move(center);
 mMainWindow->show();
}
