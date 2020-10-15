#include "trading.h"
#include <iostream>

Devise::Devise(const QString& c, const QString& m, const QString& z) :
    monnaie(m), zone(z) {
    if (c.size() > 4) throw TradingException("Code devise incorrect");
    for (int i = 0; i < c.length(); i++) {
        if (c[i] < 'A' || c[i] > 'Z') throw TradingException("Code devise incorrect");

    }
    code=c;
}

PaireDevises::PaireDevises(const Devise& b, const Devise& c, const QString& s) :
    base(&b), contrepartie(&c), surnom(s) {}


QString PaireDevises::toString() const{
    QString str;
    str=getBase().getCode()+"/"+getContrepartie().getCode();
    if (getSurnom()!="") str+="("+getSurnom()+")";
    return str;
}

void CoursOHLC::setCours(double o, double h, double l, double c) {
    if (o < 0 || h < 0 || l < 0 || c<0 || l>h) throw TradingException("cours OHLC incorrect");
        open = o; high = h; low = l; close = c;
}

CoursOHLC::CoursOHLC(double o, double h, double l, double c, double v,const QDate& d):date(d) {
    if (o < 0 || h < 0 || l < 0 || c<0 || l>h) throw TradingException("cours OHLC incorrect");
        open = o; high = h; low = l; close = c; volume=v;
}


void EvolutionCours::addCours(double o, double h, double l, double c, double v,const QDate& d) {
    if (nbMaxCours == nbCours) { // agrandissement du tableau
        CoursOHLC* newtab = new CoursOHLC[nbMaxCours + 100];
        for (unsigned int i = 0; i < nbCours; i++){
            if(&cours[i]!=nullptr)
            newtab[i] = cours[i];
        }
        // mise à jour des attributs
        CoursOHLC* old = cours;
        cours = newtab;
        nbMaxCours += 100;
        delete[] old; // destruction de l'ancien tableau
    }
    // ajout du cours
    cours[nbCours].setCours(o, h, l, c);
    cours[nbCours].setVolume(v);
    cours[nbCours].setDate(d);
    nbCours++;
    updateIndicateurs();
}

EvolutionCours::~EvolutionCours() {
    delete[] cours;
}

EvolutionCours::EvolutionCours(const EvolutionCours& e) :
    paire(e.paire),
    cours(new CoursOHLC[e.nbCours]),
    nbCours(e.nbCours),
    nbMaxCours(e.nbCours)
{
    for (unsigned int i = 0; i < nbCours; i++) cours[i] = e.cours[i];
}

EvolutionCours& EvolutionCours::operator=(const EvolutionCours& e) {
    if (this != &e) { // se protéger de l'ato-affectation
        paire = e.paire;
        nbCours = 0;
        for (unsigned int i = 0; i < e.nbCours; i++)
            addCours(e.cours[i].getOpen(), e.cours[i].getHigh(),e.cours[i].getLow(),e.cours[i].getClose(), e.cours[i].getVolume(),e.cours[i].getDate());
    }
    return *this;
}

const Devise& DevisesManager::creationDevise(const QString& c, const QString& m, const QString& z) {
    if (nbDevises == nbMaxDevises) { // agrandissement tableau
        Devise** newtab = new Devise*[nbMaxDevises + 10];
        for (unsigned int i = 0; i < nbDevises; i++){
            while(devises[i]==nullptr) i++;
            newtab[i] = devises[i];
        }
        // mise à jour des attributs
        Devise** old = devises;
        nbMaxDevises += 10;
        devises = newtab;
        delete[] old;
    }
    //Verification pour eviter les doublons
    for (unsigned int i = 0; i < nbDevises; i++)
        if(!QString::compare(c,devises[i]->getCode()))
            throw TradingException("La devise existe déjà");

    // création et ajout de la nouvelle devise...
    devises[nbDevises] = new Devise(c, m, z);
    return *devises[nbDevises++];
}

const Devise& DevisesManager::getDevise(const QString& c)const {
    for (unsigned int i = 0; i < nbDevises; i++)
        if (devises[i]->getCode() == c) {return *devises[i];}
    throw TradingException("devise inexistante");
}

const PaireDevises& DevisesManager::getPaireDevises(const QString & c1, const QString & c2){
    const Devise& d1 = getDevise(c1);
    const Devise& d2 = getDevise(c2);
    for (unsigned int i = 0; i < nbPaires; i++){
        while(paires[i]==nullptr) i++;
        if (paires[i]->getBase().getCode() == c1 && paires[i]->getContrepartie().getCode() == c2)
            return *paires[i];
    }
    // si la paire de devises n'est pas trouvée, il faut la créer
    if (nbPaires == nbMaxPaires) { // agrandissement du tableau
        PaireDevises** newtab = new PaireDevises*[nbMaxPaires + 10];
        for (unsigned int i = 0; i < nbPaires; i++){
            while(paires[i]==nullptr) i++;
            newtab[i] = paires[i];
        }

        PaireDevises** old = paires;
        nbMaxPaires += 10;
        paires = newtab;
        delete[] old;
    }

    for (unsigned int i = 0; i < nbPaires; i++){
        //while(paires[i]==nullptr) i++;
        if (paires[i]->getBase().getCode() == c2 && paires[i]->getContrepartie().getCode() == c1)
            throw TradingException("Le paire de devise \nexiste déjà");
    }

    paires[nbPaires] = new PaireDevises(d1, d2);
    return *paires[nbPaires++];
}

EvolutionCours* DevisesManager::creerCoursDevise(const PaireDevises*pDevise,double o, double h, double l, double c, double v,const QDate& d){


    const CoursOHLC *existe=getCoursDevise(pDevise,d);
    if(existe!=nullptr)
        throw TradingException("Ce cours existe deja");

    // si le cours n'est pas trouvé, il faut le créer
    if (nbECoursTab == nbMaxECoursTab) { // agrandissement du tableau
        unsigned int j=0;
        EvolutionCours** newtab = new EvolutionCours*[nbMaxPaires + 10];
        for (unsigned int i = 0; i < nbECoursTab; i++){
            //while(ecoursTab[i]==nullptr) i++;
            newtab[j] = ecoursTab[i];
            j++;
        }

        EvolutionCours** old = ecoursTab;
        nbMaxECoursTab += 10;
        ecoursTab = newtab;
        delete[] old;
    }

    //Cas ou le paire existe deja et seulement on va ajouter le cours
    for (unsigned int i = 0; i < nbECoursTab; i++){
        if(ecoursTab[i]->getPaireDevises().toString()==pDevise->toString()){
             ecoursTab[i]->addCours(o,h,l,c,v,d);
             return ecoursTab[i];
        }
    }

    ecoursTab[nbECoursTab] = new EvolutionCours(*pDevise);
    ecoursTab[nbECoursTab]->addCours(o,h,l,c,v,d);
    return ecoursTab[nbECoursTab++];
}

const CoursOHLC* DevisesManager::getCoursDevise(const PaireDevises*pDevise,const QDate& d) const{
    //double op,hi,lo,cl;

    for (unsigned int i = 0; i < nbECoursTab; i++){
            if(ecoursTab[i]->getPaireDevises().toString()==pDevise->toString()){
                for (EvolutionCours::iterator it=ecoursTab[i]->begin();it!=ecoursTab[i]->end();++it){
                    CoursOHLC &coursX=*it;
                    if (coursX.getDate().toString()==d.toString())
                            return &coursX;
                }
            }
    }
    return nullptr;
}



DevisesManager::~DevisesManager() {
    for (unsigned int i = 0; i < nbPaires; i++) delete paires[i];
    for (unsigned int i = 0; i < nbDevises; i++) delete devises[i];
    delete[] paires; delete[] devises;
}

DevisesManager::Handler DevisesManager::handler=DevisesManager::Handler();

const PaireDevises& DevisesManager::recupererPaire(QString c){
     QString base, contrepartie;
     int pos=3;
     for(int k=0;k<c.length();k++){
         if(c[k]=='/')
             pos=k;
     }
     base=c.left(pos);
     contrepartie=c.right(c.length()-pos-1);
     std::cout<<base.toStdString()<<" "<<contrepartie.toStdString();

     return getPaireDevises(base,contrepartie);

}

 //!< Update les indicateurs par defaut 
void EvolutionCours::updateIndicateurs(){
    int day=0;
    double emaCurrent12=0,sommeHaussiere=0,sommeBaissiere=0,rsiCalcule,closeYesterday=0,emaCurrent26=0;

    /*double tabEMA12[this->getNbCours()];
    double tabEMA26[this->getNbCours()];*/
    double tabDifferences[this->getNbCours()],yesterdayMACD=0;

    for (EvolutionCours::iterator it=this->begin();it!=this->end();++it) {
        //Pour chaque cours OHLC:
        CoursOHLC &cours=*it;

        //Calcule EMA 12 periods
        if(day==0){
            emaCurrent12=calcEMA(cours.getClose(),12,1);
            cours.setEMA12(emaCurrent12);
            //ema->append(day,emaCurrent);
        }else{
            emaCurrent12=calcEMA(cours.getClose(),12,emaCurrent12);
            cours.setEMA12(emaCurrent12);
        }

         //Calcule EMA 26 periods
        if(day==0){
             emaCurrent26=calcEMA(cours.getClose(),26,1);
            cours.setEMA26(emaCurrent26);
            //ema->append(day,emaCurrent);
        }else{
            emaCurrent26=calcEMA(cours.getClose(),26,emaCurrent26);
            cours.setEMA26(emaCurrent26);
        }

        //Calcul MACD
        cours.setMACD(emaCurrent12-emaCurrent26);

        //On garde les difference pour calculer le RSI
        if(day==0) tabDifferences[day]=0;
        else tabDifferences[day]=cours.getClose()-closeYesterday;
        closeYesterday=cours.getClose();

        if(day==0) cours.setSignalMACD(calcEMA(cours.getMACD(),9,1));
        else cours.setSignalMACD(calcEMA(cours.getMACD(),9,yesterdayMACD));
        yesterdayMACD=cours.getMACD();
        day++;
    }

    unsigned int x=0;
    //Calcule SRI (The standard is to use 14 periods to calculate
    //the initial RSI value but we'll use a valeur de 50 and to the rest we'll use 9 periods)
    int i=0;
    for(EvolutionCours::iterator it=this->begin();it!=this->end();++it){
            CoursOHLC &cours=*it;
           if(i==0){
               rsiCalcule=50.0;
           }else{
               if(i>=8){
                   sommeHaussiere=0;
                   sommeBaissiere=0;
                   for(unsigned int j=x;j<x+9;j++){
                       if(j-1>this->getNbCours()) break;
                       if(tabDifferences[j]>=0) sommeHaussiere=sommeHaussiere+tabDifferences[j];
                       else sommeBaissiere=sommeBaissiere+abs(tabDifferences[j]);
                   }
                   x++;
               }else{
                   if(tabDifferences[i]>=0) sommeHaussiere=sommeHaussiere+tabDifferences[i];
                   else sommeBaissiere=sommeBaissiere+abs(tabDifferences[i]);
               }
               rsiCalcule=calcRSI(sommeHaussiere,sommeBaissiere);

           }
           //rsiSerie->append(i,rsiCalcule);
           cours.setRSI(rsiCalcule);
           i++;
    }

}
