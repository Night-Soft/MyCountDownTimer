#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLCDNumber>
#include <QTimer>
#include <QLabel>
#include <QProgressBar>
#include <QComboBox>
#include <mainwindow.h>
class MainWindow;


namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = 0);
    ~Dialog1();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void sigClose();

public:
    Ui::Dialog1 *ui;
    Dialog1 *dilog1;
    QTimer * tmrr;
    MainWindow *m;
    QProgressBar *progresBar;

public:
    QLabel *labelText;
    QLabel * labelText2;
    QComboBox * comboBoxStitching;
    int iiDouble = 0;

};

#endif // DIALOG_H
