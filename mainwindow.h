#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "personnel.h"
#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include "smtp.h"
#include "invite.h"
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

    void on_invite_ajout_button_clicked();



    void on_invite_supprime_button_clicked();

    void on_pb_invite_triASC_clicked();

    void on_pb_invite_triDSC_clicked();

    void on_invite_pdf_button_clicked();

    void on_invite_stat_clicked();

    void on_invite_rechercher_button_clicked();

    void on_invite_modifier_button_clicked();

    void on_invite_micro_start_clicked();

    void on_invite_micro_stop_clicked();



    void on_invite_jeu_reponse_2_clicked();



    void on_tab_invite_clicked(const QModelIndex &index);

    void on_invite_jeu_generate_clicked();

private:
    Ui::MainWindow *ui;
    personnel per;
    QStringList files;
    QTcpSocket *socket;
    notepade *notepadee;
    notification N;
    QString fnct;
    invite I;
    QAudioInput *mAudioInput;
    QFile *MAudioFile;
    int idrandom;
};
#endif // MAINWINDOW_H
