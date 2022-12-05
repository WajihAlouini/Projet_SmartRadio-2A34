#ifndef NOTEPADE_H
#define NOTEPADE_H

#include <QMainWindow>
#include<QtCore>
#include<QtGui>

namespace Ui {
class notepade;
}

class notepade : public QMainWindow
{
    Q_OBJECT

public:
    explicit notepade(QWidget *parent = nullptr);
    ~notepade();

private slots:
    void on_actionSAVE_triggered();

    void on_actionOPEN_triggered();

    void on_actionSAVE_AS_triggered();

    void on_actionCOPY_triggered();

    void on_actionCUT_triggered();

    void on_actionUNDO_triggered();

    void on_actionREDO_triggered();

    void on_actionPASTE_triggered();

    void on_actionNEW_triggered();

private:
    Ui::notepade *ui;
    QString mFilename;
};

#endif // NOTEPADE_H
