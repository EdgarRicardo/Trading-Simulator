#include "ccours.h"
 //!< Interface pour ajouter un cours à une Paire de devise selon un jour au DeviseManager by Corona
CreateCours::CreateCours(DevisesManager&dManager,QWidget *parent):QDialog(parent),dm(dManager){
    cCours =new QLabel("Ajouter un cours d'un\n    paire de devises",this);
    cCours->setGeometry(100,10,250,100);
    cCours->setFont(QFont("Segoe UI Light", 20));

    paireL=new QLabel("Paire de Devise:",this);
    paireL->setGeometry(40,120,150,30);
    paireL->setFont(QFont("Segoe UI Light", 12));

    open=new QLabel("Open:",this);
    open->setGeometry(70,170,150,30);
    open->setFont(QFont("Segoe UI Light", 12));

    high=new QLabel("High:",this);
    high->setGeometry(70,220,150,30);
    high->setFont(QFont("Segoe UI Light", 12));

    low=new QLabel("Low:",this);
    low->setGeometry(70,270,150,30);
    low->setFont(QFont("Segoe UI Light", 12));

    closeL=new QLabel("Close:",this);
    closeL->setGeometry(70,320,150,30);
    closeL->setFont(QFont("Segoe UI Light", 12));

    volume=new QLabel("Volume:",this);
    volume->setGeometry(70,370,150,30);
    volume->setFont(QFont("Segoe UI Light", 12));

    date=new QLabel("Date:",this);
    date->setGeometry(70,420,150,30);
    date->setFont(QFont("Segoe UI Light", 12));

    paireC=new QComboBox(this);
    paireC->setGeometry(200,120,150,30);
    paireC->setFont(QFont("Segoe UI Light", 12));
    PaireDevises** par=dm.getPaires();
    for (unsigned int i = 0; i < dm.getNbPaires(); i++){
        if(par[i]!=nullptr)
            paireC->addItem(par[i]->toString());
    }

    openLE=new QLineEdit("48.63",this);
    openLE->setGeometry(170,170,150,30);
    openLE->setFont(QFont("Segoe UI Light", 12));

    highLE=new QLineEdit("57.52",this);
    highLE->setGeometry(170,220,150,30);
    highLE->setFont(QFont("Segoe UI Light", 12));

    lowLE=new QLineEdit("47.21",this);
    lowLE->setGeometry(170,270,150,30);
    lowLE->setFont(QFont("Segoe UI Light", 12));

    closeLE=new QLineEdit("51.24",this);
    closeLE->setGeometry(170,320,150,30);
    closeLE->setFont(QFont("Segoe UI Light", 12));

    volumeLE=new QLineEdit("15785",this);
    volumeLE->setGeometry(170,370,150,30);
    volumeLE->setFont(QFont("Segoe UI Light", 12));

    dateW= new QDateEdit(this);
    dateW->setGeometry(170,420,150,30);
    dateW->setFont(QFont("Segoe UI Light", 12));

    cancel= new QPushButton("Cancel",this);
    cancel->setGeometry(300,470,80,30);
    cancel->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(close()));

    ok= new QPushButton("Ok",this);
    ok->setGeometry(200,470,80,30);
    ok->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(okAction()));

    resultat=new QLabel(this);
    resultat->setGeometry(20,455,150,50);
    resultat->setFont(QFont("Segoe UI Light", 10));
}

void CreateCours::okAction(){
    QString pD,o,h,l,c,v,e="Remplissez toutes les\ninformations demandées",base,contrapartie,str;
    o=openLE->text();
    h=highLE->text();
    c=closeLE->text();
    l=lowLE->text();
    v=volumeLE->text();
    pD=paireC->currentText();
    try {
        if(o.isEmpty() || h.isEmpty() || c.isEmpty() || l.isEmpty() || pD.isEmpty() || v.isEmpty()) throw e;
        const PaireDevises& pDevise = dm.recupererPaire(pD);
        EvolutionCours *creation=dm.creerCoursDevise(&pDevise,o.toDouble(),h.toDouble(),l.toDouble(),
                            c.toDouble(),v.toDouble(),QDate(dateW->date()));
        resultat->setText("Cours numero "+str.setNum(creation->getNbCours())+
                          "\n pour "+creation->getPaire()->toString());
    }
    catch(const QString e){
        resultat->setText(e);
    }
    catch (TradingException e){
        resultat->setText(e.getInfo());
    }

}
