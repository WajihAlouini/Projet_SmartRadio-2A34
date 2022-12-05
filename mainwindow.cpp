#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"personnel.h"
#include<QMessageBox>
#include<QIntValidator>
#include<QObject>
#include<QAbstractItemModel>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QtDebug>
#include <QDebug>
#include <QPdfWriter>
#include <QTextDocument>
#include <QPrintDialog>
#include <QSqlQuery>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <notepade.h>
#include <notifications.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
     ui->lineEdit_id->setValidator(new QIntValidator(100, 99999999, this));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int ID=ui->lineEdit_id->text().toInt();
     QString NOMP=ui->lineEdit_nom->text();
       QString PRENOM=ui->lineEdit_prenom->text();
     QString FONCTION=fnct;
        int SALAIRE=ui->lineEdit_salaire->text().toInt();
        personnel k (ID,NOMP,PRENOM,FONCTION,SALAIRE);
        bool test=k.ajouter();
        if(!test)
        {
        QMessageBox::critical( nullptr,QObject::tr(" not OK"), QObject::tr("ajout  non effectué \n" "click cancel to exit ."),QMessageBox::Cancel);

        }

           else{
            QMessageBox::information ( nullptr, QObject::tr(" OK"),QObject::tr("ajout  effectué \n" "click cancel to exit ."),QMessageBox::Cancel);
 ui->tableView->setModel(k.afficher());
 N.notification_ajout();

        }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int ID=ui->lineEdit_supp->text().toInt();
    bool test=per.supprimer(ID);
    if(test)
    {
        QMessageBox::information( nullptr, QObject::tr("OK"),QObject::tr("suppression effectué \n" "click cancel to exit ."),QMessageBox::Cancel);
    ui->tableView->setModel(per.afficher());
    N.notification_supprimer();
    }

    else
        {QMessageBox::critical ( nullptr,QObject::tr(" not OK"), QObject::tr("suppression non effectué \n" "click cancel to exit ."),QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_modifier_clicked()
{
    personnel pe;
           int ID=ui->id->text().toInt();
           QString NOMP=ui->nom->text();
           QString PRENOM=ui->prenom->text();
            QString FONCTION=fnct;
             int SALAIRE=ui->salaire->text().toInt();

            bool test=pe.modifier(ID,NOMP,PRENOM,FONCTION,SALAIRE);
            if (!test){
     QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                       QObject::tr("invite modifiée.\n"
                                 "Click ok to exit."), QMessageBox::Ok);
         ui->tableView->setModel(pe.afficher());


             N.notification_modifier();}

       else
           QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                       QObject::tr("echec de modifier !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);     
  }


void MainWindow::on_pushButton_tri_clicked()
{
    QSqlQueryModel*model =new QSqlQueryModel();
    model->setQuery("SELECT *FROM personnel ORDER BY NOMP");
    ui->tableView->setModel(model);

}

void MainWindow::on_pushButton_recherche_clicked()
{
    personnel per;

                 per.rechercher(ui->linerech->text(),ui->tableView);

         ui->linerech->setText("");

}



void MainWindow::on_pushButton_pdf_clicked()
{{
    QSqlDatabase db;
                    QTableView TableView;
                    QSqlQueryModel * Modal=new  QSqlQueryModel();

                    QSqlQuery qry;
                     qry.prepare("SELECT * FROM personnel ");
                     qry.exec();
                     Modal->setQuery(qry);
                    TableView.setModel(Modal);

                     db.close();


                     QString strStream;
                     QTextStream out(&strStream);

                     const int rowCount = TableView.model()->rowCount();
                     const int columnCount =  TableView.model()->columnCount();

                     const QString strTitle ="Document";

                     out <<  "<html>\n"
                         "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg(strTitle)
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"
                        << QString("<h3 style=\" font-size: 32px; font-family: Arial, Helvetica, sans-serif; color: #FF9933; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des personnels")
                        <<"<br>"
                         <<"<table border=1 cellspacing=0 cellpadding=2>\n";

                     out << "<thead><tr bgcolor=#f0f0f0>";
                     for (int column = 0; column < columnCount; column++)
                         if (!TableView.isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(TableView.model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!TableView.isColumnHidden(column)) {
                                 QString data = TableView.model()->data(TableView.model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table>\n"
                             "<br><br>"
                             //<< QString("<p><img src=":/img/aze.png"; width="200"; height="200";\">%1</p>\n")
                             <<"<br>"
                             <<"<table border=1 cellspacing=0 cellpadding=2>\n";


                         out << "<thead><tr bgcolor=#f0f0f0>";

                             out <<  "</table>\n"

                         "</body>\n"
                         "</html>\n";

                     QTextDocument *document = new QTextDocument();
                     document->setHtml(strStream);

                     QPrinter printer;
                     QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                     if (dialog->exec() == QDialog::Accepted) {

                         QLabel lab;
                          QPixmap pixmap(":/img/aze.png");
                         lab.setPixmap(pixmap);
                         QPainter painter(&lab);
                         //QPrinter printer(QPrinter::PrinterResolution);

                         //pixmap.load("aze.png");
                         //painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
                         //painter.drawPixmap(10,10,50,50, pixmap);

                         document->print(&printer);
                     }

                     printer.setOutputFormat(QPrinter::PdfFormat);
                     printer.setPaperSize(QPrinter::A4);
                     printer.setOutputFileName("/tmp/commandes.pdf");
                     printer.setPageMargins(QMarginsF(15, 15, 15, 15));



                     delete document;
}
}




void MainWindow::on_pushButton_3_clicked()
{
  ui->setupUi(this);
  QString fn1="cronequeure";
      QString fn2="technecien";
      QString fn3="personnel";
          QString fn4="technecien de son";
qreal f1=0,f2=0,f3=0,f4=0;
QSqlQuery q1,q2,q3,q4;
    q1.prepare("SELECT * FROM PERSONNEL WHERE FONCTION='"+fn1+"'" );

     if(q1.exec())
     {
         while (q1.next())
         {
             f1++;
         }
     }
     q2.prepare("SELECT * FROM PERSONNEL WHERE FONCTION='"+fn2+"'" );

      if(q2.exec())
      {
          while (q2.next())
          {
              f2++;
          }
      }
      q3.prepare("SELECT * FROM PERSONNEL WHERE FONCTION='"+fn3+"'" );

       if(q3.exec())
       {
           while (q3.next())
           {
               f3++;
           }
       }
       q4.prepare("SELECT * FROM PERSONNEL WHERE FONCTION='"+fn4+"'" );

        if(q4.exec())
        {
            while (q4.next())
            {
                f4++;
            }
        }
  qreal pourcentage1=(f1/(f1+f2+f3+f4)*100);
  qreal pourcentage2=(f2/(f1+f2+f3+f4)*100);
  qreal pourcentage3=(f3/(f1+f2+f3+f4)*100);
  qreal pourcentage4=(f4/(f1+f2+f3+f4)*100);



       QPieSeries *series =new  QPieSeries();
       series->append("cronequeure",pourcentage1);
         series->append("technecien",pourcentage2);
           series->append("personnel ",pourcentage3);
             series->append("technecien de son",pourcentage4);

QPieSlice *slice1 =series->slices().at(0);
slice1->setExploded();
     slice1->setLabelVisible();
     slice1->setPen(QPen(Qt::darkGreen, 2));
     slice1->setBrush(Qt::green);
QPieSlice *slice2 =series->slices().at(1);
slice2->setExploded();
    slice2->setLabelVisible();
    slice2->setPen(QPen(Qt::darkRed, 2));
    slice2->setBrush(Qt::red);
QPieSlice *slice3 =series->slices().at(2);

slice3->setExploded();
    slice3->setLabelVisible();
    slice3->setPen(QPen(Qt::darkYellow, 2));
    slice3->setBrush(Qt::yellow);
QPieSlice *slice4 =series->slices().at(3);

slice4->setExploded();
    slice4->setLabelVisible();
    slice4->setPen(QPen(Qt::darkBlue, 2));
    slice4->setBrush(Qt::blue);
               QChart *chart = new QChart();
               chart->addSeries(series);
                    chart->setTitle("Equipe du Radio");
                    chart->legend()->hide();
                     chart->setAnimationOptions(QChart::AllAnimations);


               QChartView *chartview =new QChartView(chart);
               chartview->setRenderHint(QPainter::Antialiasing);
               QGridLayout *layout = new QGridLayout();
                   layout->addWidget(chartview);
                   ui->statistique->setLayout(layout);

}

void MainWindow::on_notepadebt_clicked()
{
    notepadee = new notepade(this);
     notepadee->show();
}


void MainWindow::on_comboBox_2_activated(const QString &arg1)
{

}

void MainWindow::on_comboBox_activated(const QString &arg1)
{

}

void MainWindow::on_pushButton_4_clicked()//ouvrir
{
     A.write_to_ardouino("1");
}

void MainWindow::on_pushButton_5_clicked()//fermer
{
    A.write_to_ardouino("0");
}
void MainWindow::update_label()
{
    data=A.read_from_ardouino();
        QByteArray text=QByteArray::fromHex(data);
        QSqlQuery qry;
        serialBuffer  +=QString::fromStdString(data.toStdString());

        if( qry.exec("select * from PERSONNEL where ID like '"+serialBuffer+"%'")
                     )
        {
                             int count=0;
                             while(qry.next())
                                { count++;}
                         if(count==1)
                         {

                        QMessageBox::information(this,"porte","la porte est ouverte");
                     }
                         }
                         else
                         {
                            // QMessageBox::warning(this,"error","can't log in check informations");
            QMessageBox::warning(this,"error","error");
                         }
}

