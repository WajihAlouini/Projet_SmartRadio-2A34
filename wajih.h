#ifndef WAJIH_H
#define WAJIH_H

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QAudioInput>
#include "invite.h"
#include <QTcpSocket>
#include <QAbstractSocket>
#include "notepade.h"
  #include <notifications.h>

#include "ui_wajih.h"

#include <QMainWindow>

namespace Ui {
class wajih;
}

class wajih : public QMainWindow
{
    Q_OBJECT

public:
    explicit wajih(QWidget *parent = nullptr);
    ~wajih();
private slots:

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


    QStringList files;
    QTcpSocket *socket;
    notepade *notepadee;
    notification N;
    QString fnct;
    invite I;
    QAudioInput *mAudioInput;
    QFile *MAudioFile;
    int idrandom;


    Ui::wajih *ui;
};

#endif // WAJIH_H
