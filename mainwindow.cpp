#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "invite.h"
#include <QMessageBox>
#include <QString>
#include <QRegularExpression>
#include <QPrinter>
#include <QPrintDialog>
#include <QDialog>
#include <QSqlQuery>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QIntValidator>
#include <QAudioRecorder>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDebug>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QMessageBox>


int idrandom;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // audioRecorder = new QAudioRecorder(this);
    ui->id_ajout->setValidator(new QIntValidator(100,99999999, this));
    ui->id_supp->setValidator(new QIntValidator(100,99999999, this));
    ui->id_modifier->setValidator(new QIntValidator(100,99999999, this));
    ui->id_recherche->setValidator(new QIntValidator(100,99999999, this));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{ int id=ui->id_ajout->text().toInt();
  int repetition=ui->rep_ajout->text().toInt();
  QDateTime datetime=ui->datetime_ajout->dateTime();
invite I(id,repetition,datetime);
    bool test=I.ajouter();
    if (test)
    {ui->tab_invite->setModel(I.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                              QObject::tr("Ajout effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);


              }
              else
                  QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    }








void MainWindow::on_pb_supprimer_clicked()
{
    invite I1;
    I1.setid(ui->id_supp->text().toInt());
    bool test=I1.supprimer(I1.getid());
    QMessageBox msgBox;
    if (test)
    {msgBox.setText("Suppression avec succes");
    ui->tab_invite->setModel(I1.afficher());}
    else msgBox.setText("Echec de suppression");
    msgBox.exec();
}
void MainWindow::on_pb_modifier_clicked()
{
     int repetition=ui->rep_modifier->text().toInt();
    int id=ui->id_modifier->text().toInt();
   QDateTime datetime=ui->datetime_modifier_2->dateTime();

     invite I2(id,repetition,datetime);
     bool test=I2.modifier();
    ;
;     if(test){
         QMessageBox::information(nullptr, QObject::tr(" OK"),
                     QObject::tr("modifier successful.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

     }
     else
     {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("modifier failed.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);}
     ui->tab_invite->setModel(I2.afficher());

}



void MainWindow::on_pb_recherche_clicked()
{
    invite I3;
        if (ui->id_recherche->text().length()>0){
            QString id=ui->id_recherche->text();
        ui->tab_recherche->setModel(I3.afficherech(id,1));}
        else if (ui->datetime_recherche->text().length()>0){
            QString id=ui->datetime_recherche->text();
            ui->tab_recherche->setModel(I3.afficherech(id,2));
        }
        else{
            QMessageBox::information(nullptr, QObject::tr(" OK"),
                        QObject::tr("les champs sont vide merci d'en remplire un"), QMessageBox::Cancel);

        }
}

void MainWindow::on_pb_pdf_clicked()
{QPrinter printer;
    printer.setPrinterName("printer name");
    QPrintDialog dialog(&printer,this);
    if(dialog.exec()==QDialog::Rejected)
    {

        return ;
    }
    else
        ui->pdf->print(&printer);
}


void MainWindow::on_tab_invite_clicked(const QModelIndex &index)
{
    QString val=ui->tab_invite->model()->data(index).toString();
  QSqlQuery qry;
    qry.prepare("select * from invite where ID=:val");
    qry.bindValue(":val",val);
    if (qry.exec())
    {
        while(qry.next())
        {


             ui->id_recherche->setText(qry.value(0).toString());
            ui->rep_ajout->setPrefix(qry.value(1).toString());
            ui->datetime_ajout->setDateTime(qry.value(2).toDateTime());

            QString s=(qry.value(0).toString()+"\n"+qry.value(1).toString()+"\n"+qry.value(2).toString()+"\n"+qry.value(3).toString());
            ui->pdf->setText(s);
        }
    }
        else
        {
           QMessageBox::warning(this,"error","no information");
        }
}


void MainWindow::on_pb_tri_id_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * from invite ORDER BY ID ASC");
    ui->tab_invite->setModel(model);
}



void MainWindow::on_pb_tri_id_2_clicked()
{QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * from invite ORDER BY ID DESC");
    ui->tab_invite->setModel(model);

}






void MainWindow::on_start_micro_clicked()
{invite I5;

   I5.playvideo();
}

void MainWindow::on_stop_micro_clicked()
{

    QMediaPlayer* player = new QMediaPlayer;
        QVideoWidget* vw= new QVideoWidget;
        player->setVideoOutput(vw);

        player->setMedia(QUrl("qrc:/Sound.mp4"));
        vw->setGeometry(100,100,300,400);
        vw->show();
        player->stop();


}


void MainWindow::on_reponse_enigme_clicked()
{QString rep;

    rep=ui->reponse->text();
   if(rep==I.rechercherep(idrandom)){
       QMessageBox::information(nullptr, QObject::tr("REPONSE"),
                   QObject::tr("Bonne reponse! Vous gagnez un bon d'achat de 50 dt!"), QMessageBox::Cancel);
   }else{QMessageBox::critical(nullptr, QObject::tr("REPONSE"),
                               QObject::tr("Mauvaise reponse vous perdez!"), QMessageBox::Cancel);}

}

void MainWindow::on_generate_enigme_clicked()
{
    idrandom=1 + (rand() % 4);
   ui->question->setText(I.recherchequestion(idrandom));
}

void MainWindow::on_pb_stat_clicked()
{
    QT_CHARTS_USE_NAMESPACE
                 MainWindow w;

                // Assign names to the set of bars used
                 QSqlQuery query;

        query.prepare("SELECT  count (ID) FROM invite ");
        query.exec();
            int a;
                while(query.next())
                {

                      a = query.value(0).toInt();//Récupère le résultat de la requête


                }

        QBarSet *set0 = new QBarSet("Nombre de repetition par invite");

       *set0 << 2 << 3 << 5 << 3 << 4 << a ;

        QBarSeries *series = new QBarSeries();
        series->append(set0);

        QChart *chart = new QChart();

        // Add the chart
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::AllAnimations);

        // Holds the category titles
        QStringList categories;

        categories<< "Janvier" << "Février" << "Mars"  << "Mai" << "Juin" << "Juillet" ;

        // Adds categories to the axes
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        chart->legend()->setAlignment(Qt::AlignBottom);



        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Used to change the palette
        QPalette pal = qApp->palette();

        // Change the color around the chart widget and text
        pal.setColor(QPalette::Window, QRgb(0xff9999));
        pal.setColor(QPalette::WindowText, QRgb(0x660000));

        // Apply palette changes to the application
        qApp->setPalette(pal);

        // Customize the title font
            QFont font;
            font.setPixelSize(40);
            chart->setTitleFont(font);
            chart->setTitleBrush(QBrush(Qt::cyan));
            chart->setTitle("Statistique de Repetition");

        QMainWindow window;


    setCentralWidget(chartView);}
