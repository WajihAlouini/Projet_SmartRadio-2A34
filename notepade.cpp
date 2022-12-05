#include "notepade.h"
#include "ui_notepade.h"
#include <QFileDialog>
notepade::notepade(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::notepade)
{
    ui->setupUi(this);
     this->setCentralWidget(ui->textEdit);
}

notepade::~notepade()
{
    delete ui;
}
void notepade::on_actionNEW_triggered()
{
  mFilename ="" ;
  ui->textEdit->setPlainText("");

}

void notepade::on_actionSAVE_triggered()
{
 QFile sFile(mFilename);
 if(sFile.open(QFile::WriteOnly | QFile::Text))
 {
     QTextStream out(&sFile);
     out << ui->textEdit->toPlainText();

   sFile.flush();
   sFile.close();

 }
}
void notepade::on_actionSAVE_AS_triggered()
{
    QString file= QFileDialog::getSaveFileName(this,"Open a file");
    if(!file.isEmpty())
    {
      QFile sFile(file);
      mFilename =file;
      on_actionSAVE_triggered();

    }
}
void notepade::on_actionOPEN_triggered()
{
 QString file= QFileDialog::getOpenFileName(this,"Open a file");
 if(!file.isEmpty())
 {
   QFile sFile(file);
   if(sFile.open(QFile::ReadOnly | QFile::Text))
   {
     QTextStream in (&sFile);
     QString text = in.readAll();
     sFile.close();
     ui->textEdit->setPlainText(text);


   }

 }
}
void notepade::on_actionCOPY_triggered()
{
  ui->textEdit->copy();
}

void notepade::on_actionCUT_triggered()
{
     ui->textEdit->cut();
}
void notepade::on_actionPASTE_triggered()
{
  ui->textEdit->paste();
}

void notepade::on_actionUNDO_triggered()
{
   ui->textEdit->undo();
}

void notepade::on_actionREDO_triggered()
{
   ui->textEdit->redo();
}



