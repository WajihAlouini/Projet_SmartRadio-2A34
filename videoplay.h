#ifndef VIDEOPLAY_H
#define VIDEOPLAY_H

#include <QDialog>
#include<QDebug>
namespace Ui {
class videoplay;
}

class videoplay : public QDialog
{
    Q_OBJECT

public:
    explicit videoplay(QWidget *parent = nullptr);
    ~videoplay();

private:
    Ui::videoplay *ui;
};

#endif // VIDEOPLAY_H
