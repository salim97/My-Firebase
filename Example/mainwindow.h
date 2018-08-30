#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <firebase.h>
#include "rdv.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Firebase *m_firebase;
    RDV *rdv ;
};

#endif // MAINWINDOW_H
