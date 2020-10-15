#include "simulationauto.h"
#include "ui_simulationauto.h"

simulationAuto::simulationAuto(Simulation& sim,DevisesManager& dManager, QDate dateD, const PaireDevises& pDev, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::simulationAuto),
    s(sim),
    dm(dManager),
    dateDebut(dateD),
    paireDev(pDev)
{
    ui->setupUi(this);
    ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
    ui->label_DBase->setText(s.getDBase());
    ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));
    ui->label_DContrepartie->setText(s.getDContrepartie());
    ui->label_DTotal->setText(s.getDContrepartie());
    ui->label_DTotal->setText(s.getDContrepartie());

    ui->label_Montant->setText("Montant en " + s.getDContrepartie());


    ui->label_TransactionHistory->setText("Historique des transactions (en " + s.getDContrepartie() + ")");

    ui->tableWidget_history->setColumnCount(4);
    QStringList titles;
    titles << "Date" << "Devise de Cotation" << "Devise de Base" << "Retour sur investissement";
    ui->tableWidget_history->setHorizontalHeaderLabels(titles);
    ui->pushButton_New->setEnabled(false);

    ui->dateEdit_debut->setMinimumDate(dateD);
    ui->dateEdit_fin->setMinimumDate(ui->dateEdit_debut->date());

    // Regler la date maximum à la date la plus haute des cours OHLCV
    QString paire = paireDev.getBase().getCode() + "/" + paireDev.getContrepartie().getCode();
    EvolutionCours* ec= nullptr;
    EvolutionCours** ecTab=dm.getCours();
    //On va obtenir le EvolutionCours que l'utilisateur veut voir selon le paire choisi
    for (unsigned int i = 0; i < dm.getNbCoursTab(); i++){
        if(ecTab[i]!=nullptr && ecTab[i]->getPaire()->toString()==paire){
            ec=ecTab[i];
            break;
        }
    }
    CoursOHLC* cours=ec->getCours();
    ui->dateEdit_fin->setMaximumDate(cours[ec->getNbCours()-1].getDate());


}

simulationAuto::~simulationAuto()
{
    delete ui;
}

void simulationAuto::on_pushButton_begin_clicked()
{
        double montant = ui->lineEdit_Montant->text().toDouble();
        QDate dateJ = QDate(ui->dateEdit_debut->date());
        dateFin = QDate(ui->dateEdit_fin->date());
        int numberDays = dateJ.daysTo(QDate(ui->dateEdit_fin->date()));
        for (unsigned int i=0; i<numberDays; i++)
        {

            try {
                if (ui->comboBox_start->currentText() == "Stratégie 1 : RSI")
                {
                    s.effectuerTransactionsRSI(montant, dateJ);

                }
                if (ui->comboBox_start->currentText() == "Stratégie 2 : EMA")
                {
                    s.effectuerTransactionsRSI(montant, dateJ);
                }
                if (ui->comboBox_start->currentText() == "Stratégie 3 : MACD")
                {
                    s.effectuerTransactionsRSI(montant, dateJ);
                }
             }
            catch (SimulationException e){}

            dateJ=dateJ.addDays(1);

        }
        for(int i=0; i<s.getNumberTransactions()-1; i++)
        {
            int index =  ui->tableWidget_history->rowCount();
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
            //On remplit le tableau
            ui->tableWidget_history->insertRow(ui->tableWidget_history->rowCount());
            ui->tableWidget_history->setItem(index, 0, new QTableWidgetItem(date));
            ui->tableWidget_history->setItem(index, 1, new QTableWidgetItem(dContrepartieCell));
            ui->tableWidget_history->setItem(index, 2, new QTableWidgetItem(dBaseCell));
            ui->tableWidget_history->setItem(index, 3, new QTableWidgetItem(QString::number(s.getROI(index+1))));

            ui->label_MTotal->setText(QString::number(s.getMontantTotalActuel(dateJ)));

    }

    ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
    ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));

    ui->pushButton_begin->setEnabled(false);
    ui->pushButton_New->setEnabled(true);
}

void simulationAuto::on_pushButton_New_clicked()
{
    s.supprimerTransactions(dateFin);
    ui->tableWidget_history->setRowCount(0);
    ui->label_MDBase->setText(QString::number(s.getDevisesBase()));
    ui->label_MDContrepartie->setText(QString::number(s.getDevisesContrepartie()));
    ui->label_MTotal->setText("");
    ui->pushButton_begin->setEnabled(true);
    ui->pushButton_New->setEnabled(false);
}

void simulationAuto::on_pushButton_Cancel_clicked()
{
    close();
    parentWidget()->setVisible(true);

}


void simulationAuto::on_dateEdit_debut_dateTimeChanged(const QDateTime &dateTime)
{
    ui->dateEdit_fin->setMinimumDate(ui->dateEdit_debut->date());
}

void simulationAuto::on_pushButton_Load_clicked()
{
    QDataStream io;
    QFile fichierSimulation;
    QDir pathf;
    //SAUVEGARDER LES DOUBLES
    pathf.cd(s.getPathSimulation());
    QString filename=pathf.path()+'/'+"autodoubles"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
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
    //cout<<"TAUX"<<taux<<"Base"<<base<<contre;
    s.setdoublesvalues(base,contre,taux);

    fichierSimulation.flush();
    fichierSimulation.close();

    //SAUVEGARDER LES VECTORS
    pathf.currentPath();
    pathf.cd(s.getPathSimulation());
    filename=pathf.path()+'/'+"autovectors"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
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



    QDate dateJ = QDate(ui->dateEdit_debut->date());
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



    filename=pathf.path()+'/'+"autotext"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
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

void simulationAuto::on_pushButton_Save_clicked()
{
    QDataStream io;
    QFile fichierSimulation;
    QDir pathf;
    //!<SAUVEGARDER LES DOUBLES
    pathf.cd(s.getPathSimulation());
    QString filename=pathf.path()+'/'+"autodoubles"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
    fichierSimulation.setFileName(filename);
    fichierSimulation.open(QIODevice::WriteOnly);
    io.setDevice(&fichierSimulation);
    io.setVersion(QDataStream::Qt_4_8);//!<IL FAUT METTRE LA VERSION QU'ON UTILISE
    io << s.getdoubleDevisesBase();
    io << s.getdoubleDevisesContrepartie();
    io << s.getTauxCommission();
    io << s.getNumberTransactions();
    fichierSimulation.flush();
    fichierSimulation.close();

    //SAUVEGARDER LES VECTORS
    pathf.cd(s.getPathSimulation());
    filename=pathf.path()+'/'+"autovectors"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
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


    filename=pathf.path()+'/'+"autotext"+s.getDBase()+'-'+s.getDContrepartie()+".txt";
    fichierSimulation.setFileName(filename);
    fichierSimulation.open(QIODevice::WriteOnly);
    io.setDevice(&fichierSimulation);
    io.setVersion(QDataStream::Qt_4_8);//IL FAUT METTRE LA VERSION QU'ON UTILISE

    QString commentaire;

    commentaire=ui->textEdit->toPlainText();
    io << commentaire;


    ui->label_error->setText("Sauvegarde réussie.");

    fichierSimulation.flush();
    fichierSimulation.close();


}
