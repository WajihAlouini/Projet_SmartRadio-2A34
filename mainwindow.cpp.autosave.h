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
#include <QPdfWriter>
#include <QTextDocument>
#include <QPrintDialog>
#include <QChart>
#include <QChartView>
#include <QPieSlice>
#include <QPieSeries>
#include <QGridLayout>
#include <QtCharts/QChartView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_id->setValidator(new QIntValidator(100, 99999999, this));
    ui->tableView->setModel(per.afficher());
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
     QString FONCTION=ui->lineEdit_fonction->text();
        int SALAIRE=ui->lineEdit_salaire->text().toInt();

        personnel k (ID,NOMP,PRENOM,FONCTION,SALAIRE);
        bool test=k.ajouter();
        if(!test)
        {
        QMessageBox::information( nullptr,QObject::tr(" not OK"), QObject::tr("ajout  non effectué \n" "click cancel to exit ."),QMessageBox::Cancel);

        }
           else{
            QMessageBox::critical ( nullptr, QObject::tr(" OK"),QObject::tr("ajout  effectué \n" "click cancel to exit ."),QMessageBox::Cancel);
 ui->tableView->setModel(k.afficher());
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
            QString FONCTION=ui->fonction->text();
             int SALAIRE=ui->salaire->text().toInt();

            bool test=pe.modifier(ID,NOMP,PRENOM,FONCTION,SALAIRE);
            if (test){
     QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),
                       QObject::tr("invite modifiée.\n"
                                 "Click ok to exit."), QMessageBox::Ok);
         ui->tableView->setModel(pe.afficher());

     }
       else
           QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),
                       QObject::tr("echec de modifier !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);     
  }


void MainWindow::on_pushButton_tri_clicked()
{
    ui->tableView->setModel(per.trierpersonnel());
}

void MainWindow::on_pushButton_recherche_clicked()
{
    personnel per;

                 per.rechercher(ui->linerech->text(),ui->tableView);;

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
    ui->tabWidget->show();
        ui->tabWidget->setCurrentIndex(4);
        QSqlQuery q1,q2,q3,q4,q5,q6;
        qreal tot=0,c1=0,c2=0,c3=0,c4=0,c5=0;
        q1.prepare("Select * from Hotel");
        if(q1.exec())
        {
            while (q1.next())
            {
                tot++;
            }
        }
        q2.prepare("Select * from personnel where fonction ='1'");
        if(q2.exec())
        {
            while (q2.next())
            {
                c1++;
            }
        }
        q3.prepare("Select * from personnel where fonction ='2'");
        if(q3.exec())
        {
            while (q3.next())
            {
                c2++;
            }
        }
        q4.prepare("Select * from personnel where fonction ='3'");
        if(q4.exec())
        {
            while (q4.next())
            {
                c3++;
            }
        }
        q5.prepare("Select * from personnel where fonction ='4'");
        if(q5.exec())
        {
            while (q5.next())
            {
                c4++;
            }
        }
        q6.prepare("Select * from personnel where fonction ='5'");
        if(q6.exec())
        {
            while (q6.next())
            {
                c5++;
            }
        }
        c1=c1/tot;
        c2=c2/tot;
        c3=c3/tot;
        c4=c4/tot;
        c5=c5/tot;
        QPieSeries *series = new QPieSeries();
                series->append("1",c1);
                series->append("2",c2);
                series->append("3",c3);
                series->append("4",c4);
                series->append("5",c5);
                QPieSlice *slice0 = series->slices().at(0);
                slice0->setExploded();
                slice0->setLabelVisible();
                slice0->setPen(QPen(Qt::darkGray, 2));
                slice0->setBrush(Qt::gray);
                QPieSlice *slice1 = series->slices().at(1);
                slice1->setExploded();
                slice1->setLabelVisible();
                slice1->setPen(QPen(Qt::darkRed, 2));
                slice1->setBrush(Qt::red);
                QPieSlice *slice2 = series->slices().at(2);
                slice2->setExploded();
                slice2->setLabelVisible();
                slice2->setPen(QPen(Qt::darkYellow, 2));
                slice2->setBrush(Qt::yellow);
                QPieSlice *slice3 = series->slices().at(3);
                slice3->setExploded();
                slice3->setLabelVisible();
                slice3->setPen(QPen(Qt::darkGreen, 2));
                slice3->setBrush(Qt::green);
                QPieSlice *slice4 = series->slices().at(4);
                slice4->setExploded();
                slice4->setLabelVisible();
                slice4->setPen(QPen(Qt::blue, 2));
                slice4->setBrush(Qt::cyan);
                QChart *chart = new QChart();
                chart->addSeries(series);
                chart->setTitle("MOST CLASSES SAVED");
                chart->setAnimationOptions(QChart::AllAnimations);
                chart->legend()->hide();
                
                QChartView() *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                QGridLayout *layout = new QGridLayout();
                layout->addWidget(chartView);
                ui->statistiques->setLayout(layout);
}
