#include "rana.h"
#include "ui_rana.h"
#include "emission.h"
#include "statistic.h"
#include <QMessageBox>
#include <QTextStream>
#include <QTextDocument>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QSqlQuery>
#include <QIntValidator>
#include <QtDebug>
#include<QObject>
#include "historique.h"

rana::rana(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::rana)
{
    ui->setupUi(this);
     ui->tableView->setModel(EM.afficher());
}

rana::~rana()
{
    delete ui;
}
void rana::on_pushButton_clicked()
{
    int id = ui->lineEdit_ID->text().toInt();
    QString nom = ui->lineEdit_Nom->text();
    QString heure = ui->lineEdit_Heure->text();
    QString type = ui->lineEdit_Type->text();
    int duree = ui->lineEdit_Duree->text().toInt();
    int nb_view = ui->lineEdit_NBView->text().toInt();

    int idh = ui->lineEdit_ID->text().toInt();
    QString nomh = ui->lineEdit_Nom->text();
    QString typeh = ui->lineEdit_Type->text();
    historique h(typeh,idh,nomh);
    h.Ajouter();

    Emission E(id, nom,heure,type,duree,nb_view );
    bool test = E.ajouter();

    if (test){
        ui->tableView->setModel(EM.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Ajout effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Ajouter non effectué"),
                              QMessageBox::Cancel
                              );
    }
}

void rana::on_pushButton_Supprimer_clicked()
{
    int id = ui->lineEdit_ID_2->text().toInt();
    bool test = EM.supprimer(id);

    if (test){
        ui->tableView->setModel(EM.afficher());
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("Suppression effectué"),
                              QMessageBox::Ok
                              );
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Suppression non effectué"),
                              QMessageBox::Cancel
                              );
    }
}


void rana::on_pushButton_2_clicked()
{
    Emission E2;
    int id = ui->lineEdit_ID_M->text().toInt();
    QString nom = ui->lineEdit_Nom_M->text();
    QString heure = ui->lineEdit_Heure_M->text();
    QString type = ui->lineEdit_Type_M->text();
    int duree = ui->lineEdit_Duree_M->text().toInt();
    int nb_view = ui->lineEdit_NBView_M->text().toInt();


    bool test = E2.modifier( id,nom,heure,type,duree,nb_view);
    if (test){

        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                              QObject::tr("modification effectué"),
                              QMessageBox::Ok
                              );
        ui->tableView->setModel(E2.afficher());
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("modification non effectué"),
                              QMessageBox::Cancel
                              );
    }
}



void rana::on_pushButton_Actualiser_clicked()
{
    ui->tableView->setModel(EM.afficher());

}



void rana::on_pushButton_Chercher_clicked()
{
    QString rech_field = ui->lineEdit_Recherche->text();
    ui->tableView->setModel(EM.recherche(rech_field));

}


void rana::on_pushButton_Trier__clicked()
{
    QString type_of_tri;
    QString tri_par;
    if (ui->radioButton_Tri_Asc->isChecked()){
        type_of_tri = "asc";
    }
    if (ui->radioButton_Tri_Desc->isChecked()){
        type_of_tri = "desc";
    }
    tri_par = ui->comboBox_Tri->currentText();
    ui->tableView->setModel(EM.trier(type_of_tri, tri_par));
}





void rana::on_pushButton_5_clicked()
{
    QSqlDatabase db;
                      QTableView tableView;
                      QSqlQueryModel * Modal=new  QSqlQueryModel();

                      QSqlQuery qry;
                       qry.prepare("SELECT * FROM EMISSION ");
                       qry.exec();
                       Modal->setQuery(qry);
                     tableView.setModel(Modal);



                       db.close();


                       QString strStream;
                       QTextStream out(&strStream);

                       const int rowCount = tableView.model()->rowCount();
                       const int columnCount =  tableView.model()->columnCount();


                       const QString strTitle ="Document";


                       out <<  "<html>\n"
                           "<head>\n"
                               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                           <<  QString("<title>%1</title>\n").arg(strTitle)
                           <<  "</head>\n"
                           "<body bgcolor=#ffffff link=#5000A0>\n"
                          << QString("<h3 style=\" font-size: 32px; font-family: Arial, Helvetica, sans-serif; color: #FF9933; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des emission")
                          <<"<br>"
                           <<"<table border=1 cellspacing=0 cellpadding=2>\n";

                       out << "<thead><tr bgcolor=#f0f0f0>";
                       for (int column = 0; column < columnCount; column++)
                           if (!tableView.isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(tableView.model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";

                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!tableView.isColumnHidden(column)) {
                                   QString data = tableView.model()->data(tableView.model()->index(row, column)).toString().simplified();
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












void rana::on_actionOpenTriggered()
{
    ui->setupUi(this);
    QPieSeries *series =new  QPieSeries();
           series->append("sport",20);
             series->append("politique",50);
               series->append("culture ",10);
                 series->append("cuisine",50);
                   series->append("kids",30);
    QPieSlice *slice =series->slices().at(1);
    slice->setExploded(true);
      slice->setLabelVisible(true);
       slice->setPen(QPen(Qt::darkGreen,2));
        slice->setBrush(Qt::green) ;
                   QChart *chart = new QChart();
                   chart->addSeries(series);
                   chart->setTitle("audiance des emissions");

                   QChartView *chartview =new QChartView(chart);
                   chartview->setParent(ui->horizontalFrame);

}

void rana::on_on_actionOpenTriggered_clicked()
{
    statistic = new class statistic(this);
    statistic->setWindowTitle("Smart Radio | Statistiques");
    statistic->show();
}

void rana::on_calendarWidget_selectionChanged()
{
    QString x=ui->calendarWidget->selectedDate().toString();
    QDate x1=ui->calendarWidget->selectedDate();
    ui->lineEdit_Calendrier->setText(x);
    ui->tableView_Calendar->setModel(EM.afficher_calendrier(x1));
}

void rana::on_pushButton_6_clicked()
{
    ui->tableView_hist->setModel(h.Afficher());
}

