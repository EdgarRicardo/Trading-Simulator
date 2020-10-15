#include "simulationmanualc.h"
#include "ui_simulationmanualc.h"
#include "simulation.h"

SimulationManualC::SimulationManualC(Simulation& sim,DevisesManager&dManager,QDate d, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulationManualC),
    s(sim),
    dm(dManager),
    dateDebut(d)
{
    // Affiche un message d'erreur si la date est incorrecte
    erreur=new QLabel(this);
    erreur->setGeometry(20,200,150,50);
    erreur->setFont(QFont("Segoe UI Light", 10));

    double cotation;
    cotation = 1.5;

    ui->setupUi(this);
    ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
    ui->label_DBase->setText(s.getDBase());
    ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));
    ui->label_DContrepartie->setText(s.getDContrepartie());
    ui->label_DTotal->setText(s.getDContrepartie());
    ui->label_Dchange->setText(s.getDContrepartie());

    ui->label_TransactionHistory->setText("Historique des transactions (en " + s.getDContrepartie() + ")");

    ui->tableWidget_history->setColumnCount(4);
    QStringList titles;
    titles << "Date" << "Devise de Cotation" << "Devise de Base" << "Retour sur investissement";
    ui->tableWidget_history->setHorizontalHeaderLabels(titles);

    ui->pushButton_Cancel->setEnabled(false); //on désactive le bouton "annuler la dernière opération"

    ui->dateEdit_Transaction->setDate(dateDebut);



}

SimulationManualC::~SimulationManualC()
{
    delete ui;
}

void SimulationManualC::on_pushButton_Quit_clicked()
{
    close();
    parentWidget()->setVisible(true);

}

void SimulationManualC::on_pushButton_Buy_clicked()
{
    /*

    int index;
    double dBase, dContrepartie, cotation, ROI;

    cotation = 1.5;
    double montant = ui->lineEdit_Montant->text().toDouble();
    std::string date = ui->dateEdit_Transaction->date().toString("dd/MM/yyyy").toStdString();
    s.effectuerVente(montant, 1.5,  date);

    //update des textes
    ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
    ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));
    ui->label_MTotal->setText(QString::number(s.getDevisesContrepartie() + s.getDevisesBase()*cotation));



    dBase = s.getDevisesBase();
    dContrepartie  = s.getDevisesContrepartie();
    ROI = (dBase*cotation + dContrepartie) /(s.getDeviseBaseInitiales()*cotation + s.getDeviseContrepartieInitiales());

    index =  ui->tableWidget_history->rowCount();
    QString dContrepartieCell = QString::number(s.getDeviseContrepartieIndex(index));
    dContrepartieCell += " + (" + QString::number(montant -montant*s.getTauxCommission()) + ")";

    QString dBaseCell = QString::number(s.getDeviseBaseIndex(index)*cotation);
    dBaseCell += " - (" + QString::number(montant) + ")";

    //On remplit le tableau
    ui->tableWidget_history->insertRow(ui->tableWidget_history->rowCount());
    ui->tableWidget_history->setItem(index, 0, new QTableWidgetItem(QString::fromStdString(date)));
    ui->tableWidget_history->setItem(index, 1, new QTableWidgetItem(dContrepartieCell));
    ui->tableWidget_history->setItem(index, 2, new QTableWidgetItem(dBaseCell));
    ui->tableWidget_history->setItem(index, 3, new QTableWidgetItem(QString::number(ROI)));

    ui->pushButton_Cancel->setEnabled(true); //on active le bouton "annuler la dernière opération"
*/

    ui->label_erreurDate->setText("");
    try {

        QString c,e="Remplissez toutes les\ninformations demandées";
        int index;
        double dBase, dContrepartie, cotation, ROI;

        cotation = 1.5;
        double montant = ui->lineEdit_Montant->text().toDouble();
        std::string date = ui->dateEdit_Transaction->date().toString("dd/MM/yyyy").toStdString();
        s.effectuerAchat(montant, QDate(ui->dateEdit_Transaction->date()));
        //update des textes
        ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
        ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));

        ui->label_MTotal->setText(QString::number(s.getMontantTotalActuel(QDate(ui->dateEdit_Transaction->date()))));


        dBase = s.getDevisesBase();
        dContrepartie  = s.getDevisesContrepartie();
        ROI = (dBase*cotation + dContrepartie) /(s.getDeviseBaseInitiales()*cotation + s.getDeviseContrepartieInitiales());

        index =  ui->tableWidget_history->rowCount();

        QString dContrepartieCell = QString::number(s.getDeviseContrepartieIndex(index+1));
        dContrepartieCell += " + (" + QString::number(s.getDeviseContrepartieIndex(index+1) - s.getDeviseContrepartieIndex(index) ) + ")";

        QString dBaseCell = QString::number(s.getConversionDBase(index, QDate(ui->dateEdit_Transaction->date())));
        dBaseCell += " - (" + QString::number(s.getConversionDBase(index+1, QDate(ui->dateEdit_Transaction->date())) - s.getConversionDBase(index, QDate(ui->dateEdit_Transaction->date()))) + ")";

        //On remplit le tableau
        ui->tableWidget_history->insertRow(ui->tableWidget_history->rowCount());
        ui->tableWidget_history->setItem(index, 0, new QTableWidgetItem(QString::fromStdString(date)));
        ui->tableWidget_history->setItem(index, 1, new QTableWidgetItem(dContrepartieCell));
        ui->tableWidget_history->setItem(index, 2, new QTableWidgetItem(dBaseCell));
        ui->tableWidget_history->setItem(index, 3, new QTableWidgetItem(QString::number(s.getROI(index+1))));

        ui->pushButton_Cancel->setEnabled(true); //on active le bouton "annuler la dernière opération"
       }
    catch (SimulationException e){
    ui->label_erreurDate->setText(e.getInfo());}


}


void SimulationManualC::on_pushButton_Sell_clicked()
{


    ui->label_erreurDate->setText("");
    try {
        int index;
        double dBase, dContrepartie, cotation, ROI;

        cotation = 1.5;
        double montant = ui->lineEdit_Montant->text().toDouble();
        std::string date = ui->dateEdit_Transaction->date().toString("dd/MM/yyyy").toStdString();
        s.effectuerVente(montant, QDate(ui->dateEdit_Transaction->date()));

        //update des textes
        ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
        ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));
        ui->label_MTotal->setText(QString::number(s.getMontantTotalActuel(QDate(ui->dateEdit_Transaction->date()))));



        dBase = s.getDevisesBase();
        dContrepartie  = s.getDevisesContrepartie();
        ROI = (dBase*cotation + dContrepartie) /(s.getDeviseBaseInitiales()*cotation + s.getDeviseContrepartieInitiales());

        index =  ui->tableWidget_history->rowCount();

        QString dContrepartieCell = QString::number(s.getDeviseContrepartieIndex(index+1));
        dContrepartieCell += " - (" + QString::number(s.getDeviseContrepartieIndex(index+1) - s.getDeviseContrepartieIndex(index) ) + ")";

        QString dBaseCell = QString::number(s.getConversionDBase(index+1, QDate(ui->dateEdit_Transaction->date())));
        dBaseCell += " + (" + QString::number(s.getConversionDBase(index+1, QDate(ui->dateEdit_Transaction->date())) - s.getConversionDBase(index, QDate(ui->dateEdit_Transaction->date())) ) + ")";

        //On remplit le tableau
        ui->tableWidget_history->insertRow(ui->tableWidget_history->rowCount());
        ui->tableWidget_history->setItem(index, 0, new QTableWidgetItem(QString::fromStdString(date)));
        ui->tableWidget_history->setItem(index, 1, new QTableWidgetItem(dContrepartieCell));
        ui->tableWidget_history->setItem(index, 2, new QTableWidgetItem(dBaseCell));
        ui->tableWidget_history->setItem(index, 3, new QTableWidgetItem(QString::number(s.getROI(index+1))));

        ui->pushButton_Cancel->setEnabled(true); //on active le bouton "annuler la dernière opération"
       }
    catch (SimulationException e){
    ui->label_erreurDate->setText(e.getInfo());}

}



void SimulationManualC::on_pushButton_Cancel_clicked()
{

    double cotation = 1.5;

    ui->tableWidget_history->removeRow(ui->tableWidget_history->rowCount()-1);
    ui->pushButton_Cancel->setEnabled(false);

    s.annulerDerniereOperation();

    //update des textes
    ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
    ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));
    ui->label_MTotal->setText(QString::number(s.getDevisesContrepartie() + s.getDevisesBase()*cotation));

}

void SimulationManualC::on_pushButton_Load_clicked()
{
    QDataStream io;
    QFile fichierSimulation;
    QDir pathf;
    //SAUVEGARDER LES DOUBLES
    pathf.cd(s.getPathSimulation());
    QString filename=pathf.path()+'/'+"manudoubles"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
    fichierSimulation.setFileName(filename);
    fichierSimulation.open(QIODevice::ReadOnly);
    io.setDevice(&fichierSimulation);
    io.setVersion(QDataStream::Qt_4_8);//IL FAUT METTRE LA VERSION QU'ON UTILISE
    double base, contre, taux;
    int indicetabBase;
    io >> base;
    io >> contre;
    io >> taux;
    io >> indicetabBase;
    cout<<"TAUX"<<taux<<"Base"<<base<<contre;
    s.setdoublesvalues(base,contre,taux);

    fichierSimulation.flush();
    fichierSimulation.close();

    //SAUVEGARDER LES VECTORS
    pathf.cd(s.getPathSimulation());
    filename=pathf.path()+'/'+"manuvectors"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
    fichierSimulation.setFileName(filename);
    fichierSimulation.open(QIODevice::ReadOnly);
    io.setDevice(&fichierSimulation);
    io.setVersion(QDataStream::Qt_4_8);//IL FAUT METTRE LA VERSION QU'ON UTILISE

    double base1;
    double contre1;
    QDate date1;
    vector <double> basetab;
    vector <double> contretab;
    vector <QDate> datetab;


    for(int k=0;k<indicetabBase;k++){

        io >> base1;
        io >> contre1;
        io >> date1;
        std::cout<<"*******"<<base1<<contre1<<date1.toString().toStdString()<<"*******"<<endl;
        s.pushbacktabvalues(base1, contre1, date1);
        basetab.push_back(base1);
        contretab.push_back(contre1);
        datetab.push_back(date1);

    }
    fichierSimulation.flush();
    fichierSimulation.close();



    QDate dateJ = QDate(ui->dateEdit_Transaction->date());
    //!<dateJ=s.getDate(0);


    for(int i=0; i<s.getNumberTransactions()-1; i++)
    {
        int index = i;

        int indexSup = index+1;
        QString symboleC = " +";
        QString symboleB = " -";

        if (s.getDeviseContrepartieIndex(indexSup) - s.getDeviseContrepartieIndex(index) < 0)
        {
            symboleC = " -";
            QString symboleB = " +";
        }
        QString dContrepartieCell;
        QString dBaseCell ;
        dContrepartieCell = QString::number(s.getDeviseContrepartieIndex(indexSup));
        dContrepartieCell += symboleC + " (" + QString::number(s.getDeviseContrepartieIndex(indexSup) - s.getDeviseContrepartieIndex(index) ) + ")";
        dBaseCell = QString::number(s.getConversionDBase(indexSup, QDate(s.getDate(indexSup))));
        dBaseCell += symboleB + " (" + QString::number(s.getConversionDBase(indexSup, QDate(s.getDate(indexSup))) - s.getConversionDBase(index, QDate(s.getDate(index))) ) + ")";
        QString date = s.getDate(index).toString("dd/MM/yyyy");
        //!< On remplit le tableau
        ui->tableWidget_history->insertRow(i);
        ui->tableWidget_history->setItem(i, 0, new QTableWidgetItem(date));
        ui->tableWidget_history->setItem(i, 1, new QTableWidgetItem(dContrepartieCell));
        ui->tableWidget_history->setItem(i, 2, new QTableWidgetItem(dBaseCell));
        ui->tableWidget_history->setItem(i, 3, new QTableWidgetItem(QString::number(s.getROI(index+1))));
    }



    filename=pathf.path()+'/'+"manutext"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
    fichierSimulation.setFileName(filename);
    fichierSimulation.open(QIODevice::ReadOnly);
    io.setDevice(&fichierSimulation);
    io.setVersion(QDataStream::Qt_4_8);//IL FAUT METTRE LA VERSION QU'ON UTILISE

    QString commentaire;

    io >> commentaire;
    ui->textEdit->setText(commentaire);

    ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
    ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));

    ui->label_MTotal->setText(QString::number(s.getMontantTotalActuel(s.getDate(s.getNumberTransactions()-1))));

    fichierSimulation.flush();
    fichierSimulation.close();


}

void SimulationManualC::on_pushButton_Save_clicked()
{

    QDataStream io;
    QFile fichierSimulation;
    QDir pathf;
    //SAUVEGARDER LES DOUBLES
    pathf.cd(s.getPathSimulation());
    QString filename=pathf.path()+'/'+"manudoubles"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
    fichierSimulation.setFileName(filename);
    fichierSimulation.open(QIODevice::WriteOnly);
    io.setDevice(&fichierSimulation);
    io.setVersion(QDataStream::Qt_4_8);//IL FAUT METTRE LA VERSION QU'ON UTILISE
    io << s.getdoubleDevisesBase();
    io << s.getdoubleDevisesContrepartie();
    io << s.getTauxCommission();
    io << s.getNumberTransactions();
    fichierSimulation.flush();
    fichierSimulation.close();

    //SAUVEGARDER LES VECTORS
    pathf.cd(s.getPathSimulation());
    filename=pathf.path()+'/'+"manuvectors"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
    fichierSimulation.setFileName(filename);
    fichierSimulation.open(QIODevice::WriteOnly);
    io.setDevice(&fichierSimulation);
    io.setVersion(QDataStream::Qt_4_8);//IL FAUT METTRE LA VERSION QU'ON UTILISE

    int indicetabBase=s.getNumberTransactions();
    //while(s.getDeviseBaseIndex(indice)||(s.getDeviseContrepartieIndex(indice)!=NULL))
    for(int k=0;k<indicetabBase;k++){
        io<< s.getDeviseBaseIndex(k);
        io<< s.getDeviseContrepartieIndex(k);
        io<< s.getDate(k);
    }

    fichierSimulation.flush();
    fichierSimulation.close();


    filename=pathf.path()+'/'+"manutext"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
    fichierSimulation.setFileName(filename);
    fichierSimulation.open(QIODevice::WriteOnly);
    io.setDevice(&fichierSimulation);
    io.setVersion(QDataStream::Qt_4_8);//IL FAUT METTRE LA VERSION QU'ON UTILISE

    QString commentaire;

    commentaire=ui->textEdit->toPlainText();
    io << commentaire;

    ui->label_erreurDate->setText("Sauvegarde réussie.");


    fichierSimulation.flush();
    fichierSimulation.close();

    //!< s.garderDeviseManager();

}
