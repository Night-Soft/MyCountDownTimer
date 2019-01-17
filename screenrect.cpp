#include "screenrect.h"

screenrect::screenrect()
{

}
void screenrect::windowCenter(QMainWindow *qMainWindow){
    QDesktopWidget desktop;
    QRect  screenRect = desktop.availableGeometry(desktop.primaryScreen());
    QPoint center = screenRect.center();
    int x = center.x() - (qMainWindow->width()/2);  
    int y = center.y() - (qMainWindow->height()/2);
    center.setX(x);
    center.setY(y);
    qMainWindow->move(center);
    qMainWindow->show();
}
