#include "trading.h"

//!< Fonctions pour le calcul des indicateurs by Corona
//!
void EvolutionCours::addEma(const int period){
    double emaCurrent=0;
    int day=0;
    for (EvolutionCours::iterator it=begin();it!=end();++it) {
        //Pour chaque cours OHLC:
        CoursOHLC &cours=*it;
        if(day==0){
            emaCurrent=calcEMA(cours.getClose(),period,1);
            ema[emaCount].push_back(emaCurrent);
        }else{
            emaCurrent=calcEMA(cours.getClose(),period,emaCurrent);
            ema[emaCount].push_back(emaCurrent);
        }
        day++;
    }
    emaCount++;
}

void EvolutionCours::addRsi(const int period){
    double rsiCalcule=0,sommeHaussiere=0,sommeBaissiere=0,closeYesterday=0;
    int day=0;
    double tabDifferences[this->getNbCours()];
    for (EvolutionCours::iterator it=this->begin();it!=this->end();++it) {
        //Pour chaque cours OHLC:
        CoursOHLC &cours=*it;
        if(day==0) tabDifferences[day]=0;
        else tabDifferences[day]=cours.getClose()-closeYesterday;
        closeYesterday=cours.getClose();
        day++;
    }
    unsigned int x=0;
     //!< by Corona Calcule SRI (The standard is to use 14 periods to calculate
     //!< by Corona The initial RSI value but we'll use a valeur de 50 and to the rest we'll use "period" periods)
    unsigned int i=0;
    unsigned int per=static_cast<unsigned int>(period);
    for(EvolutionCours::iterator it=this->begin();it!=this->end();++it){
           if(i==0){
               rsiCalcule=50.0;
           }else{
               if(i>=per-1){
                   sommeHaussiere=0;
                   sommeBaissiere=0;
                   for(unsigned int j=x;j<x+per;j++){
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
           rsi[rsiCount].push_back(rsiCalcule);
           i++;
    }
    rsiCount++;
}

 //!< Dans addMacd on modifie le vector de signals car il existe un lien entre le mancd et la signal by Corona
void EvolutionCours::addMacd(const int periodEma1,const int periodEma2,const
                             int periodSignal){
    int day=0;
    double emaCurrent1=0,emaCurrent2=0,yesterdayMACD=0;

    for (EvolutionCours::iterator it=this->begin();it!=this->end();++it) {
        CoursOHLC &cours=*it;

         //!< by CoronaCalcule EMA1 periods selon la variable periodEma1
        if(day==0) emaCurrent1=calcEMA(cours.getClose(),periodEma1,1);
        else emaCurrent1=calcEMA(cours.getClose(),periodEma1,emaCurrent1);

        if(day==0) emaCurrent2=calcEMA(cours.getClose(),periodEma2,1);
        else emaCurrent2=calcEMA(cours.getClose(),periodEma2,emaCurrent2);


         //!< by Corona Calcul MACD
        macd[macdCount].push_back(emaCurrent1-emaCurrent2);

        if(day==0) signal[macdCount].push_back(calcEMA(emaCurrent1-emaCurrent2,periodSignal,1));
        else signal[macdCount].push_back(calcEMA(emaCurrent1-emaCurrent2,periodSignal,yesterdayMACD));
        yesterdayMACD=emaCurrent1-emaCurrent2;
        day++;
    }
    macdCount++;
}

double calcEMA(double todayPrice, int period, double emaYesterday){
   auto k = 2.0 / (period + 1.0);
   return todayPrice * k + emaYesterday * (1 - k);
}
double calcRSI(double sommeHaussiere, double sommeBaissiere){
    if(sommeBaissiere==0.0) sommeBaissiere=1;
    double rs=sommeHaussiere/sommeBaissiere;
    return 100-(100/(1+rs));
}
