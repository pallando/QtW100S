#include "workerthread.h"
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

Workerthread::Workerthread(QObject *parent) :
  QThread(parent)
{
}


bool Workerthread::getTurnedon() const
{
  return turnedon;
}

void Workerthread::setTurnedon(bool value)
{
  turnedon = value;
}


int Workerthread::getThrottle() const
{
  return throttle;
}

void Workerthread::setThrottle(int value)
{
  throttle = value;
}


int Workerthread::getElev() const
{
  return elev;
}

void Workerthread::setElev(int value)
{
  elev = value;
}


int Workerthread::getAile() const
{
  return aile;
}

void Workerthread::setAile(int value)
{
  aile = value;
}


int Workerthread::getRotation() const
{
  return rotation;
}

void Workerthread::setRotation(int value)
{
  rotation = value;
}

void Workerthread::run()
{
  QHostAddress host(QString("192.168.10.1"));
  QTcpSocket sock;
  sock.connectToHost(host,2001);

  while(turnedon)
  {
    char data[18];
    data[0] = 97;
    data[1] = throttle >> 8;
    data[2] = throttle;
    data[3] = rotation >> 8;
    data[4] = rotation;
    data[5] = elev >> 8;
    data[6] = elev;
    data[7] = aile >> 8;
    data[8] = aile;
    data[9] = aile >> 8;
    data[10] = aile;
    data[11] = throttle >> 8;
    data[12] = throttle;
    data[13] = rotation >> 8;
    data[14] = rotation;
    data[15] = elev >> 8;
    data[16] = elev;
    data[17] = 0;
    for(int i=0; i<17; ++i)
      data[17] += data[i];
    data[17] &= 255;
    sock.write(data,18);
    sock.waitForReadyRead(100);
  }
  sock.close();
}





