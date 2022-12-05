#ifndef RANA_H
#define RANA_H
#include "emission.h"
#include "statistic.h"

#include "qcustomplot.h"
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include "historique.h"

#include <QMainWindow>


namespace Ui {
class rana;
}

class rana : public QMainWindow
{
    Q_OBJECT

public:
    explicit rana(QWidget *parent = nullptr);
    ~rana();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_Supprimer_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_Actualiser_clicked();
    void on_pushButton_Chercher_clicked();
    void on_pushButton_Trier__clicked();

    void on_pushButton_5_clicked();




    void on_actionOpenTriggered();



    void on_pushButton_7_clicked();


    void on_on_actionOpenTriggered_clicked();

    void on_calendarWidget_selectionChanged();

    void on_pushButton_6_clicked();

private:
    Ui::rana *ui;
     void getChat();

    Emission EM,ETU;
    statistic *statistic;
    historique h;


};

#endif // RANA_H
