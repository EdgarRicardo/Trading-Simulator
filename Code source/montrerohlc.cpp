#include "montrerohlc.h"


 //! Interface pour voir les cours d'un paire de devise + creer indicateurs + bouton pour voir les graphiques
MontrerOHLC::MontrerOHLC(DevisesManager&dManager,QWidget *parent):QDialog(parent),dm(dManager){
    dPaire =new QLabel("Voir cours d'une devise",this);
    dPaire->setGeometry(20,20,380,40);
    dPaire->setFont(QFont("Segoe UI Light", 20));

    paireL=new QLabel("Paire de Devise:",this);
    paireL->setGeometry(40,100,150,30);
    paireL->setFont(QFont("Segoe UI Light", 12));

    paireC=new QComboBox(this);
    paireC->setGeometry(200,100,150,30);
    paireC->setFont(QFont("Segoe UI Light", 12));
    PaireDevises** par=dm.getPaires();
    for (unsigned int i = 0; i < dm.getNbPaires(); i++){
        if(par[i]!=nullptr)
            paireC->addItem(par[i]->toString());
    }

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


void MontrerOHLC::okAction(){
    QString c,e="Remplissez toutes les\ninformations demandées";
    c=paireC->currentText();
    try {
        if(c.isEmpty()) throw e;
        const PaireDevises& pDevise = dm.recupererPaire(c);
        tableCours* tC=new tableCours(dm,pDevise,this);
        tC->setFixedSize(665,400);
        tC->show();
        this->setVisible(false);
    }
    catch(const QString e){
        resultat->setText(e);
    }catch (TradingException e){
        resultat->setText(e.getInfo());
    }

}

tableCours::tableCours(DevisesManager&dManager,const PaireDevises&paireD,QWidget *parent):QDialog(parent),paireDev(paireD),dm(dManager){
    coursL =new QLabel("Paire: "+paireDev.toString(),this);
    coursL->setGeometry(20,20,380,40);
    coursL->setFont(QFont("Segoe UI Light", 20));

    EvolutionCours** ecTab=dm.getCours();
    //On va obtenir le EvolutionCours que l'utilisateur veut voir selon le paire choisi
    for (unsigned int i = 0; i < dm.getNbCoursTab(); i++){
        if(ecTab[i]!=nullptr && ecTab[i]->getPaire()->toString()==paireDev.toString()){
            ec=ecTab[i];
            break;
        }
    }
    //CoursOHLC* coursX;
    if(ec!=nullptr && ec->getNbCours()>0){
        CoursOHLC* cours=ec->getCours();
        QString str;
        tableC = new QTableWidget(int(ec->getNbCours()),6,this);

         //boucle pour ajouter tous les cours - On peut aussi utiliser l'iterator
        for (unsigned int i=0;i<ec->getNbCours();i++){
                if(&cours[i]!=nullptr){
                    QTableWidgetItem *date = new QTableWidgetItem(cours[i].getDate().toString("yyyy/MM/dd"));
                    tableC->setItem(int(i),0, date);

                    QTableWidgetItem *open = new QTableWidgetItem(str.setNum(cours[i].getOpen()));
                    tableC->setItem(int(i),1, open);

                    QTableWidgetItem *high = new QTableWidgetItem(str.setNum(cours[i].getHigh()));
                    tableC->setItem(int(i),2, high);

                    QTableWidgetItem *low = new QTableWidgetItem(str.setNum(cours[i].getLow()));
                    tableC->setItem(int(i),3, low);

                    QTableWidgetItem *close = new QTableWidgetItem(str.setNum(cours[i].getClose()));
                    tableC->setItem(int(i),4, close);

                    QTableWidgetItem *volume = new QTableWidgetItem(str.setNum(cours[i].getVolume()));
                    tableC->setItem(int(i),5, volume);
                }
        }
    }
    else tableC = new QTableWidget(0,6,this);
    tableC->setGeometry(25,75,615,250);
    QStringList headers = { "DAY", "OPEN", "HIGH", "LOW","CLOSE","VOLUME"};
    tableC->setHorizontalHeaderLabels(headers);

    retourner= new QPushButton("Retourner",this);
    retourner->setGeometry(550,350,100,30);
    retourner->setFont(QFont("Segoe UI Light", 12));
    QObject::connect(retourner, SIGNAL(clicked()), this, SLOT(closeAction()));

    resultBougies= new QLabel(this);
    resultBougies->setGeometry(25,340,125,40);
    resultBougies->setFont(QFont("Segoe UI Light", 10));

    viewerBougies= new QPushButton("Graphiques",this);
    viewerBougies->setGeometry(380,350,130,30);
    viewerBougies->setFont(QFont("Segoe UI Light", 12));

    typeIndicateur=new QComboBox(this);
    typeIndicateur->setGeometry(240,335,100,25);
    typeIndicateur->setFont(QFont("Segoe UI Light", 10));
    typeIndicateur->addItem("EMA");
    typeIndicateur->addItem("RSI");
    typeIndicateur->addItem("MACD-Signal");

    addIndicateur= new QPushButton("Add Indicateur",this);
    addIndicateur->setGeometry(240,365,100,25);
    addIndicateur->setFont(QFont("Segoe UI Light", 10));
    QObject::connect(viewerBougies, SIGNAL(clicked()), this, SLOT(bougiesViewerAction()));
    QObject::connect(addIndicateur, SIGNAL(clicked()), this, SLOT(addIndicateurAction()));

}

void tableCours::bougiesViewerAction(){
    try {
        QString e="Il n'y pas bougies\n à montrer", e2="Au moins 17 cours \nsont requis pour \nafficher les bougies";
        if(ec==nullptr) throw e;
        if(ec->getNbCours()<17) throw e2;
        EvolutionViewer *c=new EvolutionViewer(ec,this);
        c->showMaximized();
    } catch (const QString e) {
        resultBougies->setStyleSheet("QLabel { background-color : yellow; color : black; }");
        resultBougies->setText(e);
    }
}

 //!< Ouvrir l'interface correspondante au indicateur que l'utilisateur veut ajouter
void tableCours::addIndicateurAction(){
    QString e="Il n'y pas cours\n pour faire un indicateur";
    try {
        if(ec==nullptr) throw e;
        if(typeIndicateur->currentText()=="EMA"){
           addEMA *c=new addEMA(ec,this);
           c->setFixedSize(400,270);
           c->setModal(true);
           c->show();
        }else if(typeIndicateur->currentText()=="RSI"){
            addRSI *c=new addRSI(ec,this);
            c->setFixedSize(400,270);
            c->setModal(true);
            c->show();
        }else{
            addMACD *c=new addMACD(ec,this);
            c->setFixedSize(400,300);
            c->setModal(true);
            c->show();
        }

    } catch (const QString e) {
        resultBougies->setStyleSheet("QLabel { background-color : yellow; color : black; }");
        resultBougies->setText(e);
    }

}

void tableCours::closeAction()
{
    close();
    parentWidget()->setVisible(true);
}
