#include "menucsv.h"

Menucsv::Menucsv(DevisesManager& DM,QWidget *parent): QMainWindow(parent),dm(DM){
    menucsv =new QLabel("Menu de chargement des données",this);
    menucsv->setGeometry(50,20,700,60);
    menucsv->setFont(QFont("Segoe UI Light", 20));


    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    //LISTE
    nomcsv=new QComboBox(this);
    nomcsv->setGeometry(50,80,300,30);
    nomcsv->setFont(QFont("Segoe UI Light", 12));
    ListeFichiers liste(nomcsv,dir);//On est créee la liste de fichiers d'un repertoire commun pour tous les fichiers

    //BUTTONS

    csvdefault= new QPushButton("Charger tout le fichier",this);
    csvdefault->setGeometry(50,450,300,30);
    csvdefault->setFont(QFont("Segoe UI Light", 12));
    connect(csvdefault,SIGNAL(clicked()),this, SLOT(chargercsvdefault()));

    graphique= new QPushButton("Montrer cours d'un paire",this);
    graphique->setGeometry(450,80,300,30);
    graphique->setFont(QFont("Segoe UI Light", 12));
    connect(graphique,SIGNAL(clicked()),this, SLOT(montrerOHCLAction()));

    simulationSelection=new QPushButton("Simulation",this);
    simulationSelection->setFont(QFont("Segoe UI Light", 12));
    simulationSelection->setGeometry(450,130,300,30);
    connect(simulationSelection,SIGNAL(clicked()),this, SLOT(simulationSelectionAction()));


    nombase= new QLineEdit(this);
    if(nomcsv->currentText().isEmpty()) nombase->setText("Il n'y a pas des fichiers .cvs dans cette dossier");
    else nombase->setText("Code de votre devise de base si on veut acheter des investissements");
    nombase->setGeometry(50,230,700,60);
    nombase->setFont(QFont("Segoe UI Light", 12));

    exit= new QPushButton("Exit",this);
    exit->setGeometry(650,450,80,30);
    exit->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(exit, SIGNAL(clicked()), this, SLOT(close()));
}


void Menucsv::chargercsvdefault(){// charger le Devise Manager avec le fichier selectionné
    ListeFichiers liste;
    QString nom=nomcsv->currentText();
    QString base=nombase->text();
    try {
        liste.getListeBougies(dm, nom, base, nombase,dir); //fonction spécial qui le réalise
    }catch(const QString e){
        nombase->setText(e);
    }catch (TradingException e){
        nombase->setText(e.getInfo());
    }
}

void Menucsv::montrerOHCLAction(){
    MontrerOHLC *c=new MontrerOHLC(dm,this);
    c->setFixedSize(400,270);
    c->setModal(true);
    c->show();
}

void Menucsv::simulationSelectionAction(){
    SimulationSelection *c= new SimulationSelection(dm,this);
    c->show();
}
