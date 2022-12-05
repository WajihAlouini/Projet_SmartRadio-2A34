#include "salim.h"
#include "ui_salim.h"
#include "sponsor.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QComboBox>
#include <QTextStream>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QtDebug>
#include <QPdfWriter>
#include <QTextDocument>
#include <QPrintDialog>
#include <QTextDocument>
#include <QSqlQuery>
#include <QApplication>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPrinter>
#include <QPrintDialog>
#include <QTimer>
#include <QDateTime>
QT_CHARTS_USE_NAMESPACE


salim::salim(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salim)
{
    ui->setupUi(this);
    ui->tabspons->setModel(S.afficher());
       QTimer *timer=new QTimer(this);
       connect(timer ,SIGNAL(timeout()),this,SLOT(showtime()));
       timer->start();
       secc = 0;
       mint = 0;
       pause = false;
       connect(&reloj,SIGNAL(timeout()),this,SLOT(procesar()));
}

salim::~salim()
{
    delete ui;
}
void salim::on_bp_ajouter_clicked()
{
QString nom=ui->le_nom->text();
QString heure=ui->le_heure->text();
QString duree=ui->le_duree->text();
int repetition=ui->le_repet->currentText().toInt();
sponsor S(nom,heure,duree,repetition);
bool test=S.ajouter();


    if(test)
{

        //QMessageBox()::information(nullptr,QObject::tr("OK"),)

        QMessageBox::information( nullptr, QObject::tr("OK"),QObject::tr("ajout effectué \n" "click cancel to exit ."),QMessageBox::Cancel);
                 }else
            QMessageBox::critical ( nullptr,QObject::tr(" not OK"), QObject::tr("ajout  non effectué \n" "click cancel to exit ."),QMessageBox::Cancel);




}
void salim::on_bp_supprime_clicked()
{
    sponsor s1;s1.setnom(ui->le_nom_supp->text());
    bool test=s1.supprimer(s1.getnom());
    if(test)
{

        //QMessageBox()::information(nullptr,QObject::tr("OK"),)

        QMessageBox::information( nullptr, QObject::tr("OK"),QObject::tr("supprime effectué \n" "click cancel to exit ."),QMessageBox::Cancel);
    }else
        QMessageBox::critical ( nullptr,QObject::tr(" not OK"), QObject::tr("supprime  non effectué \n" "click cancel to exit ."),QMessageBox::Cancel);


    }

void salim::on_bp_modifier_clicked()
{
    QString nom=ui->le_nom->text();
    QString duree=ui->le_duree->text();
    QString heure=ui->le_heure->text();
    int repetition=ui->le_repet->currentText().toInt();
    sponsor s(nom,duree,heure,repetition);
    bool test=s.modifier(nom);
        if(test)
        { ui->tabspons->setModel(s.afficher());
     QMessageBox::information(nullptr, QObject::tr("modification avec succes"),
                 QObject::tr(" successful.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("erreur de modification"),
                    QObject::tr(" erreur.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}
void salim::on_bp_tri_clicked()
{
    ui->tabspons->setModel(S.afficherTri());
}
void salim::on_bp_rech_clicked()
{
    sponsor S;
    S.afficherRech(ui->le_rech->text(),ui->tabspons);
            ui->le_rech->setText("");
}
/*void MainWindow::on_bp_stat_clicked()
{
    s = new stat_combo();

  s->setWindowTitle("statistique ComboBox");
  s->choix_pie();
  s->show();

}*/
void salim::on_bp_pdf_clicked()
{
    QSqlDatabase db;
                   QTableView tabspons;
                   QSqlQueryModel * Modal=new  QSqlQueryModel();

                   QSqlQuery qry;
                    qry.prepare("SELECT * FROM sponsor ");
                    qry.exec();
                    Modal->setQuery(qry);
                   tabspons.setModel(Modal);



                    db.close();


                    QString strStream;
                    QTextStream out(&strStream);

                    const int rowCount = tabspons.model()->rowCount();
                    const int columnCount =  tabspons.model()->columnCount();


                    const QString strTitle ="Document";


                    out <<  "<html>\n"
                        "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg(strTitle)
                        <<  "</head>\n"
                        "<body bgcolor=#ffffff link=#5000A0>\n"
                       << QString("<h3 style=\" font-size: 32px; font-family: Arial, Helvetica, sans-serif; color: #FF9933; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des Clients")
                       <<"<br>"
                        <<"<table border=1 cellspacing=0 cellpadding=2>\n";

                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!tabspons.isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(tabspons.model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";

                    for (int row = 0; row < rowCount; row++) {
                        out << "<tr>";
                        for (int column = 0; column < columnCount; column++) {
                            if (!tabspons.isColumnHidden(column)) {
                                QString data = tabspons.model()->data(tabspons.model()->index(row, column)).toString().simplified();
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

void salim::on_bp_aller_clicked()
{
QSqlQuery q1,q2,q3,q4,q5;
    qreal tot=0,c1=0,c2=0,c3=0,c4=0;
    q1.prepare("Select * from sponsor");
    if(q1.exec())
    {
        while (q1.next())
        {
            tot++;
        }
    }
    q2.prepare("Select * from sponsor where repetition ='0'");
    if(q2.exec())
    {
        while (q2.next())
        {
            c1++;
        }
    }
    q3.prepare("Select * from sponsor where repetition ='1'");
    if(q3.exec())
    {
        while (q3.next())
        {
            c2++;
        }
    }
    q4.prepare("Select * from sponsor where repetition ='2'");
    if(q4.exec())
    {
        while (q4.next())
        {
            c3++;
        }
    }
    q5.prepare("Select * from sponsor where repetition ='3'");
    if(q5.exec())
    {
        while (q5.next())
        {
            c4++;
        }
    }
    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;
    c4=c4/tot;

    QPieSeries *series = new QPieSeries();
            series->append("0",c1);
            series->append("1",c2);
            series->append("2",c3);
            series->append("3",c4);
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
            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("REPETITION DE SPONSOR");
            chart->setAnimationOptions(QChart::AllAnimations);
            chart->legend()->hide();
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            QGridLayout *layout = new QGridLayout();
            layout->addWidget(chartView);
            ui->label_stat->setLayout(layout);
}
void salim::showtime()
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->digital_clock->setText(time_text);

}

void salim::on_bp_play_clicked()
{
    reloj.start(1000);
}

void salim::on_bp_pause_clicked()
{
    if (pause==false){
        reloj.stop();
        pause=true;
    }
    else{
        pause=false;
        reloj.start(1000);
    }
}

void salim::on_bp_stop_clicked()
{
    mint=0;
    secc=0;
    pause=false;
    ui->mint->display(mint);
    ui->secc->display(secc);
    reloj.stop();
}
void salim::procesar()
{
    secc=secc+1;
    if(secc==60)
    {secc=0;
        mint=mint+1;}
    else {
        ui->secc->display(secc);
        ui->mint->display(mint);
    }

}

