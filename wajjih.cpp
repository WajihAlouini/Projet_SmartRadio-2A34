#include "wajjih.h"
#include "ui_wajjih.h"
#include <QPrintDialog>
#include <QMultimedia>
#include <QVideoWidget>


wajjih::wajjih(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wajjih)
{
    ui->setupUi(this);
    ui->invite_ajout_id->setValidator(new QIntValidator(100,99999999, this));
    ui->invite_supprimer_id->setValidator(new QIntValidator(100,99999999, this));
    ui->invite_modifier_id->setValidator(new QIntValidator(100,99999999, this));
   ui->invite_rechercher_id->setValidator(new QIntValidator(100,99999999,this));
ui->tab_invite->setModel(I.afficher());
}

wajjih::~wajjih()
{
    delete ui;}
    void wajjih::on_invite_ajout_button_clicked()
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


    void wajjih::on_pb_invite_triASC_clicked()
    { QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("Select * from invite ORDER BY ID ASC");
        ui->tab_invite->setModel(model);

    }
    void wajjih::on_pb_invite_triDSC_clicked()
    {
        QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("Select * from invite ORDER BY ID DESC");
        ui->tab_invite->setModel(model);
    }
    void wajjih::on_invite_supprime_button_clicked()
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
    void wajjih::on_invite_modifier_button_clicked()
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
    void wajjih::on_invite_rechercher_button_clicked()
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
    void wajjih::on_invite_pdf_button_clicked()
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

    void wajjih::on_invite_stat_clicked()
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




    void wajjih::on_invite_micro_start_clicked()
    { invite I5;

        I5.playvideo();

    }

    void wajjih::on_invite_micro_stop_clicked()
    {
        QMediaPlayer* player = new QMediaPlayer;
            QVideoWidget* vw= new QVideoWidget;
            player->setVideoOutput(vw);

            player->setMedia(QUrl("qrc:/Sound.mp4"));
            vw->setGeometry(100,100,300,400);
            vw->show();
            player->stop();

    }

    void wajjih::on_invite_jeu_reponse_2_clicked()
    { QString rep;

        rep=ui->invite_jeu_reponse->text();
       if(rep==I.rechercherep(idrandom)){
           QMessageBox::information(nullptr, QObject::tr("REPONSE"),
                       QObject::tr("Bonne reponse! Vous gagnez un bon d'achat de 50 dt!"), QMessageBox::Cancel);
       }else{QMessageBox::critical(nullptr, QObject::tr("REPONSE"),
                                   QObject::tr("Mauvaise reponse vous perdez!"), QMessageBox::Cancel);}

    }

    void wajjih::on_invite_jeu_generate_clicked()
    {

        idrandom=1 + (rand() % 5);
       ui->invite_jeu_question->setText(I.recherchequestion(idrandom));
    }



    void wajjih::on_tab_invite_clicked(const QModelIndex &index)
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


}
