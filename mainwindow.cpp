#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <xinput.h>
#include <math.h>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow), worker(parent), timer(parent)
{
  ui->setupUi(this);
  connect(&timer, SIGNAL(timeout()), this, SLOT(checkGamepad()));
  worker.setAile(ui->aile_slider->value());
  worker.setElev(ui->elev_slider->value());
  worker.setRotation(ui->rotation_slider->value());
  worker.setThrottle(ui->throttle_slider->value());
  worker.setTurnedon(ui->turnedOn->isChecked());
  timer.start(50);
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

void MainWindow::checkGamepad()
{
  int controllerNum = 0;
  XINPUT_STATE state;
  short LX = 0;
  short LY = 0;
  short RX = 0;
  short RY = 0;
//  BYTE LT = (BYTE) 0;
//  BYTE RT = (BYTE) 0;

  // Zeroise the state
  ZeroMemory(&state, sizeof(XINPUT_STATE));

  // Get the state
  DWORD Result = XInputGetState(controllerNum, &state);
  if(Result != ERROR_SUCCESS)
    ui->turnedOn->setChecked(false);
  else
  {
    LX = state.Gamepad.sThumbLX;
    LY = state.Gamepad.sThumbLY;
    RX = state.Gamepad.sThumbRX;
    RY = state.Gamepad.sThumbRY;
//    LT = state.Gamepad.bLeftTrigger;
//    RT = state.Gamepad.bRightTrigger;

    if(abs(LX) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
      LX = 0;
    if(abs(LY) < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
      LY = 0;

    if(abs(RX) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
      RX = 0;
    if(abs(RY) < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
      RY = 0;

//    if(abs(LT) < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
//      LT = 0;
//    if(abs(RT) < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
//      RT = 0;

    float normLX = (1.0 + fmaxf(-1, (float) LX / SHRT_MAX))/2;
    float normLY = (1.0 + fmaxf(-1, (float) LY / SHRT_MAX))/2;
    float normRX = (1.0 + fmaxf(-1, (float) RX / SHRT_MAX))/2;
    float normRY = (1.0 + fmaxf(-1, (float) RY / SHRT_MAX))/2;
    //float normLT = (1.0 + fmaxf(-1, (float) LT / 255))/2;
    //float normRT = (1.0 + fmaxf(-1, (float) RT / 255))/2;

    int minThrottle = ui->throttle_slider->minimum();
    int maxThrottle = ui->throttle_slider->maximum();
    ui->throttle_slider->setValue((minThrottle+normRY*(maxThrottle-minThrottle)));
    ui->statusBar->showMessage(QString::number(ui->throttle_slider->value()));

    int minRot = ui->rotation_slider->minimum();
    int maxRot = ui->rotation_slider->maximum();
    ui->rotation_slider->setValue(minRot + normRX*(maxRot-minRot));

    int minElev = ui->elev_slider->minimum();
    int maxElev = ui->elev_slider->maximum();
    ui->elev_slider->setValue(minElev + normLY*(maxElev-minElev));

    int minAile = ui->aile_slider->minimum();
    int maxAile = ui->aile_slider->maximum();
    ui->aile_slider->setValue(minAile + normLX*(maxAile-minAile));
  }
}
