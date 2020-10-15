#include "menu.h"

 //!Interface principale: New devise, new paire devise, new cours, etc.
Menu::Menu(DevisesManager&DM,QWidget *parent):QMainWindow(parent),dm(DM){

    menuO =new QLabel("Menu d'options",this);
    menuO->setGeometry(300,20,200,40);
    menuO->setFont(QFont("Segoe UI Light", 20));

    addDev= new QPushButton("Ajouter une nouvelle devise",this);
    addDev->setGeometry(50,80,300,30);
    addDev->setFont(QFont("Segoe UI Light", 12));
    connect(addDev,SIGNAL(clicked()),this, SLOT(addDeviseAction()));

    addPaireD= new QPushButton("Ajouter une nouvelle paire",this);
    addPaireD->setGeometry(50,140,300,30);
    addPaireD->setFont(QFont("Segoe UI Light", 12));
    connect(addPaireD,SIGNAL(clicked()),this, SLOT(addPaireAction()));

    addCours= new QPushButton("Ajouter un nouveau cours",this);
    addCours->setGeometry(50,200,300,30);
    addCours->setFont(QFont("Segoe UI Light", 12));
    connect(addCours,SIGNAL(clicked()),this, SLOT(addCoursAction()));


    montrerOHLC=new QPushButton("Cours d'une paire",this);
    montrerOHLC->setGeometry(450,80,300,30);
    montrerOHLC->setFont(QFont("Segoe UI Light", 12));
    connect(montrerOHLC,SIGNAL(clicked()),this, SLOT(montrerOHCLAction()));

    simulationSelection=new QPushButton("Simulation",this);
    simulationSelection->setFont(QFont("Segoe UI Light", 12));
    simulationSelection->setGeometry(450,140,300,30);
    connect(simulationSelection,SIGNAL(clicked()),this, SLOT(simulationSelectionAction()));


    exit= new QPushButton("Exit",this);
    exit->setGeometry(650,250,80,30);
    exit->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(exit, SIGNAL(clicked()), this, SLOT(close()));
}

 //Actions pour ouvrir les interfaces correspodance au bouton cliqué

void Menu::simulationSelectionAction(){
    SimulationSelection *c= new SimulationSelection(dm,this);
    c->show();
}

void Menu::addDeviseAction(){
    CreateDevise *c=new CreateDevise(dm,this);
    c->setFixedSize(400,300);
    c->setModal(true);
    c->setWindowFlag(Qt::WindowCloseButtonHint,false);
    c->show();
}

void Menu::addPaireAction(){
    CreatePaire *c=new CreatePaire(dm,this);
    c->setFixedSize(400,300);
    c->setModal(true); //Bloque l'ecran pere
    c->show();
}

void Menu::addCoursAction(){
    CreateCours *c=new CreateCours(dm,this);
    c->setFixedSize(400,510);
    c->setModal(true);
    c->show();
}

void Menu::montrerOHCLAction(){
    MontrerOHLC *c=new MontrerOHLC(dm,this);
    c->setFixedSize(400,270);
    c->setModal(true);
    c->show();
}
