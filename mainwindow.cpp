#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  worker.setAile(ui->aile_slider->value());
  worker.setElev(ui->elev_slider->value());
  worker.setRotation(ui->rotation_slider->value());
  worker.setThrottle(ui->throttle_slider->value());
  worker.setTurnedon(ui->turnedOn->isChecked());
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::turnedOn(bool on)
{
  worker.setTurnedon(on);
  worker.start();
}

void MainWindow::updateThrottle(int val)
{
  worker.setThrottle(val);
}

void MainWindow::updateElev(int val)
{
  worker.setElev(val);
}

void MainWindow::updateRotation(int val)
{
  worker.setRotation(val);
}

void MainWindow::updateAile(int val)
{
  worker.setAile(val);
}
