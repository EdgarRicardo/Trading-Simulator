#include "modeselection.h"
#include "ui_modeselection.h"


ModeSelection::ModeSelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeSelection)
{
    ui->setupUi(this);
}

ModeSelection::~ModeSelection()
{
    delete ui;
}

void ModeSelection::on_okButton_clicked()
{
    if(ui->radioButton_CSV->isChecked())
    {
        DevisesManager& dm=DevisesManager::getManager();
        Menucsv *m= new Menucsv(dm,this);
        m->setFixedSize(800,500);
        m->show();
    }
    if(ui->radioButton_Manual->isChecked())
    {
        DevisesManager& dm=DevisesManager::getManager();
        dm.creationDevise("ARS", "Argentina","Argentina");
        dm.creationDevise("AZN", "Manat azerbaiyano","Azerbaiyano");
        const PaireDevises& BTC_USD=dm.getPaireDevises("ARS", "AZN");
        //!<  Une bougie = Un mois pour bitcoin entre janvier 2017 et août 2018
        dm.creerCoursDevise(&BTC_USD,4261.48000000,4745.42000000,3400.00000000,4745.42000000,15000,QDate(2017,1,1));
        dm.creerCoursDevise(&BTC_USD,4689.89000000,4939.19000000,2817.00000000,4378.51000000,11000,QDate(2017,2,1));
        dm.creerCoursDevise(&BTC_USD,4378.49000000,6498.01000000,4110.00000000,6463.00000000,9000,QDate(2017,3,1));
        dm.creerCoursDevise(&BTC_USD,6463.00000000,11300.03000000,5325.01000000,9838.96000000,7500,QDate(2017,4,1));
        dm.creerCoursDevise(&BTC_USD,9837.00000000,19798.68000000,9380.00000000,13716.36000000,18901,QDate(2017,5,1));
        dm.creerCoursDevise(&BTC_USD,13715.65000000,17176.24000000,9035.00000000,10285.10000000,15500,QDate(2017,6,1));
        dm.creerCoursDevise(&BTC_USD,10285.10000000,11786.01000000,6000.01000000,10326.76000000,10640,QDate(2017,7,1));
        dm.creerCoursDevise(&BTC_USD,10325.64000000,11710.00000000,6600.10000000,6923.91000000,14310,QDate(2017,8,1));
        dm.creerCoursDevise(&BTC_USD,6922.00000000,9759.82000000,6430.00000000,9246.01000000,10200,QDate(2017,9,1));
        dm.creerCoursDevise(&BTC_USD,9246.01000000,10020.00000000,7032.95000000,7485.01000000,10010,QDate(2017,10,1));
        dm.creerCoursDevise(&BTC_USD,7485.01000000,7786.69000000,5750.00000000,6390.07000000,10080,QDate(2017,11,1));
        dm.creerCoursDevise(&BTC_USD,6391.08000000,8491.77000000,6070.00000000,7730.93000000,10900,QDate(2017,12,1));
        dm.creerCoursDevise(&BTC_USD,7735.67000000,7750.00000000,5880.00000000,7011.21000000,17800,QDate(2018,1,1));
        dm.creerCoursDevise(&BTC_USD,7011.21000000,7410.00000000,6111.00000000,6626.57000000,11200,QDate(2018,2,1));
        dm.creerCoursDevise(&BTC_USD,6626.57000000,7680.00000000,6205.00000000,6371.93000000,10000,QDate(2018,3,1));
        dm.creerCoursDevise(&BTC_USD,6369.52000000,6615.15000000,3652.66000000,4041.32000000,12000,QDate(2018,4,1));
        dm.creerCoursDevise(&BTC_USD,4041.27000000,4312.99000000,3156.26000000,3702.90000000,13300,QDate(2018,5,1));
        dm.creerCoursDevise(&BTC_USD,3701.23000000,4069.80000000,3349.92000000,3434.10000000,16487,QDate(2018,6,1));
        dm.creerCoursDevise(&BTC_USD,3434.10000000,4198.00000000,3373.10000000,3813.69000000,12020,QDate(2018,7,1));
        dm.creerCoursDevise(&BTC_USD,3814.26000000,4140.00000000,3670.69000000,4106.65000000,19060,QDate(2018,8,1));
        dm.creerCoursDevise(&BTC_USD,814.26000000,940.00000000,170.69000000,306.65000000,1060,QDate(2018,9,1));
        dm.creerCoursDevise(&BTC_USD,214.26000000,340.00000000,170.69000000,306.65000000,1060,QDate(2018,10,1));
        dm.creerCoursDevise(&BTC_USD,7514.26000000,18400.00000000,7510.69000000,9806.65000000,29061,QDate(2018,11,1));
        dm.creerCoursDevise(&BTC_USD,7514.26000000,18400.00000000,6510.69000000,9806.65000000,29061,QDate(2018,12,1));
        dm.creerCoursDevise(&BTC_USD,7514.26000000,18400.00000000,9510.69000000,9806.65000000,29061,QDate(2019,1,1));
        Menu *m=new Menu(dm,this);
        m->setFixedSize(800,300);
        m->setWindowModality(Qt::ApplicationModal);
        m->show();
    }

}

void ModeSelection::on_quitButton_clicked()
{
    close();
}
