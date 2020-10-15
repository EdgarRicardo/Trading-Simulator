#include "addindicateur.h"

 //! Interfaces pour ajouter les Indicateurs EMA, RSI ou MACD

addEMA::addEMA(EvolutionCours* evolutionC,QWidget *parent):QDialog(parent),ec(evolutionC){
    addI =new QLabel("Add Indicateur EMA: "+ec->getPaireDevises().toString(),this);
    addI->setGeometry(20,20,380,40);
    addI->setFont(QFont("Segoe UI Light", 20));

    periodsL=new QLabel("Periods:",this);
    periodsL->setGeometry(40,100,150,30);
    periodsL->setFont(QFont("Segoe UI Light", 12));

    periodsLE=new QLineEdit(this);
    periodsLE->setGeometry(200,100,150,30);
    periodsLE->setFont(QFont("Segoe UI Light", 12));
    periodsLE->setValidator(new QIntValidator(5,30,this));

    resultat=new QLabel(this);
    resultat->setGeometry(20,200,150,50);
    resultat->setFont(QFont("Segoe UI Light", 10));

    cancel= new QPushButton("Cancel",this);
    cancel->setGeometry(300,200,80,30);
    cancel->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(close()));

    ok= new QPushButton("Ok",this);
    ok->setGeometry(200,200,80,30);
    ok->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(okAction()));
}

addRSI::addRSI(EvolutionCours* evolutionC,QWidget *parent):QDialog(parent),ec(evolutionC){
    addI =new QLabel("Add Indicateur RSI: "+ec->getPaireDevises().toString(),this);
    addI->setGeometry(20,20,380,40);
    addI->setFont(QFont("Segoe UI Light", 20));

    periodsL=new QLabel("Periods:",this);
    periodsL->setGeometry(40,100,150,30);
    periodsL->setFont(QFont("Segoe UI Light", 12));

    periodsLE=new QLineEdit(this);
    periodsLE->setGeometry(200,100,150,30);
    periodsLE->setFont(QFont("Segoe UI Light", 12));
    periodsLE->setValidator(new QIntValidator(5,30,this));


    resultat=new QLabel(this);
    resultat->setGeometry(20,200,150,50);
    resultat->setFont(QFont("Segoe UI Light", 10));

    cancel= new QPushButton("Cancel",this);
    cancel->setGeometry(300,200,80,30);
    cancel->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(close()));

    ok= new QPushButton("Ok",this);
    ok->setGeometry(200,200,80,30);
    ok->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(okAction()));
}


addMACD::addMACD(EvolutionCours* evolutionC,QWidget *parent):QDialog(parent),ec(evolutionC){
    addI =new QLabel("Add Indicateur MACD: "+ec->getPaireDevises().toString(),this);
    addI->setGeometry(20,20,380,40);
    addI->setFont(QFont("Segoe UI Light", 20));

    periodsEma1L=new QLabel("Periods EMA 1:",this);
    periodsEma1L->setGeometry(40,100,150,30);
    periodsEma1L->setFont(QFont("Segoe UI Light", 12));

    periodsEma1LE=new QLineEdit(this);
    periodsEma1LE->setGeometry(200,100,150,30);
    periodsEma1LE->setFont(QFont("Segoe UI Light", 12));
    periodsEma1LE->setValidator(new QIntValidator(5,30,this));

    periodsEma2L=new QLabel("Periods EMA 2:",this);
    periodsEma2L->setGeometry(40,150,150,30);
    periodsEma2L->setFont(QFont("Segoe UI Light", 12));

    periodsEma2LE=new QLineEdit(this);
    periodsEma2LE->setGeometry(200,150,150,30);
    periodsEma2LE->setFont(QFont("Segoe UI Light", 12));
    periodsEma2LE->setValidator(new QIntValidator(5,30,this));

    periodsSignalL=new QLabel("Periods Signal:",this);
    periodsSignalL->setGeometry(40,200,150,30);
    periodsEma1L->setFont(QFont("Segoe UI Light", 12));

    periodsSignalLE=new QLineEdit(this);
    periodsSignalLE->setGeometry(200,200,150,30);
    periodsSignalLE->setFont(QFont("Segoe UI Light", 12));
    periodsSignalLE->setValidator(new QIntValidator(5,30,this));

    resultat=new QLabel(this);
    resultat->setGeometry(20,250,150,50);
    resultat->setFont(QFont("Segoe UI Light", 10));

    cancel= new QPushButton("Cancel",this);
    cancel->setGeometry(300,250,80,30);
    cancel->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(close()));

    ok= new QPushButton("Ok",this);
    ok->setGeometry(200,250,80,30);
    ok->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(okAction()));
}

void addEMA::okAction(){
    QString str,e="Remplissez toutes les\ninformations demandées",e2="Nombre entre 5 et 30",str2,
            e3="Maximum de 5 indicateurs EMA";
    str=periodsLE->text();
    try {
    if(ec->getNbEmas()>4) throw e3;
    if(str.isEmpty()) throw e;
    if(str.toInt()<5 || str.toInt()>30) throw e2;
    ec->addEma(str.toInt());  //Function pour ajouter l'indicateur EMA
    resultat->setText("Création réussie:EMA "+str2.setNum(ec->getNbEmas()));
    } catch (const QString  e){
        resultat->setText(e);
    }
}

void addRSI::okAction(){
    QString str,e="Remplissez toutes les\ninformations demandées",e2="Nombre entre 5 et 30",str2,
            e3="Maximum de 5 indicateurs SRI";
    str=periodsLE->text();
    try {
    if(ec->getNbRsis()>4) throw e3;
    if(str.isEmpty()) throw e;
    if(str.toInt()<5 || str.toInt()>30) throw e2;
    ec->addRsi(str.toInt());  //Ajouter Indicateur RSI
    resultat->setText("Création réussie:RSI "+str2.setNum(ec->getNbRsis()));
    } catch (const QString  e){
        resultat->setText(e);
    }
}

void addMACD::okAction(){
    QString ema,ema2,signal,e="Remplissez toutes les\ninformations demandées",e2="Nombre entre 5 et 30",str,
            e3="Maximum de 5 indicateurs MACD";
    ema=periodsEma1LE->text();
    ema2=periodsEma2LE->text();
    signal=periodsSignalLE->text();
    try {
    if(ec->getNbMacds()>4) throw e3;
    if(ema.isEmpty() || ema2.isEmpty() || signal.isEmpty()) throw e;
    if(ema.toInt()<5 || ema.toInt()>30 || ema2.toInt()<5 || ema2.toInt()>30 ||
            signal.toInt()<5 || signal.toInt()>30) throw e2;
    ec->addMacd(ema.toInt(),ema2.toInt(),signal.toInt());  //Ajouter MACD
    resultat->setText("Création réussie:MACD "+str.setNum(ec->getNbMacds()));
    } catch (const QString  e){
        resultat->setText(e);
    }
}
