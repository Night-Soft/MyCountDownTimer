#ifndef DIALOGNEW_H
#define DIALOGNEW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QCheckBox>

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QMainWindow
{
    Q_OBJECT

public:
    explicit DialogSettings(QWidget *parent = 0);
    ~DialogSettings();

public:
    Ui::DialogSettings *ui;
    QCheckBox * checkBoxDelay;
    QSpinBox * spinBoxDelay;
};

#endif // DIALOGNEW_H
