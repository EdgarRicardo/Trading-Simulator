#include "cpaires.h"

CreatePaire::CreatePaire(DevisesManager &dManager, QWidget *parent):QDialog(parent),dm(dManager){
    //fenetre.setFixedSize(400, 500);

    cPaire =new QLabel("Creer un paire de devises",this);
    cPaire->setGeometry(60,20,300,30);
    cPaire->setFont(QFont("Segoe UI Light", 20));

    cancel= new QPushButton("Cancel",this);
    cancel->setGeometry(300,250,80,30);
    cancel->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(close()));

    devise1L =new QLabel("Devise 1:",this);
    devise1L->setGeometry(75,80,100,30);
    devise1L->setFont(QFont("Segoe UI Light", 15));

    devise1=new QComboBox(this);
    devise1->setGeometry(30,120,150,30);
    devise1->setFont(QFont("Segoe UI Light", 12));
    Devise** dev=dm.getDevises();
    for (unsigned int i = 0; i < dm.getNbDevises(); i++){
        while(dev[i]==nullptr) i++;
        devise1->addItem(dev[i]->getCode());
    }

    devise2L =new QLabel("Devise 2:",this);
    devise2L->setGeometry(265,80,100,30);
    devise2L->setFont(QFont("Segoe UI Light", 15));

    devise2=new QComboBox(this);
    devise2->setGeometry(220,120,150,30);
    devise2->setFont(QFont("Segoe UI Light", 12));
    for (unsigned int i = 0; i < dm.getNbDevises(); i++){
        while(dev[i]==nullptr) i++;
        devise2->addItem(dev[i]->getCode());
    }

    ok= new QPushButton("Ok",this);
    ok->setGeometry(200,250,80,30);
    ok->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(okAction()));

    resultat=new QLabel(this);
    resultat->setGeometry(20,220,180,60);
    resultat->setFont(QFont("Segoe UI Light", 10));
}

void CreatePaire::okAction(){
    QString d1,d2,e="On ne peut pas faire un paire\n avec 2 divises egales",str;
    d1=devise1->currentText();
    d2=devise2->currentText();
    try {
        if(!QString::compare(d1,d2)) throw e;
        unsigned int nbPrs=dm.getNbPaires(); //Nombre de paires actuelles
        dm.getPaireDevises(d1,d2);
        //On va voir si le nombre des paire a aumente, sinon ca signifie que la paire devise existe deja
        if(dm.getNbPaires()==nbPrs) resultat->setText("Le paire de devise \nexiste déjà");
        else resultat->setText("Création réussie "+str.setNum(dm.getNbPaires()));
    }
    catch(const QString e){
        resultat->setText(e);
    }
    catch (TradingException e){
        resultat->setText(e.getInfo());
    }

}
