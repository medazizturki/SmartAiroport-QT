#include "employes.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>




Employe::Employe()
{
CIN=0; nom=" "; prenom=" "; sexe=" "; num_tel=0; email=" "; adress= " ";
}


Employe::Employe(int CIN,QString nom,QString prenom,QString sexe,QDate date_naissance,int num_tel,QString email, QString adress)
{
    this->CIN=CIN;
    this->nom=nom;
    this->prenom=prenom;
    this->sexe=sexe;
    this->date_naissance=date_naissance;
    this->num_tel=num_tel;
    this->email=email;
    this->adress=adress;
}


int Employe::getCIN(){return CIN;}
QString Employe::getnom(){return nom;}
QString Employe::getprenom(){return prenom;}
QString Employe::getsexe(){return sexe;}
QDate Employe::getdate_naissance(){return date_naissance;}
int Employe::getnum_tel(){return num_tel;}
QString Employe::getemail(){return email;}
QString Employe::getadress(){return adress;}


void Employe::setCIN(int CIN){this->CIN=CIN;}
void Employe::setnom(QString nom){this->nom=nom;}
void Employe::setprenom(QString prenom){this->prenom=prenom;}
void Employe::setsexe(QString sexe){this->sexe=sexe;}
void Employe::setdate_naissance(QDate date_naissance){this->date_naissance=date_naissance;}
void Employe::setnum_tel(int num_tel){this->num_tel=num_tel;}
void Employe::setemail(QString email){this->email=email;}
void Employe::setadress(QString adress){this->adress=adress;}



/******************************************************************************************************************/

/*******************************************CRUDS*****************************************************/



bool Employe::ajouterEmploye()
{

     QSqlQuery query;
     query.prepare("INSERT INTO EMPLOYE (CIN, NOM, PRENOM ,SEXE, DATE_NAISSANCE, NUM_TEL, EMAIL, ADRESS) "
                   "VALUES (:CIN, :nom, :prenom, :sexe, :date_naissance, :num_tel, :email, :adress)");// prparation de requette
     query.bindValue(":CIN", CIN); //remplir CIN2 dans CIN1
     query.bindValue(":nom", nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":sexe",sexe);
     query.bindValue(":date_naissance",date_naissance );
     query.bindValue(":num_tel",num_tel);
     query.bindValue(":email",email);
     query.bindValue(":adress",adress);
     return query.exec();

}



/***********************************************************************************************/


QSqlQueryModel* Employe::afficherEmploye()
{
     QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT *  FROM EMPLOYE ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));//nom entite
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("num_tel"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("email"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("adress"));

     return model;
}


/***********************************************************************************************/


bool Employe::supprimerEmploye(int CIN)
{
    QSqlQuery query;
    query.prepare(" Delete from EMPLOYE where CIN=:CIN ");
    query.bindValue(":CIN",CIN);

    return query.exec();
}



/***********************************************************************************************/



bool Employe::supprimerTout()
{
    QSqlQuery query;
    query.prepare("delete from EMPLOYE ");
    return query.exec();
}



/***********************************************************************************************/



bool Employe::modifierEmploye(int CIN,QString nom,QString prenom,QString sexe,QDate date_naissance,int num_tel,QString email,QString adress)
{

    QSqlQuery query;
    query.prepare("update EMPLOYE set nom=:nom,prenom=:prenom,sexe=:sexe,date_naissance=:date_naisssance,num_tel=:num_tel,email=:email,adress=:adress where CIN=:CIN");
    query.bindValue(":CIN",CIN);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":sexe",sexe);
    query.bindValue(":date_naisssance",date_naissance);
    query.bindValue(":num_tel",num_tel);
    query.bindValue(":email",email);
    query.bindValue(":adress",adress);
    return query.exec();

}


/******************************************************************************************************************************************/

/****************************************Metiers*******************************************************/



QSqlQueryModel* Employe::RechercheEmploye(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM employe WHERE CIN LIKE '"+recherche+"%' OR nom LIKE '"+recherche+"%' OR prenom LIKE '"+recherche+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("num_tel"));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr("email"));
     model->setHeaderData(7, Qt::Horizontal, QObject::tr("adress"));

return model;
}


/***********************************************************************************************/


//Trie Par CIN montant
QSqlQueryModel * Employe::trierEmployeParCIN_M()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM EMPLOYE order by CIN ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

//Trie Par CIN descendent
QSqlQueryModel * Employe::trierEmployeParCIN_D()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM EMPLOYE order by CIN DESC");
           q->exec();
           model->setQuery(*q);
           return model;
}

//Trie Par Nom
QSqlQueryModel * Employe::trierEmployeParNom()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM EMPLOYE order by nom ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}


//Trie Par Date Naissance
QSqlQueryModel * Employe::trierEmployeParDate()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM EMPLOYE order by date_naissance ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}






