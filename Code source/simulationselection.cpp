#include "simulationselection.h"
#include "ui_simulationselection.h"
#include "simulationmanualpap.h"
#include "simulationauto.h"



SimulationSelection::SimulationSelection(DevisesManager& dManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationSelection),
    dm(dManager)
{
    ui->setupUi(this);
    PaireDevises** par= dm.getPaires();
    for (unsigned int i = 0; i < dm.getNbPaires(); i++){
        if(par[i]!=nullptr)
        ui->comboBox_PaireDevises->addItem(par[i]->toString());
     }
    ui->lineEdit_dContrepartie->setText("1000000");
    ui->lineEdit_dBase->setText("0");
    ui->lineEdit_commission->setText("0.001");
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);



}

SimulationSelection::~SimulationSelection()
{
    delete ui;
}

void SimulationSelection::on_pushButton_Ok_clicked()
{
    ui->label_erreur->setText("");
    if(ui->radioButton_Manual->isChecked())
    {
        std::string paire=ui->comboBox_PaireDevises->currentText().toStdString();
        double dContrepartie = ui->lineEdit_dContrepartie->text().toDouble();
        double dBase = ui->lineEdit_dBase->text().toDouble();
        double commission = ui->lineEdit_commission->text().toDouble();
        QDate date = ui->dateEdit->date();

        QString c,e="Veuillez remplir toutes \nles informations demandées";
        c= ui->comboBox_PaireDevises->currentText();
        QString dB = ui->lineEdit_dBase->text();
        QString dC = ui->lineEdit_dContrepartie->text();
        QString Comm = ui->lineEdit_commission->text();
        try {
            if(c.isEmpty() || dB.isEmpty() || dC.isEmpty() || Comm.isEmpty() || date.isNull()) throw e;
            const PaireDevises& pDevise = dm.recupererPaire(c);

            Simulation s(dContrepartie, dBase,commission, date, pDevise, dm);
            s.setPathSimulation(dir);
            SimulationManualC *sm= new SimulationManualC(s, dm,date, this);
            sm->show();
        }
        catch(const QString e){
            ui->label_erreur->setText(e);
        }catch (TradingException e){
            ui->label_erreur->setText(e.getInfo());
        }



    }

    if(ui->radioButton_ManualPP->isChecked())
    {
        std::string paire=ui->comboBox_PaireDevises->currentText().toStdString();
        double dContrepartie = ui->lineEdit_dContrepartie->text().toDouble();
        double dBase = ui->lineEdit_dBase->text().toDouble();
        double commission = ui->lineEdit_commission->text().toDouble();
        QDate date = QDate(ui->dateEdit->date());

        QString c,e="Veuillez remplir toutes \nles informations demandées";
        c= ui->comboBox_PaireDevises->currentText();
        QString dB = ui->lineEdit_dBase->text();
        QString dC = ui->lineEdit_dContrepartie->text();
        QString Comm = ui->lineEdit_commission->text();
        try {
            if(c.isEmpty() || dB.isEmpty() || dC.isEmpty() || Comm.isEmpty() || date.isNull()) throw e;
            const PaireDevises& pDevise = dm.recupererPaire(c);

            Simulation s(dContrepartie, dBase,commission, date, pDevise, dm);
            s.setPathSimulation(dir);
            SimulationManualPaP *smpp= new SimulationManualPaP(s, dm, date, this);
            smpp->show();
        }
        catch(const QString e){
            ui->label_erreur->setText(e);
        }catch (TradingException e){
            ui->label_erreur->setText(e.getInfo());
        }

    }

    if(ui->radioButton_Auto->isChecked())
    {
        std::string paire=ui->comboBox_PaireDevises->currentText().toStdString();
        double dContrepartie = ui->lineEdit_dContrepartie->text().toDouble();
        double dBase = ui->lineEdit_dBase->text().toDouble();
        double commission = ui->lineEdit_commission->text().toDouble();
        QDate date = ui->dateEdit->date();

        QString c,e="Veuillez remplir toutes \nles informations demandées";
        c= ui->comboBox_PaireDevises->currentText();
        QString dB = ui->lineEdit_dBase->text();
        QString dC = ui->lineEdit_dContrepartie->text();
        QString Comm = ui->lineEdit_commission->text();

        QString mode;
        try {
            if(c.isEmpty() || dB.isEmpty() || dC.isEmpty() || Comm.isEmpty() || date.isNull()) throw e;
            const PaireDevises& pDevise = dm.recupererPaire(c);

            Simulation s(dContrepartie, dBase,commission, date, pDevise, dm);
            s.setPathSimulation(dir);
            simulationAuto *sa= new simulationAuto(s, dm, date, pDevise, this);
            sa->show();
        }
        catch(const QString e){
            ui->label_erreur->setText(e);
        }catch (TradingException e){
            ui->label_erreur->setText(e.getInfo());
        }

    }
    this->setVisible(false);


}

void SimulationSelection::on_pushButton_Cancel_clicked()
{
    close();
}

void SimulationSelection::on_comboBox_PaireDevises_currentTextChanged(const QString &arg1)
{
    EvolutionCours* ec= nullptr;
    EvolutionCours** ecTab=dm.getCours();
    //On va obtenir le EvolutionCours que l'utilisateur veut voir selon le paire choisi
    for (unsigned int i = 0; i < dm.getNbCoursTab(); i++){
        if(ecTab[i]!=nullptr && ecTab[i]->getPaire()->toString()==arg1){
            ec=ecTab[i];
            break;
        }
    }

    CoursOHLC* cours=ec->getCours();
    ui->dateEdit->setDate(cours[0].getDate());
    ui->dateEdit->setMinimumDate(cours[0].getDate());

}
