#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "sponsor.h"
#include <QMainWindow>
#include <QTimer>
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

    void on_bp_ajouter_clicked();
    void on_bp_modifier_clicked();
    void on_bp_supprime_clicked();
    void on_bp_tri_clicked();
    void on_bp_rech_clicked();
    void on_bp_pdf_clicked();
    void on_bp_stat_clicked();
    void on_bp_aller_clicked();
    void showtime();

    void on_bp_play_clicked();

    void on_bp_pause_clicked();

    void on_bp_stop_clicked();

    void procesar();
private:
    Ui::MainWindow *ui;
    sponsor S;
    short int mint;
    short int secc;
    bool pause;
    QTimer reloj;
};
#endif // MAINWINDOW_H
