#include "avion.h"
#include "connexion.h"
#include <QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QTextDocument>


avion::avion()
{
    code=0;
    QString depart="";
     QString arrivee="";
     QString duree="";
     QString prix="";
     nbplace=0;

}



avion::avion(int code,QString depart,QString arrivee,QString duree,int prix,int nbplace)
{
    this->code=code;
    this->depart=depart;
    this->arrivee=arrivee;
    this->duree=duree;
    this->prix=prix;
    this->nbplace=nbplace;
}

int avion::get_code(){return code;}
QString avion::get_depart(){return depart;}
int avion::get_nbplace(){return nbplace;}
QString avion::get_arrivee(){return arrivee;}
int avion::get_prix(){return prix;}
QString avion::get_duree(){return duree;}



void avion::setcode(int code){this->code=code;}
void avion::setdepart(QString depart){this->depart=depart;}
void avion::setarrivee(QString arrivee){this->arrivee=arrivee;}
void avion::setduree(QString duree){this->duree=duree;}
void avion::setprix(int prix){this->prix=prix;}
void avion::setnbplace(int nbplace){this->nbplace=nbplace;}



bool avion::ajouterAvion()
{

     QSqlQuery query;
     query.prepare("INSERT INTO AVION (CODE, DEPART, ARRIVEE , DUREE, PRIX, NBPLACE) "
                   "VALUES (:code, :depart, :arrivee, :duree, :prix, :nbplace)");// prparation de requette
     query.bindValue(":code", code);
     query.bindValue(":depart", depart);
     query.bindValue(":arrivee",arrivee);
     query.bindValue(":duree",duree);
     query.bindValue(":prix",prix );
     query.bindValue(":nbplace",nbplace);
     return query.exec();

}



/***********************************************************************************************/


QSqlQueryModel* avion::afficherAvion()
{
     QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT *  FROM AVION ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("depart"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("arrivee"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbplace"));

     return model;
}


/***********************************************************************************************/


bool avion::supprimerAvion(int code)
{
    QSqlQuery query;
    query.prepare(" Delete from AVION where CODE=:CODE ");
    query.bindValue(":CODE",code);

    return query.exec();
}




/***********************************************************************************************/



bool avion::modifierAvion(int code, QString depart , QString arrivee , QString duree, int prix, int nbplace)
{
    QSqlQuery query;
    query.prepare("update AVION set depart=:depart,arrivee=:arrivee,duree=:duree,prix=:prix,nbplace=:nbplace where code=:code");
    query.bindValue(":code",code);
    query.bindValue(":depart",depart);
    query.bindValue(":arrivee",arrivee);
    query.bindValue(":prix",prix);
    query.bindValue(":duree",duree);
    query.bindValue(":nbplace",nbplace);
    return query.exec();

}




/******************************************************************************************************************************/


QSqlQueryModel* avion::RechercheAvion(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM avion WHERE code LIKE '"+recherche+"%' OR depart LIKE '"+recherche+"%' OR nbplace LIKE '"+recherche+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("code"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("depart"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("arrivee"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbplace"));



return model;
}

/********************************************************************************************/



QSqlQueryModel * avion::trieravionParCodeAvion()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM AVION order by code ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

////////////////////
QSqlQueryModel * avion::trieravionParnbplace()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM AVION order by nbplace ASC");
           q->exec();
           model->setQuery(*q);
           return model;
}

////////////////////
QSqlQueryModel * avion::trieravionParprix()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM AVION order by prix ASC");

           q->exec();
           model->setQuery(*q);
           return model;
}




