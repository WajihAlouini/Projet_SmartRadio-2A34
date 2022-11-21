#ifndef NOTPAD_H
#define NOTPAD_H

#include <QDialog>

namespace Ui {
class notpad;
}

class notpad : public QDialog
{
    Q_OBJECT

public:
    explicit notpad(QWidget *parent = nullptr);
    ~notpad();

private:
    Ui::notpad *ui;
};

#endif // NOTPAD_H
