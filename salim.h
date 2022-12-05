#ifndef SALIM_H
#define SALIM_H
#include "sponsor.h"
#include <QTimer>
QT_BEGIN_NAMESPACE
#include <QDialog>

namespace Ui {
class salim;
}

class salim : public QDialog
{
    Q_OBJECT

public:
    explicit salim(QWidget *parent = nullptr);
    ~salim();
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
    Ui::salim *ui;
    sponsor S;
        short int mint;
        short int secc;
        bool pause;
        QTimer reloj;
};

#endif // SALIM_H
