#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PROJECT_ID "test-ccd18"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rdv = new RDV();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    rdv->update();
}
