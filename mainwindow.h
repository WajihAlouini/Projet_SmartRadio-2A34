#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "personnel.h"
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "notepade.h"
  #include <notifications.h>
#include "ardouino.h"
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
    void on_pushButton_supprimer_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_recherche_clicked();
    void on_pushButton_tri_clicked();
    void on_pushButton_pdf_clicked();
    void on_pushButton_3_clicked();
    void on_notepadebt_clicked();
    void on_comboBox_activated(const QString &arg1);
    void on_comboBox_2_activated(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
void update_label();
private:
    Ui::MainWindow *ui;
    personnel per;
    QStringList files;
    QTcpSocket *socket;
    notepade *notepadee;
    notification N;
    QString fnct;
    ardouino A;
    QByteArray data ;
    QString serialBuffer;
};
#endif // MAINWINDOW_H
