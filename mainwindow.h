#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "invite.h"
#include <QAudioInput>
#include <QFile>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();


    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();



    void on_pb_recherche_clicked();

    void on_pb_pdf_clicked();

    void on_tab_invite_clicked(const QModelIndex &index);

    void on_pb_tri_id_clicked();



    void on_pb_tri_id_2_clicked();






    void on_start_micro_clicked();

    void on_stop_micro_clicked();



    void on_generate_enigme_clicked();
    void on_reponse_enigme_clicked();



    void on_pb_stat_clicked();

private:
    Ui::MainWindow *ui;
    invite I;
    QAudioInput *mAudioInput;
    QFile *MAudioFile;
};

#endif // MAINWINDOW_H
