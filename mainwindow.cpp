#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"personnel.h"
#include<QMessageBox>
#include<QIntValidator>
#include<QObject>
#include<QAbstractItemModel>
#include <QtPrintSupport/QPrinter>
#include <QPrinter>
#include <QPrintDialog>
#include <QtDebug>
#include <QDebug>
#include <QPdfWriter>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QTextDocument>
#include"alert.h"
#include "smtp.h"
#include <QSqlQuery>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <notepade.h>
#include <notifications.h>
#include "invite.h"
#include <QAudioRecorder>
#include <QMediaPlayer>
#include <QVideoWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   //for email tab
   connect(ui->envoyer, SIGNAL(clicked()),this, SLOT(sendMail()));
   connect(ui->browse, SIGNAL(clicked()), this, SLOT(browse()));
         ui->lineEdit_id->setValidator(new QIntValidator(100, 99999999, this));
     ui->tableView->setModel(per.afficher());
     //Controle de saisie (invite)
     ui->invite_ajout_id->setValidator(new QIntValidator(100,99999999, this));
     ui->invite_supprimer_id->setValidator(new QIntValidator(100,99999999, this));
     ui->invite_modifier_id->setValidator(new QIntValidator(100,99999999, this));
    ui->invite_rechercher_id->setValidator(new QIntValidator(100,99999999,this));
 ui->tab_invite->setModel(I.afficher());
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
        int alert=ui->lineEdit_alert->text().toInt();

        personnel k (ID,NOMP,PRENOM,FONCTION,SALAIRE,alert);
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
            QString FONCTION=ui->fonction->text();
             int SALAIRE=ui->salaire->text().toInt();
              int alert=ui->alert->text().toInt();
            bool test=pe.modifier(ID,NOMP,PRENOM,FONCTION,SALAIRE,alert);
            if (test){
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

void MainWindow::on_pushButton_4_clicked()
{
QString id=ui->lineEdit_alert->text();
    QSqlQuery Query;
    Query.prepare("select * FROM personnel where ID=:id and alert LIKE '%1%'");
     Query.bindValue(":id", id);
   alert  *cErr =new alert();
   if  (Query.next())
   {
       QMessageBox::information(nullptr, QObject::tr("micro  detecter"),
                   QObject::tr("micro  detecter.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);}
       else{
           QMessageBox::critical(nullptr, QObject::tr("micro non detecter"),
                       QObject::tr("micro non detecter.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

   }
}




void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("mohamedali.benromdhane1@esprit.tn","medali@@@","smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

   /* if( !files.isEmpty() )
    smtp->sendMail("mohamedali.benromdhane1@esprit.tn", ui->adresseMail->text() , ui->objet->text(),ui->message->toPlainText() );
    else
        smtp->sendMail("mohamedali.benromdhane1@esprit.tn", ui->adresseMail->text() , ui->objet->text(),ui->message->toPlainText());*/
}

void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->adresseMail->clear();
    ui->objet->clear();
    ui->file->clear();
    ui->message->clear();
   // ui->pass->clear();
}






/*
void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("rana.maknine@esprit.tn","211JFT0381.", "smtp.gmail.com",456);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("meriem.mghirbi@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("meriem.mghirbi@esprit.tn",ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
       // QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    {
        QSystemTrayIcon *notif = new QSystemTrayIcon;

        notif->showMessage("succes","message envoyé",QSystemTrayIcon::Information,1500);

    }
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}
*/
void MainWindow::on_notepadebt_clicked()
{
    notepadee = new notepade(this);
   notepadee->show();
}


   // connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));



void MainWindow::on_envoyer_clicked()
{
    Smtp* smtp = new Smtp("mohamedali.benromdhane1@esprit.tn","medali@@@","smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    fnct=arg1;
}
void MainWindow::on_invite_ajout_button_clicked()
{int id=ui->invite_ajout_id->text().toInt();
    int repetition=ui->invite_ajout_rep->text().toInt();
    QDateTime datetime=ui->invite_ajout_date->dateTime();
  invite I(id,repetition,datetime);
      bool test=I.ajouter();


      if (test)
      { ui->tab_invite->setModel(I.afficher());
          QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("Ajout effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);


                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                QObject::tr("Ajout non effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

      }


void MainWindow::on_pb_invite_triASC_clicked()
{ QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * from invite ORDER BY ID ASC");
    ui->tab_invite->setModel(model);

}
void MainWindow::on_pb_invite_triDSC_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select * from invite ORDER BY ID DESC");
    ui->tab_invite->setModel(model);
}
void MainWindow::on_invite_supprime_button_clicked()
{
    invite I1;
    I1.setid(ui->invite_supprimer_id->text().toInt());
    bool test=I1.supprimer(I1.getid());
    QMessageBox msgBox;
    if (test)
    {msgBox.setText("Suppression avec succes");
    ui->tab_invite->setModel(I1.afficher());}
    else msgBox.setText("Echec de suppression");
    msgBox.exec();
}
void MainWindow::on_invite_modifier_button_clicked()
{ int repetition=ui->invite_modifier_id->text().toInt();
    int id=ui->invite_modifier_rep->text().toInt();
    QDateTime datetime=ui->invite_modifier_date->dateTime();
    invite I2(id,repetition,datetime);
    bool test=I2.modifier();

       if(test){
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
void MainWindow::on_invite_rechercher_button_clicked()
{ invite I3;
    if (ui->invite_rechercher_id->text().length()>0){
        QString id=ui->invite_rechercher_id->text();
    ui->invite_tab_recherche->setModel(I3.afficherech(id,1));}
    else if (ui->invite_rechercher_id->text().length()>0){
        QString id=ui->invite_rechercher_date->text();
        ui->invite_tab_recherche->setModel(I3.afficherech(id,2));
    }
    else{
        QMessageBox::information(nullptr, QObject::tr(" OK"),
                    QObject::tr("les champs sont vide merci d'en remplire un"), QMessageBox::Cancel);

    }

}
void MainWindow::on_invite_pdf_button_clicked()
{
    QPrinter printer;
        printer.setPrinterName("printer name");
        QPrintDialog dialog(&printer,this);
        if(dialog.exec()==QDialog::Rejected)
        {

            return ;
        }
        else
            ui->invite_pdf->print(&printer);
}

void MainWindow::on_invite_stat_clicked()
{
    QSqlQuery q1,q2,q3,q4,q5;
        qreal tot=0,c1=0,c2=0,c3=0,c4=0;
        q1.prepare("Select * from invite");
        if(q1.exec())
        {
            while (q1.next())
            {
                tot++;
            }
        }
        q2.prepare("Select * from invite where REPETITIONS=:0");
        if(q2.exec())
        {
            while (q2.next())
            {
                c1++;
            }
        }
        q3.prepare("Select * from invite where REPETITIONS LIKE '%2%'");
        if(q3.exec())
        {
            while (q3.next())
            {
                c2++;
            }
        }
        q4.prepare("Select * from invite where REPETITIONS LIKE '%9%'");
        if(q4.exec())
        {
            while (q4.next())
            {
                c3++;
            }
        }
        q5.prepare("Select * from invite where REPETITIONSLIKE '%3%'");
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
                    series->append("2",c2);
                    series->append("9",c3);
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
                    chart->setTitle("Repetitions stats");
                    chart->setAnimationOptions(QChart::AllAnimations);
                    chart->legend()->hide();
                    QChartView *chartView = new QChartView(chart);
                    chartView->setRenderHint(QPainter::Antialiasing);
                    QGridLayout *layout = new QGridLayout();
                    layout->addWidget(chartView);
                    ui->invite_stat_label->setLayout(layout);

}




void MainWindow::on_invite_micro_start_clicked()
{ invite I5;

    I5.playvideo();

}

void MainWindow::on_invite_micro_stop_clicked()
{
    QMediaPlayer* player = new QMediaPlayer;
        QVideoWidget* vw= new QVideoWidget;
        player->setVideoOutput(vw);

        player->setMedia(QUrl("qrc:/Sound.mp4"));
        vw->setGeometry(100,100,300,400);
        vw->show();
        player->stop();

}

void MainWindow::on_invite_jeu_reponse_2_clicked()
{ QString rep;

    rep=ui->invite_jeu_reponse->text();
   if(rep==I.rechercherep(idrandom)){
       QMessageBox::information(nullptr, QObject::tr("REPONSE"),
                   QObject::tr("Bonne reponse! Vous gagnez un bon d'achat de 50 dt!"), QMessageBox::Cancel);
   }else{QMessageBox::critical(nullptr, QObject::tr("REPONSE"),
                               QObject::tr("Mauvaise reponse vous perdez!"), QMessageBox::Cancel);}

}

void MainWindow::on_invite_jeu_generate_clicked()
{

    idrandom=1 + (rand() % 5);
   ui->invite_jeu_question->setText(I.recherchequestion(idrandom));
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


             ui->invite_ajout_id->setText(qry.value(0).toString());
            ui->invite_ajout_rep->setPrefix(qry.value(1).toString());
            ui->invite_ajout_date->setDateTime(qry.value(2).toDateTime());

            QString s=(qry.value(0).toString()+"\n"+qry.value(1).toString()+"\n"+qry.value(2).toString()+"\n"+qry.value(3).toString());
            ui->invite_pdf->setText(s);
        }
    }
        else
        {
           QMessageBox::warning(this,"error","no information");
        }
}

