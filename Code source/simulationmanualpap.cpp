#include "simulationmanualpap.h"
#include "ui_simulationmanualpap.h"

SimulationManualPaP::SimulationManualPaP(Simulation& sim,DevisesManager & dManager,QDate d, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulationManualPaP),
    s(sim),
    dm(dManager),
    dateJ(d)
{
    ui->setupUi(this);
    ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
    ui->label_DBase->setText(s.getDBase());
    ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));
    ui->label_DContrepartie->setText(s.getDContrepartie());
    ui->label_DTotal->setText(s.getDContrepartie());
    //ui->label_Dchange->setText(s.getDContrepartie());

    ui->label_TransactionHistory->setText("Historique des transactions (en " + s.getDContrepartie() + ")");

    ui->label_Montant->setText("Montant en " + s.getDContrepartie());

    ui->tableWidget_history->setColumnCount(4);
    QStringList titles;
    titles << "Date" << "Devise de Cotation" << "Devise de Base" << "Retour sur investissement";
    ui->tableWidget_history->setHorizontalHeaderLabels(titles);
    ui->label_OpenPrice->setText(QString::number(s.getCurrentOpen(dateJ)));
    ui->label_dateJ->setText(dateJ.toString("dd/MM/yyyy"));

    ui->dateEdit_back->setMaximumDate(dateJ);

}

SimulationManualPaP::~SimulationManualPaP()
{
    delete ui;
}

void SimulationManualPaP::on_pushButton_buy_clicked()
{
    ui->label_erreurDate->setText("");
    try {

        QString c,e="Remplissez toutes les\ninformations demandées";
        int index;
        double dBase, dContrepartie, cotation;

        cotation = 1.5;
        double montant = ui->lineEdit_Montant->text().toDouble();
        s.effectuerAchat(montant, dateJ);
        //update des textes
        ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
        ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));

        ui->label_MTotal->setText(QString::number(s.getMontantTotalActuel(dateJ)));


        dBase = s.getDevisesBase();
        dContrepartie  = s.getDevisesContrepartie();
        index =  ui->tableWidget_history->rowCount();

        QString dContrepartieCell = QString::number(s.getDeviseContrepartieIndex(index+1));
        dContrepartieCell += " + (" + QString::number(s.getDeviseContrepartieIndex(index+1) - s.getDeviseContrepartieIndex(index) ) + ")";

        QString dBaseCell = QString::number(s.getConversionDBase(index, dateJ));
        dBaseCell += " - (" + QString::number(s.getConversionDBase(index, dateJ) - s.getConversionDBase(index+1, dateJ)) + ")";

        //On remplit le tableau
        ui->tableWidget_history->insertRow(ui->tableWidget_history->rowCount());
        ui->tableWidget_history->setItem(index, 0, new QTableWidgetItem(dateJ.toString("dd/MM/yyyy")));
        ui->tableWidget_history->setItem(index, 1, new QTableWidgetItem(dContrepartieCell));
        ui->tableWidget_history->setItem(index, 2, new QTableWidgetItem(dBaseCell));
        ui->tableWidget_history->setItem(index, 3, new QTableWidgetItem(QString::number(s.getROI(index+1))));

       }
    catch (SimulationException e){
    ui->label_erreurDate->setText(e.getInfo());
    }


}

void SimulationManualPaP::on_pushButton_nextDay_clicked()
{
    ui->label_erreurDate->setText("");
    dateJ=dateJ.addDays(1);
    ui->label_dateJ->setText(dateJ.toString("dd/MM/yyyy"));
    try {
    ui->label_OpenPrice->setText(QString::number(s.getCurrentOpen(dateJ)));
    }
     catch (SimulationException e){
     ui->label_erreurDate->setText(e.getInfo());
     }
    ui->dateEdit_back->setMaximumDate(dateJ);

}

void SimulationManualPaP::on_pushButton_confirm_clicked()
{
    dateJ = QDate(ui->dateEdit_back->date());
    s.supprimerTransactions(dateJ);
    ui->tableWidget_history->setRowCount(0);
    ui->label_dateJ->setText(dateJ.toString("dd/MM/yyyy"));
    ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
    ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));
    ui->label_MTotal->setText("");

}

void SimulationManualPaP::on_pushButton_sell_clicked()
{
    ui->label_erreurDate->setText("");
    try {

        QString c,e="Remplissez toutes les\ninformations demandées";
        int index;
        double dBase, dContrepartie;
        double montant = ui->lineEdit_Montant->text().toDouble();
        s.effectuerVente(montant, dateJ);
        //update des textes
        ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
        ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));

        ui->label_MTotal->setText(QString::number(s.getMontantTotalActuel(dateJ)));


        dBase = s.getDevisesBase();
        dContrepartie  = s.getDevisesContrepartie();

        index =  ui->tableWidget_history->rowCount();

        QString dContrepartieCell = QString::number(s.getDeviseContrepartieIndex(index+1));
        dContrepartieCell += " - (" + QString::number(s.getDeviseContrepartieIndex(index) - s.getDeviseContrepartieIndex(index+1) ) + ")";

        QString dBaseCell = QString::number(s.getConversionDBase(index, dateJ));
        dBaseCell += " + (" + QString::number(s.getConversionDBase(index+1, dateJ) - s.getConversionDBase(index, dateJ)) + ")";

        //On remplit le tableau
        ui->tableWidget_history->insertRow(ui->tableWidget_history->rowCount());
        ui->tableWidget_history->setItem(index, 0, new QTableWidgetItem(dateJ.toString("dd/MM/yyyy")));
        ui->tableWidget_history->setItem(index, 1, new QTableWidgetItem(dContrepartieCell));
        ui->tableWidget_history->setItem(index, 2, new QTableWidgetItem(dBaseCell));
        ui->tableWidget_history->setItem(index, 3, new QTableWidgetItem(QString::number(s.getROI(index+1))));

       }
    catch (SimulationException e){
    ui->label_erreurDate->setText(e.getInfo());
    }

}

void SimulationManualPaP::on_pushButton_cancel_clicked()
{
    close();
    parentWidget()->setVisible(true);

}

void SimulationManualPaP::on_pushButton_save_clicked()
{
    QDataStream io;
    QFile fichierSimulation;
    QDir pathf;
    //SAUVEGARDER LES DOUBLES
    pathf.cd(s.getPathSimulation());
    QString filename=pathf.path()+'/'+"pasdoubles"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
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
    filename=pathf.path()+'/'+"pasvectors"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
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


    filename=pathf.path()+'/'+"pastext"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
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

}

void SimulationManualPaP::on_pushButton_load_clicked()
{
    QDataStream io;
    QFile fichierSimulation;
    QDir pathf;
    //SAUVEGARDER LES DOUBLES
    pathf.currentPath();
    pathf.cd(s.getPathSimulation());
    QString filename=pathf.path()+'/'+"pasdoubles"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
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
    s.setdoublesvalues(base,contre,taux);

    fichierSimulation.flush();
    fichierSimulation.close();

    //SAUVEGARDER LES VECTORS
    pathf.currentPath();
    pathf.cd(s.getPathSimulation());
    filename=pathf.path()+'/'+"pasvectors"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
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
        //std::cout<<"*******"<<base1<<contre1<<date1.toString().toStdString()<<"*******"<<endl;
        s.pushbacktabvalues(base1, contre1, date1);
        basetab.push_back(base1);
        contretab.push_back(contre1);
        datetab.push_back(date1);

    }
    fichierSimulation.flush();
    fichierSimulation.close();



    QDate dateJ = QDate(ui->dateEdit_back->date());
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



    filename=pathf.path()+'/'+"pastext"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
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

    ui->label_dateJ->setText(s.getDate(s.getNumberTransactions()).toString("dd/MM/yyyy"));

    fichierSimulation.flush();
    fichierSimulation.close();
}
