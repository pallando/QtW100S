#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "workerthread.h"

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
    void turnedOn(bool on);
    void updateThrottle(int val);
    void updateElev(int val);
    void updateRotation(int val);
    void updateAile(int val);

  private:
    Ui::MainWindow *ui;
    Workerthread worker;
};

#endif // MAINWINDOW_H
