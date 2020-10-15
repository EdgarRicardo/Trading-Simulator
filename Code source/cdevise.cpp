#include "cdevise.h"

 //!< Interface pour créer une nouvelle devise by Corona
CreateDevise::CreateDevise(DevisesManager&dManager,QWidget *parent):QDialog(parent),dm(dManager){
    cd =new QLabel("Creer une devise",this);
    cd->setGeometry(100,20,200,25);
    cd->setFont(QFont("Segoe UI Light", 20));

    code=new QLabel("Code: ",this);
    code->setGeometry(50,80,60,30);
    code->setFont(QFont("Segoe UI Light", 12));
    codeLE=new QLineEdit(this);
    codeLE->setGeometry(150,80,200,30);
    codeLE->setFont(QFont("Segoe UI Light", 12));

    monnaie=new QLabel("Monnaie: ",this);
    monnaie->setGeometry(50,140,70,30);
    monnaie->setFont(QFont("Segoe UI Light", 12));
    monnaieLE=new QLineEdit(this);
    monnaieLE->setGeometry(150,140,200,30);
    monnaieLE->setFont(QFont("Segoe UI Light", 12));

    zone=new QLabel("Zone: ",this);
    zone->setGeometry(50,200,60,30);
    zone->setFont(QFont("Segoe UI Light", 12));
    zoneLE=new QLineEdit(this);
    zoneLE->setGeometry(150,200,200,30);
    zoneLE->setFont(QFont("Segoe UI Light", 12));

    resultat=new QLabel(this);
    resultat->setGeometry(20,250,150,50);
    resultat->setFont(QFont("Segoe UI Light", 10));

    cancel= new QPushButton("Cancel",this);
    cancel->setGeometry(300,250,80,30);
    cancel->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancelAction()));

    ok= new QPushButton("Ok",this);
    ok->setGeometry(200,250,80,30);
    ok->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(okAction()));
}

void CreateDevise::okAction(){
    QString c,m,z,e="Remplissez toutes les\ninformations demandées",str;
    c=codeLE->text();
    m=monnaieLE->text();
    z=zoneLE->text();
    try {
        if(c.isEmpty() || m.isEmpty() || z.isEmpty()) throw e;
        dm.creationDevise(c,m,z);
        resultat->setText("Création réussie "+str.setNum(dm.getNbDevises()));
    }
    catch(const QString e){
        resultat->setText(e);
    }
    catch (TradingException e){

        resultat->setText(e.getInfo());
    }

}

void CreateDevise::cancelAction(){
    close();
}
