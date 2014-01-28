#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

class Workerthread : public QThread
{
    Q_OBJECT
  public:
    explicit Workerthread(QObject *parent = 0);

    bool getTurnedon() const;
    void setTurnedon(bool value);

    int getThrottle() const;
    void setThrottle(int value);

    int getElev() const;
    void setElev(int value);

    int getAile() const;
    void setAile(int value);

    int getRotation() const;
    void setRotation(int value);

    void run();

  protected:
    bool turnedon;
    int throttle;
    int elev;
    int aile;
    int rotation;

  signals:

  public slots:

};

#endif // WORKERTHREAD_H
