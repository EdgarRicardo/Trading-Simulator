#include "simulation.h"

void Simulation::effectuerAchat(double dContrepartie, const QDate& date)
{

    double cotation;
    const QDate d = date;
    const CoursOHLC* c = dm.getCoursDevise(&paireDev, d);
    if (c == nullptr) throw SimulationException("Il n'y a pas de cours OHLC pour cette date");
    cotation = c->getOpen();

    double dBase = dContrepartie/cotation;
    if ( (devisesBase - dBase) < 0) throw SimulationException("Vous n'avez pas assez de devises de bases pour effectuer la transaction");
    dContrepartie = dContrepartie - dContrepartie*tauxCommission;
    devisesContrepartie = devisesContrepartie + dContrepartie;
    devisesBase -= dBase;
    tabDevisesBase.push_back(devisesBase);
    dateTransactions.push_back(date);
    tabDevisesContrepartie.push_back(devisesContrepartie);
}

void Simulation::effectuerVente(double dContrepartie, const QDate& date)
{

    double cotation;

    const CoursOHLC* c = dm.getCoursDevise(&paireDev, date);
    if (c == nullptr) throw SimulationException("Il n'y a pas de cours OHLC pour cette date");

    cotation = c->getOpen();

    double dBase = dContrepartie/cotation;
    dBase = dBase - dBase*tauxCommission;
    if ( (devisesContrepartie - dContrepartie) < 0) throw SimulationException("Vous n'avez pas assez de devises de contrepartie pour effectuer la transaction");
    devisesBase = devisesBase + dBase;
    devisesContrepartie -= dContrepartie;
    tabDevisesBase.push_back(devisesBase);
    dateTransactions.push_back(date);
    tabDevisesContrepartie.push_back(devisesContrepartie);
}

void Simulation::annulerDerniereOperation(){
    tabDevisesBase.pop_back();
    tabDevisesContrepartie.pop_back();
    dateTransactions.pop_back();
}


double Simulation::getMontantTotalActuel(const QDate& date) const
{
    double cotation;

    const CoursOHLC* c = dm.getCoursDevise(&paireDev, date);
    if (c == nullptr) throw SimulationException("Il n'y a pas de cours OHLC pour cette date");
    cotation = c->getClose();
    double montantTotal = (devisesBase*cotation + devisesContrepartie);
    return montantTotal;
}

double Simulation::getConversionDBase(unsigned int index, const QDate& date) const
{
    double cotation;

    const CoursOHLC* c = dm.getCoursDevise(&paireDev, date);
    if (c == nullptr) throw SimulationException("Il n'y a pas de cours OHLC pour cette date");
    cotation = c->getClose();
    double conversion = tabDevisesBase[index]*cotation;
    return conversion;

}

void Simulation::supprimerTransactions(const QDate& date)
{
    devisesBase = tabDevisesBase[0];
    devisesContrepartie = tabDevisesContrepartie[0];
    QDate dateI = dateTransactions[0];
    for (int i=0; i<dateTransactions.size(); i++)
    {
        if(date>dateTransactions[i])
        {
            dateTransactions.erase(dateTransactions.begin()+i);
            tabDevisesBase.erase(tabDevisesBase.begin()+i);
            tabDevisesContrepartie.erase(tabDevisesContrepartie.begin()+i);
            i--;
        }
    }
    dateTransactions.push_back(dateI); // on ajoute les valeurs de date, dBase, dContrepartie à leur liste respectif
    tabDevisesBase.push_back(devisesBase);
    tabDevisesContrepartie.push_back(devisesContrepartie);
}

double Simulation::getCurrentOpen(const QDate& date)
{
    const CoursOHLC* c = dm.getCoursDevise(&paireDev, date);
    if (c == nullptr) throw SimulationException("Il n'y a pas de cours OHLC pour cette date");

    return c->getOpen();
}

void Simulation::effectuerTransactionsRSI(double dContrepartie, const QDate& date)
{

    const CoursOHLC* c = dm.getCoursDevise(&paireDev, date);
    if ( c == nullptr) {throw SimulationException("Il n'y a pas de cours OHLC pour cette date");}
    else {
        double RSI = c->getRSI();

        if(RSI < 20 )
        {
           effectuerAchat(dContrepartie, date);
        }
        else if (RSI>80)
        {
            effectuerVente(dContrepartie, date);
        }
}

}

void Simulation::effectuerTransactionsEMA(double dContrepartie, const QDate& date)
{
    const CoursOHLC* c = dm.getCoursDevise(&paireDev, date);
    if ( c == nullptr) {throw SimulationException("Il n'y a pas de cours OHLC pour cette date");}
    else {
    double EMA = c->getEMA26();

    if(EMA > c->getOpen() )
    {
       effectuerAchat(dContrepartie, date);
    }
    else if (EMA < c->getOpen())
    {
        effectuerVente(dContrepartie, date);
    }
}
}


void Simulation::effectuerTransactionsMACD(double dContrepartie, const QDate& date)
{
    const CoursOHLC* c = dm.getCoursDevise(&paireDev, date);
    if ( c == nullptr) {throw SimulationException("Il n'y a pas de cours OHLC pour cette date");}
    else {
    double MACD = c->getMACD();

    if(MACD > c->getOpen() )
    {
       effectuerAchat(dContrepartie, date);
    }
    else if (MACD < c->getOpen())
    {
        effectuerVente(dContrepartie, date);
    }
    }
}


double Simulation::getROI(int index) const
{
    const CoursOHLC* c = dm.getCoursDevise(&paireDev, dateTransactions[index]);
    if ( c == nullptr) {}
    else {
        double cotation = c->getClose();
        return (tabDevisesBase[index]*cotation + tabDevisesContrepartie[index]) /(tabDevisesBase[0]*cotation + tabDevisesContrepartie[0]);
    }

}

void Simulation::garderDeviseManager(){
/*
    //SAUVEGARDER LE DEVISE MANAGER
    QDataStream io;
    QFile fichierSimulation;
    QDir pathf;
    pathf.currentPath();
    pathf.cd("..");
    pathf.cd("OHLC");
    pathf.cd("Database");
    QString filename=pathf.path()+'/'+"manudevisem"+paireDev.getBase().getCode()+'-'+paireDev.getContrepartie().getCode()+".txt";
    fichierSimulation.setFileName(filename);
    fichierSimulation.open(QIODevice::WriteOnly);
    io.setDevice(&fichierSimulation);
    io.setVersion(QDataStream::Qt_4_8);//IL FAUT METTRE LA VERSION QU'ON UTILISE


    EvolutionCours** ecTab=dm.getCours();




    fichierSimulation.flush();
    fichierSimulation.close();



*/


}
