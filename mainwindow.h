#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "emission.h"
#include "statistic.h"
#include "chatbox.h"
#include "qcustomplot.h"
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include "historique.h"
#include "arduino.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


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

    void on_label_11_linkActivated(const QString &link);

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();
     void update_label();


private:
    Ui::MainWindow *ui;
     void getChat();
     chatbox CB;


    Emission EM,ETU;
    Statistic *statistic;
    historique h;
    QByteArray data;
    Arduino A;

};
#endif // MAINWINDOW_H
