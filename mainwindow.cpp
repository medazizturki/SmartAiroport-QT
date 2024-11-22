
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employes.h"
#include "avion.h"
#include "emplacement.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QApplication>
#include <QPixmap>

#include <QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include<QtCharts>

#include<QPieSlice >
#include<QPieSeries>
#include<QPrinter>
#include <QFileDialog>
#include<QPrintDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget_integration->setCurrentIndex(0);

////////////////Employe
    QPixmap pic_Employe("C:/Users/21698/Desktop/employe/photo_Login_Qt");
    ui->label_photo_Employe->setPixmap(pic_Employe);
    ui->lineEdit_CIN->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_Num_Tel->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_Nom->setMaxLength(8);
    ui->lineEdit_Prenom->setMaxLength(8);
    ui->lineEdit_Adress->setMaxLength(8);



////////////////Avion
    QPixmap pic_avion("C:/Users/21698/Desktop/employe/photo_Login_Qt");
    ui->label_photo_avion->setPixmap(pic_avion);
    ui->lineEdit_codeavion->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_departavion->setMaxLength(8);
    ui->lineEdit_arriveeavion->setMaxLength(8);
    ui->lineEdit_dureevolavion->setMaxLength(8);
    ui->lineEdit_prixavion->setMaxLength(8);
    ui->lineEdit_nbplaceavion->setValidator(new QIntValidator(0, 99999999, this));



////////////////Emplacement
    QPixmap pic_Emplacement("C:/Users/21698/Desktop/employe/photo_Login_Qt");
    ui->label_photo_Emplacement->setPixmap(pic_Emplacement);
    ui->lineEdit_num->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_nom_emplacement->setMaxLength(8);
    ui->lineEdit_dimension->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_reservation->setMaxLength(8);
    ui->lineEdit_liberation->setMaxLength(8);


////////////////////////// Commande
    QPixmap pic_Commande("C:/Users/21698/Desktop/employe/photo_Login_Qt");
    ui->label_photo_pagecommande->setPixmap(pic_Commande);

//////////////////////// Login
    QPixmap pic_Login("C:/Users/21698/Desktop/employe/photo_Login_Qt");
    ui->label_photo_Login->setPixmap(pic_Login);






    //*********************************************************************************
    int ret=a.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< a.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<a.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
     //*********************************************************************************

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label()
{
    data=a.read_from_arduino();

    if(data=="1")

        a.write_to_arduino("2");
    else if (data=="0")

        a.write_to_arduino("2");  }


//******************************************************************************************************

void MainWindow::on_pushButton_gestion_employer_clicked()
{
    ui->stackedWidget_integration->setCurrentIndex(3);
}

void MainWindow::on_pushButton_gestion_avion_clicked()
{
    ui->stackedWidget_integration->setCurrentIndex(4);
}

void MainWindow::on_pushButton_emplacement_clicked()
{
    ui->stackedWidget_integration->setCurrentIndex(2);
}

void MainWindow::on_pushButton_retour_employer_clicked()
{
    ui->stackedWidget_integration->setCurrentIndex(1);
}

void MainWindow::on_pushButton_retour_avion_clicked()
{
    ui->stackedWidget_integration->setCurrentIndex(1);
}

void MainWindow::on_pushButton_retour_emplacement_clicked()
{
    ui->stackedWidget_integration->setCurrentIndex(1);
}

/******************************************************************************************************************/



/**********************************************************************************************************************/

/**********************************************************************************************************************/

/**********************************************************************************************************************/
/**************************************************Employer************************************************************/
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/**********************************************************************************************************************/


void MainWindow::on_pushButton_Ajouter_clicked()
{
    int CIN=ui->lineEdit_CIN->text().toInt(); //convertir en entier
    QString nom=ui->lineEdit_Nom->text();
    QString prenom=ui->lineEdit_Prenom->text();
    QString sexe=ui->comboBox_Sexe->currentText();
    QDate date_naissance=ui->dateEdit_naissance->date();
    int num_tel=ui->lineEdit_Num_Tel->text().toInt();
    QString email=ui->lineEdit_Email->text();
    QString adress=ui->lineEdit_Adress->text();
    Employe E(CIN,nom,prenom,sexe,date_naissance,num_tel,email,adress);
        bool test=E.ajouterEmploye();
        if(test)
              {    QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                                            QObject::tr("ajout successful.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);
                             ui->table_employe->setModel(E.afficherEmploye());
              }
                            else
                                QMessageBox::critical(nullptr, QObject::tr("Ajout errer"),
                                            QObject::tr("ajout failed.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

             ui->lineEdit_CIN->clear();
             ui->lineEdit_Nom->clear();
             ui->lineEdit_Prenom->clear();
             ui->comboBox_Sexe->setCurrentIndex(0);
             ui->dateEdit_naissance->clear();
             ui->lineEdit_Num_Tel->clear();
             ui->lineEdit_Email->clear();
             ui->lineEdit_Adress->clear();
}



/******************************************************************************************************************/



void MainWindow::on_pushButton_Afficher_clicked()
{
    ui->table_employe->setModel(E.afficherEmploye());
}



/******************************************************************************************************************/



void MainWindow::on_pushButton_Supprimer_clicked()
{
    Employe E1;
    E1.setCIN(ui->lineEdit_CIN->text().toInt());
    bool test=E1.supprimerEmploye(E1.getCIN());
    QMessageBox msgBox;
    if (ui->lineEdit_CIN->text()=="")
    {
        QMessageBox::critical(this, QObject::tr("Suppression Errer"),
                           QObject::tr("Echec de Suppression!!!\n""Veuillez remplir la label de CIN"), QMessageBox::Cancel);
    }
    else if (test)
    {
        QMessageBox::information(this, QObject::tr("Suppression avec Succes"),
                           QObject::tr("Suppression avec succes"), QMessageBox::Cancel);
        ui->table_employe->setModel(E.afficherEmploye());
    }
    ui->lineEdit_CIN->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_Prenom->clear();
    ui->comboBox_Sexe->setCurrentIndex(0);
    ui->dateEdit_naissance->clear();
    ui->lineEdit_Num_Tel->clear();
    ui->lineEdit_Email->clear();
    ui->lineEdit_Adress->clear();
}



/******************************************************************************************************************/



void MainWindow::on_pushButton_MIseAJour_clicked()
{
    int CIN=ui->lineEdit_CIN->text().toInt();
    QString nom=ui->lineEdit_Nom->text();
    QString prenom=ui->lineEdit_Prenom->text();
    QString sexe=ui->comboBox_Sexe->currentText();
    QDate date_naissance=ui->dateEdit_naissance->date();
    int num_tel=ui->lineEdit_Num_Tel->text().toInt();
    QString email=ui->lineEdit_Email->text();
    QString adress=ui->lineEdit_Adress->text();

    Employe E(CIN,nom,prenom,sexe,date_naissance,num_tel,email,adress);

    bool test=E.modifierEmploye(E.getCIN(),E.getnom(),E.getprenom(),E.getsexe(),E.getdate_naissance(),E.getnum_tel(),E.getemail(),E.getadress());

    QMessageBox msgBox;

    if ((ui->lineEdit_CIN->text()==0),(ui->lineEdit_Nom->text()==""),(ui->lineEdit_Prenom->text()==""),(ui->comboBox_Sexe->currentText()==""),(ui->lineEdit_Num_Tel->text()==0),(ui->lineEdit_Email->text()==""),(ui->lineEdit_Adress->text()==""))
    {
        QMessageBox::critical(this, QObject::tr("Modification Errer"),
                           QObject::tr("Echec de Modification!!!\n""Veuillez remplir tous le champs"), QMessageBox::Cancel);

    }
    else if(test)
    {
        QMessageBox::information(this, QObject::tr("Modification Succes"),
                           QObject::tr("Modifications avec Succes"), QMessageBox::Cancel);
        ui->table_employe->setModel(E.afficherEmploye());

    }
    ui->lineEdit_CIN->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_Prenom->clear();
    ui->comboBox_Sexe->setCurrentIndex(0);
    ui->dateEdit_naissance->clear();
    ui->lineEdit_Num_Tel->clear();
    ui->lineEdit_Email->clear();
    ui->lineEdit_Adress->clear();
}



/**********************************************************************************************************************/

/******************************************************Metiers*********************************************************/

/**********************************************************************************************************************/



void MainWindow::on_lineEdit_recherche_textChanged()
{
    QString rech=ui->lineEdit_recherche->text();
    ui->table_employe->setModel(E.RechercheEmploye(rech));
}



/****************************************************************************************/




void MainWindow::on_comboBox_tri_activated()
{
    if(ui->comboBox_tri->currentText()=="Tri par CIN Monatnt")
    {
        ui->table_employe->setModel(E.trierEmployeParCIN_M());

    }else if(ui->comboBox_tri->currentText()=="Tri par CIN Descendant")
    {
        ui->table_employe->setModel(E.trierEmployeParCIN_D());

    }else if(ui->comboBox_tri->currentText()=="Tri par Nom")
    {
        ui->table_employe->setModel(E.trierEmployeParNom());
    }else
    {

        ui->table_employe->setModel(E.trierEmployeParDate());
    }
}



/**********************************************************************************************************************/



void MainWindow::on_pushButton_Reset_clicked()
{
    Employe E1;
    bool test=E1.supprimerTout();
    QMessageBox msgBox;
         if(test)
          {    QMessageBox::information(nullptr, QObject::tr("Reset avec succes"),
                                        QObject::tr("Reset successful.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
                         ui->table_employe->setModel(E.afficherEmploye());
          }
                        else
                            QMessageBox::critical(nullptr, QObject::tr("Reset errer"),
                                        QObject::tr("Reset failed.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
}



/**********************************************************************************************************************/



void MainWindow::on_pushButton_PDF_clicked()
{
    QPdfWriter pdf("C:\\Users\\21698\\Desktop\\PDF_Projet\\PDF_Employe.pdf");

   QPainter painter(&pdf);
   int i = 4000;
          painter.setPen(Qt::red);
          painter.setFont(QFont("Time New Roman", 25));
          painter.drawText(3000,1400,"Liste Des Employes");
          painter.setPen(Qt::black);
          painter.setFont(QFont("Time New Roman", 15));
          painter.drawRect(100,3000,9400,500);
          painter.setFont(QFont("Time New Roman", 9));
          painter.drawText(400,3300,"CIN");
          painter.drawText(1350,3300,"Nom");
          painter.drawText(2200,3300,"Prenom");
          painter.drawText(3400,3300,"Sexe");
          painter.drawText(4400,3300,"Date de Naissance");
          painter.drawText(6200,3300,"Numero de Tel");
          painter.drawText(7600,3300,"Email");
          painter.drawText(8500,3300,"Adress");
          painter.drawRect(100,3000,9400,9000);

          QSqlQuery query;
          query.prepare("select * from EMPLOYE");
          query.exec();
          while (query.next())
          {
              painter.drawText(400,i,query.value(0).toString());
              painter.drawText(1350,i,query.value(1).toString());
              painter.drawText(2300,i,query.value(2).toString());
              painter.drawText(3400,i,query.value(3).toString());
              painter.drawText(4400,i,query.value(4).toString());
              painter.drawText(6200,i,query.value(5).toString());
              painter.drawText(7600,i,query.value(6).toString());
              painter.drawText(8500,i,query.value(7).toString());


             i = i + 350;
          }
          QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
          QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}



/**********************************************************************************************************************/




void MainWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
           QString password = ui->lineEdit_password->text();

           if (username == "admin" && password == "admin") {
               QMessageBox::information(this, "Login", "Username and password are correct");
            ui->stackedWidget_integration->setCurrentIndex(1);
            a.write_to_arduino("1");

           }
           else {
               QMessageBox::warning(this, "Login", "Username and password are not correct");
               a.write_to_arduino("0");
           }
           ui->lineEdit_username->clear();
           ui->lineEdit_password->clear();
}



/**********************************************************************************************************************/



void MainWindow::on_table_employe_clicked(const QModelIndex &index)
{
    ui->lineEdit_CIN->setText(ui->table_employe->model()->data(ui->table_employe->model()->index(index.row(),0)).toString());
    ui->lineEdit_Nom->setText(ui->table_employe->model()->data(ui->table_employe->model()->index(index.row(),1)).toString());
    ui->lineEdit_Prenom->setText(ui->table_employe->model()->data(ui->table_employe->model()->index(index.row(),2)).toString());
    ui->comboBox_Sexe->setCurrentText(ui->table_employe->model()->data(ui->table_employe->model()->index(index.row(),3)).toString());
//    ui->dateEdit_naissance->date(ui->table_employe->model()->data(ui->table_employe->model()->index(index.row(),4)).toString());
    ui->lineEdit_Num_Tel->setText(ui->table_employe->model()->data(ui->table_employe->model()->index(index.row(),5)).toString());
    ui->lineEdit_Email->setText(ui->table_employe->model()->data(ui->table_employe->model()->index(index.row(),6)).toString());
    ui->lineEdit_Adress->setText(ui->table_employe->model()->data(ui->table_employe->model()->index(index.row(),7)).toString());


}



/**********************************************************************************************************************/

/**********************************************************************************************************************/

/**********************************************************************************************************************/
/****************************************************AVION*************************************************************/
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/**********************************************************************************************************************/

/****************************************************CRUDS******************************************************************/

void MainWindow::on_pushButton_ajouteravion_clicked()
{

    int code=ui->lineEdit_codeavion->text().toInt(); //convertir en entier
    QString depart=ui->lineEdit_departavion->text();
    QString arrivee=ui->lineEdit_arriveeavion->text();
    QString duree=ui->lineEdit_dureevolavion->text();
    int prix=ui->lineEdit_prixavion->text().toInt();
    int nbplace=ui->lineEdit_nbplaceavion->text().toInt();
    avion A(code,depart,arrivee,duree,prix,nbplace);
        bool test=A.ajouterAvion();
        if(test)
              {    QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                                            QObject::tr("ajout successful.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);
                             ui->table_avion->setModel(A.afficherAvion());
              }
                            else
                                QMessageBox::critical(nullptr, QObject::tr("Ajout errer"),
                                            QObject::tr("ajout failed.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

        ui->lineEdit_codeavion->clear();
        ui->lineEdit_departavion->clear();
        ui->lineEdit_arriveeavion->clear();
        ui->lineEdit_dureevolavion->clear();
        ui->lineEdit_prixavion->clear();
        ui->lineEdit_nbplaceavion->clear();

}



/******************************************************************************************************************/



void MainWindow::on_pushButton_afficheravion_clicked()
{

    ui->table_avion->setModel(A.afficherAvion());
}



/******************************************************************************************************************/


void MainWindow::on_pushButton_supprimeravion_clicked()
{
    avion A1;
    A1.setcode(ui->lineEdit_codeavion->text().toInt());
    bool test=A1.supprimerAvion(A1.get_code());
    QMessageBox msgBox;
    if (ui->lineEdit_codeavion->text()=="")
    {
        QMessageBox::critical(this, QObject::tr("Suppression Errer"),
                           QObject::tr("Echec de Suppression!!!\n""Veuillez remplir la label de CIN"), QMessageBox::Cancel);
    }
    else if (test)
    {
        QMessageBox::information(this, QObject::tr("Suppression avec Succes"),
                           QObject::tr("Suppression avec succes"), QMessageBox::Cancel);
        ui->table_avion->setModel(A.afficherAvion());
    }

    ui->lineEdit_codeavion->clear();
    ui->lineEdit_departavion->clear();
    ui->lineEdit_arriveeavion->clear();
    ui->lineEdit_dureevolavion->clear();
    ui->lineEdit_prixavion->clear();
    ui->lineEdit_nbplaceavion->clear();
}



/******************************************************************************************************************/



void MainWindow::on_pushButton_miseajouravion_clicked()
{
    int code=ui->lineEdit_codeavion->text().toInt();
    QString depart=ui->lineEdit_departavion->text();
    QString arrivee=ui->lineEdit_arriveeavion->text();
    QString duree=ui->lineEdit_dureevolavion->text();
    int prix=ui->lineEdit_prixavion->text().toInt();
     int nbplace=ui->lineEdit_nbplaceavion->text().toInt();

    avion A(code,depart,arrivee,duree,prix,nbplace);

    //bool test=E.modifierEmploye(E.getCIN(),E.getnom(),E.getprenom(),E.getsexe(),E.getdate_naissance(),E.getnum_tel(),E.getemail(),E.getadress());

    bool test=A.modifierAvion(A.get_code(),A.get_depart(),A.get_arrivee(),A.get_duree(),A.get_prix(),A.get_nbplace());

    QMessageBox msgBox;

    if ((ui->lineEdit_codeavion->text()==0),(ui->lineEdit_departavion->text()==""),(ui->lineEdit_arriveeavion->text()==""),(ui->lineEdit_dureevolavion->text()==0),(ui->lineEdit_prixavion->text()==""),(ui->lineEdit_nbplaceavion->text()==0))
    {
        QMessageBox::critical(this, QObject::tr("Modification Errer"),
                           QObject::tr("Echec de Modification!!!\n""Veuillez remplir tous le champs"), QMessageBox::Cancel);

    }
    else if(test)
    {
        QMessageBox::information(this, QObject::tr("Modification Succes"),
                           QObject::tr("Modifications avec Succes"), QMessageBox::Cancel);
        ui->table_avion->setModel(A.afficherAvion());

    }
    ui->lineEdit_codeavion->clear();
    ui->lineEdit_departavion->clear();
    ui->lineEdit_arriveeavion->clear();
    ui->lineEdit_dureevolavion->clear();
    ui->lineEdit_prixavion->clear();
    ui->lineEdit_nbplaceavion->clear();

}




/**********************************************************************************************************************/

/**********************************************************************************************************************/

/******************************************************Metiers*********************************************************/

/**********************************************************************************************************************/

/**********************************************************************************************************************/



void MainWindow::on_lineEdit_Rechercheavion_textChanged()
{

        QString rech=ui->lineEdit_Rechercheavion->text();
        ui->table_avion->setModel(A.RechercheAvion(rech));

}



/************************************************************************************************************/



void MainWindow::on_comboBox_trier_avion_activated()
{
        if(ui->comboBox_trier_avion->currentText()=="Tri par Code")
        {
            ui->table_avion->setModel(A.trieravionParCodeAvion());

        }
        else if(ui->comboBox_trier_avion->currentText()=="Tri par nbplace")
        {
            ui->table_avion->setModel(A.trieravionParnbplace());

        }
        else
        {
            ui->table_avion->setModel(A.trieravionParprix());
        }
}



/************************************************************************************************************/



void MainWindow::on_table_avion_clicked(const QModelIndex &index)
{
    ui->lineEdit_codeavion->setText(ui->table_avion->model()->data(ui->table_avion->model()->index(index.row(),0)).toString());
    ui->lineEdit_departavion->setText(ui->table_avion->model()->data(ui->table_avion->model()->index(index.row(),1)).toString());
    ui->lineEdit_arriveeavion->setText(ui->table_avion->model()->data(ui->table_avion->model()->index(index.row(),2)).toString());
    ui->lineEdit_dureevolavion->setText(ui->table_avion->model()->data(ui->table_avion->model()->index(index.row(),3)).toString());
    ui->lineEdit_prixavion->setText(ui->table_avion->model()->data(ui->table_avion->model()->index(index.row(),4)).toString());
    ui->lineEdit_nbplaceavion->setText(ui->table_avion->model()->data(ui->table_avion->model()->index(index.row(),5)).toString());

}




/************************************************************************************************************/




void MainWindow::on_pushButton_PDFavion_clicked()
{
    {
        QPdfWriter pdf("C:\\Users\\21698\\Desktop\\PDF_Projet\\PDF_Avions.pdf");

       QPainter painter(&pdf);
       int i = 4000;
              painter.setPen(Qt::red);
              painter.setFont(QFont("Time New Roman", 25));
              painter.drawText(3000,1400,"Liste Des Avions");
              painter.setPen(Qt::black);
              painter.setFont(QFont("Time New Roman", 15));
              painter.drawRect(100,3000,9400,500);
              painter.setFont(QFont("Time New Roman", 9));
              painter.drawText(400,3300,"code");
              painter.drawText(1350,3300,"depart");
              painter.drawText(2200,3300,"arrivee");
              painter.drawText(3400,3300,"duree vol");
              painter.drawText(4400,3300,"prix");
              painter.drawText(6200,3300,"nb place");
              painter.drawRect(100,3000,9400,9000);

              QSqlQuery query;
              query.prepare("select * from AVION");
              query.exec();
              while (query.next())
              {
                  painter.drawText(400,i,query.value(0).toString());
                  painter.drawText(1350,i,query.value(1).toString());
                  painter.drawText(2300,i,query.value(2).toString());
                  painter.drawText(3400,i,query.value(3).toString());
                  painter.drawText(4400,i,query.value(4).toString());
                  painter.drawText(6200,i,query.value(5).toString());


                 i = i + 350;
              }
              QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
              QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }

}



/************************************************************************************************************/



void MainWindow::on_pushButton_imprimeravion_clicked()
{


    QString strStream;
                    QTextStream out(&strStream);

                    const int rowCount = ui->table_avion->model()->rowCount();
                    const int columnCount = ui->table_avion->model()->columnCount();
                    QString TT = QDateTime::currentDateTime().toString();
                    out <<"<html>\n"
                          "<head>\n"
                           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        << "<title>ERP - COMmANDE LIST<title>\n "
                        << "</head>\n"
                        "<body bgcolor=#ffffff link=#5000A0>\n"
                           "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                           +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />"
                           "<h1 style=\"text-align: center;\"><strong> ******LISTE DES  avions ****** </strong></h1>"


                        "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                          "</br> </br>";
                    // headers
                    out << "<thead><tr bgcolor=#d6e5ff>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->table_avion->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->table_avion->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";

                    // data table
                    for (int row = 0; row < rowCount; row++) {
                        out << "<tr>";
                        for (int column = 0; column < columnCount; column++) {
                            if (!ui->table_avion->isColumnHidden(column)) {
                                QString data =ui->table_avion->model()->data(ui->table_avion->model()->index(row, column)).toString().simplified();
                                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                            }
                        }
                        out << "</tr>\n";
                    }
                    out <<  "</table>\n"
                        "</body>\n"
                        "</html>\n";

                    QTextDocument *document = new QTextDocument();
                    document->setHtml(strStream);

                    QPrinter printer;

                    QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                    if (dialog->exec() == QDialog::Accepted) {
                        document->print(&printer);
                    }

                    delete document;

}




/************************************************************************************************************/




void MainWindow::on_pushButton_statestiqueavion_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                     model->setQuery("select * from AVION where PRIX < 100 ");
                     float age=model->rowCount();
                     model->setQuery("select * from AVION where PRIX  between 100 and 1000 ");
                     float agee=model->rowCount();
                     model->setQuery("select * from AVION where PRIX >1000 ");
                     float ageee=model->rowCount();
                     float total=age+agee+ageee;
                     QString a=QString("moins de 5 ans "+QString::number((age*100)/total,'f',2)+"%" );
                     QString b=QString("entre 5 et 10 Ans"+QString::number((agee*100)/total,'f',2)+"%" );
                     QString c=QString("+10 Ans"+QString::number((ageee*100)/total,'f',2)+"%" );
                     QPieSeries *series = new QPieSeries();
                     series->append(a,age);
                     series->append(b,agee);
                     series->append(c,ageee);
             if (age!=0)
             {QPieSlice *slice = series->slices().at(0);
              slice->setLabelVisible();
              slice->setPen(QPen());}
             if ( agee!=0)
             {
                      // Add label, explode and define brush for 2nd slice
                      QPieSlice *slice1 = series->slices().at(1);
                      //slice1->setExploded();
                      slice1->setLabelVisible();
             }
             if(ageee!=0)
             {
                      // Add labels to rest of slices
                      QPieSlice *slice2 = series->slices().at(2);
                      //slice1->setExploded();
                      slice2->setLabelVisible();
             }
                     // Create the chart widget
                     QChart *chart = new QChart();
                     // Add data to chart with title and hide legend
                     chart->addSeries(series);
                     chart->setTitle("Pourcentage Par Age :Nombre Des Aimaux "+ QString::number(total));
                     chart->legend()->hide();
                     // Used to display the chart
                     QChartView *chartView = new QChartView(chart);
                     chartView->setRenderHint(QPainter::Antialiasing);
                     chartView->resize(1000,500);
                     chartView->show();



}




/**********************************************************************************************************************/

/**********************************************************************************************************************/

/**********************************************************************************************************************/
/**************************************************EMPLACEMENT*********************************************************/
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/**********************************************************************************************************************/

/****************************************************CRUDS******************************************************************/






void MainWindow::on_pushButton_ajouter_Emplacement_clicked()
{
    int num=ui->lineEdit_num->text().toInt(); //convertir en entier
    QString nom_emp=ui->lineEdit_nom_emplacement->text();
    int dimension=ui->lineEdit_dimension->text().toInt();
    QString reservation=ui->lineEdit_reservation->text();
    QString liberation=ui->lineEdit_liberation->text();
    Emplacement Em(num,nom_emp,dimension,reservation,liberation);
        bool test=Em.ajouterEmplacement();
        if(test)
              {    QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                                            QObject::tr("ajout successful.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);
                                    ui->table_Emplacement->setModel(Em.afficherEmplacement());
              }
                            else
                                QMessageBox::critical(nullptr, QObject::tr("Ajout errer"),
                                            QObject::tr("ajout failed.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

        QString nomFile ="Historique";
             QFile file("C:/Users/21698/Desktop/employe/"+nomFile+".txt");
             QString finalmsg="fichier modifie avec succes";
              if(!file.exists()){
              finalmsg="fichier cree avec succes";
              }
             file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



             QTextStream txt(&file);
               QString d_info = QDateTime::currentDateTime().toString();

             QString message2=d_info+" - Un Emplacement a été ajoutée avec le nom "+ nom_emp +"\n";
             txt << message2;

        ui->lineEdit_num->clear();
        ui->lineEdit_nom_emplacement->clear();
        ui->lineEdit_dimension->clear();
        ui->lineEdit_reservation->clear();
        ui->lineEdit_liberation->clear();
}


/**************************************************************************/

void MainWindow::on_pushButton_afficher_Emplacement_clicked()
{
    ui->table_Emplacement->setModel(Em.afficherEmplacement());
}

/**************************************************************************/





void MainWindow::on_pushButton_supprimer_Emplacement_clicked()
{

    Emplacement Em1;;
    Em1.setnum(ui->lineEdit_num->text().toInt());
   QString nom_emp = Em1.getnomEm();
    bool test=Em1.supprimerEmplacement(Em1.getnum()); 
    QMessageBox msgBox;
    if (ui->lineEdit_num->text()=="")
    {
        QMessageBox::critical(this, QObject::tr("Suppression Errer"),
                           QObject::tr("Echec de Suppression!!!\n""Veuillez remplir la label de CIN"), QMessageBox::Cancel);
    }
    else if (test)
    {
        QMessageBox::information(this, QObject::tr("Suppression avec Succes"),
                           QObject::tr("Suppression avec succes"), QMessageBox::Cancel);
        ui->table_Emplacement->setModel(Em.afficherEmplacement());
        QString nomFile ="Historique";
             QFile file("C:/Users/21698/Desktop/employe/"+nomFile+".txt");
             QString finalmsg="fichier modifie avec succes";
              if(!file.exists()){
              finalmsg="fichier cree avec succes";
              }
             file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



             QTextStream txt(&file);
               QString d_info = QDateTime::currentDateTime().toString();

             QString message2=d_info+" - Un Emplacement a été suprimmé avec le nom "+ nom_emp +"\n";
             txt << message2;

    }
    ui->lineEdit_num->clear();
    ui->lineEdit_nom_emplacement->clear();
    ui->lineEdit_dimension->clear();
    ui->lineEdit_reservation->clear();
    ui->lineEdit_liberation->clear();
}



/**************************************************************************/





void MainWindow::on_pushButton_modifier_Emplacement_clicked()
{
    int num=ui->lineEdit_num->text().toInt();
    QString nom_emp=ui->lineEdit_nom_emplacement->text();
    int dimension=ui->lineEdit_dimension->text().toInt();
    QString reservation=ui->lineEdit_reservation->text();
    QString liberation=ui->lineEdit_liberation->text();

    Emplacement Em(num,nom_emp,dimension,reservation,liberation);

    bool test=Em.modifierEmplacement(Em.getnum(),Em.getnomEm(),Em.getdimension(),Em.getreservation(),Em.getliberation());

    QMessageBox msgBox;

    if ((ui->lineEdit_num->text()==0),(ui->lineEdit_nom_emplacement->text()==""),(ui->lineEdit_dimension->text()==0),(ui->lineEdit_reservation->text()==""),(ui->lineEdit_liberation->text()==""))
    {
        QMessageBox::critical(this, QObject::tr("Modification Errer"),
                           QObject::tr("Echec de Modification!!!\n""Veuillez remplir tous le champs"), QMessageBox::Cancel);

    }
    else if(test)
    {
        QMessageBox::information(this, QObject::tr("Modification Succes"),
                           QObject::tr("Modifications avec Succes"), QMessageBox::Cancel);
        ui->table_Emplacement->setModel(Em.afficherEmplacement());

    }

    QString nomFile ="Historique";
         QFile file("C:/Users/21698/Desktop/employe/"+nomFile+".txt");
         QString finalmsg="fichier modifie avec succes";
          if(!file.exists()){
          finalmsg="fichier cree avec succes";
          }
         file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);



         QTextStream txt(&file);
           QString d_info = QDateTime::currentDateTime().toString();

         QString message2=d_info+" - Un Emplacement a été modifie avec le nom "+ nom_emp +"\n";
         txt << message2;
    ui->lineEdit_num->clear();
    ui->lineEdit_nom_emplacement->clear();
    ui->lineEdit_dimension->clear();
    ui->lineEdit_reservation->clear();
    ui->lineEdit_liberation->clear();

}


void MainWindow::on_comboBox_trier_Emplacement_activated()
{

    if(ui->comboBox_trier_Emplacement->currentText()=="Tri par Num")
    {
        ui->table_Emplacement->setModel(Em.triEmplacementParNum());

    }
    else if(ui->comboBox_trier_Emplacement->currentText()=="Tri par Nom")
    {
        ui->table_Emplacement->setModel(Em.triEmplacementParNom());

    }
    else
    {
        ui->table_Emplacement->setModel(Em.triEmplacementParDimension());
    }
}



void MainWindow::on_lineEdit_recherche_emplacement_textChanged()
{
            QString rech=ui->lineEdit_recherche_emplacement->text();
            ui->table_Emplacement->setModel(Em.chercheEmplacement(rech));

}

void MainWindow::on_table_Emplacement_clicked(const QModelIndex &index)
{
        ui->lineEdit_num->setText(ui->table_Emplacement->model()->data(ui->table_Emplacement->model()->index(index.row(),0)).toString());
        ui->lineEdit_nom_emplacement->setText(ui->table_Emplacement->model()->data(ui->table_Emplacement->model()->index(index.row(),1)).toString());
        ui->lineEdit_dimension->setText(ui->table_Emplacement->model()->data(ui->table_Emplacement->model()->index(index.row(),2)).toString());
        ui->lineEdit_reservation->setText(ui->table_Emplacement->model()->data(ui->table_Emplacement->model()->index(index.row(),3)).toString());
        ui->lineEdit_liberation->setText(ui->table_Emplacement->model()->data(ui->table_Emplacement->model()->index(index.row(),4)).toString());


}

void MainWindow::on_pushButton_Excel_clicked()
{

    QString nomFile="fichier excel ";
        QMessageBox msg;
        if(!nomFile.length()){

            msg.setText("entrer le nom du fichier");
            msg.exec();
        }
        else{
        QFile file("C:/Users/21698/Desktop/Excel_Projet/"+nomFile+".csv");
        QString finalmsg="fichier modifie avec succes";
         if(!file.exists()){
         finalmsg="fichier cree avec succes";
         }
        file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);

        QTextStream txt(&file);
        txt<<"Numéro \t\t  Nom    \t\t Dimension   \t\t  Reservation  \t\t     Liberation      \n";

        for(int i=0;i<5;i++){

        QString num= ui->table_Emplacement->model()->index(i,0).data().toString();
        QString nom= ui->table_Emplacement->model()->index(i,1).data().toString();
        QString dimension= ui->table_Emplacement->model()->index(i,2).data().toString();
        QString reservation= ui->table_Emplacement->model()->index(i,3).data().toString();
        QString liberation= ui->table_Emplacement->model()->index(i,4).data().toString();

        if(num.length()){

        txt<< "'"+ num +"' \t";
        txt<< "'"+ nom +"' \t";
        txt<< "'"+ dimension +"' \t";
        txt<< "'"+ reservation +"' \t";
        txt<< "'"+ liberation +"' \n\n";
        }
        }
        msg.setText(finalmsg);
        msg.exec();
        file.close();
        }

}

