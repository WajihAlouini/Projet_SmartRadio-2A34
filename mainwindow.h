#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "personnel.h"
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include "smtp.h"
#include <QTcpSocket>
#include <QAbstractSocket>
#include "notepade.h"
  #include <notifications.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_recherche_clicked();
    void on_pushButton_tri_clicked();
    void on_pushButton_pdf_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void sendMail();
    void mailSent(QString);
    void browse();
    void on_notepadebt_clicked();

    //void on_sendBtn_clicked();

    void on_envoyer_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    personnel per;
    QStringList files;
    QTcpSocket *socket;
    notepade *notepadee;
    notification N;
    QString fnct;
};
#endif // MAINWINDOW_H