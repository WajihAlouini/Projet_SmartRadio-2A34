#ifndef STATISTIC_H
#define STATISTIC_H

#include <QDialog>

namespace Ui {
class statistic;
}

class statistic : public QDialog
{
    Q_OBJECT

public:
    explicit statistic(QWidget *parent = nullptr);
    ~statistic();
   statistic(QVector<double>* ticks,QVector<QString> *labels);
      void MakeStat();
private:
    Ui::statistic *ui;
};

#endif // STATISTIC_H
