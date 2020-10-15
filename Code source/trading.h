#ifndef TRADING_H
#define TRADING_H

#include <QString>
#include <QDate>
#include <cmath>
#include<QVector>
#include<QList>
#include<vector>
#include<list>
using namespace std;

//! Classe d'exceptions trading
/**
 *  Classe pour gerer les exceptions de trading.
 */
class TradingException {
public:
    TradingException(const QString& message) :info(message) {}
    QString getInfo() const { return info; }
private:
    QString info;
};

//! Classe avec les caracteristiques d'une devise
/**
 *  Classe des devises.
 */
class Devise {
    QString code;
    QString monnaie, zone;
    Devise(const QString& c, const QString& m, const QString& z = "");
    ~Devise() = default;
    friend class DevisesManager;
public:
    QString getCode() const { return code; }
    const QString& getMonnaie() const { return monnaie; }
    const QString& getZoneGeographique() const { return zone; }
};

//! Classe avec les caracteristiques d'une paire de devises
/**
 *  Classe des paire de devises.
 */
class PaireDevises {
    const Devise* base;
    const Devise* contrepartie;
    QString surnom;
    PaireDevises(const Devise& b, const Devise& c, const QString& s = "");
    ~PaireDevises() = default;
    friend class DevisesManager;
public:
    const Devise& getBase() const { return *base; }
    const Devise& getContrepartie() const { return *contrepartie; }
    const QString& getSurnom() const { return surnom; }
    QString toString() const;
};

//! Classe avec les caracteristiques d'un cours OHLC
/**
 *  Classe caracteristiques d'un cours OHLC.
 */
class CoursOHLC {
    double open = 0, high = 0, low = 0, close = 0, volume=0;
    QDate date;
    //Indicateurs de demonstration initial = Indicateurs par defaut
    double ema12=0,ema26=0,rsi=0,macd=0,signal=0; //ema12 = Ema de 12 periodes ;  ema26 = Ema de 26 periodes -> On peut calculer plus rapidement le macd
public:
    int num=1;
    CoursOHLC() {}
    CoursOHLC(double o, double h, double l, double c, double v,const QDate& d);
    double getOpen() const { return open; }
    double getHigh() const { return high; }
    double getLow() const { return low; }
    double getClose() const { return close; }
    double getVolume() const { return volume; }
    void setCours(double o, double h, double l, double c);
    void setVolume(double v) {if(v<0) throw TradingException("cours OHLC incorrect"); volume=v;}
    QDate getDate() const { return date; }
    double getEMA12() const{return ema12;} //!< Obtenir le indicateur par defaut ema à 12 periodes
    double getEMA26() const{return ema26;} //!< Obtenir le indicateur par defaut ema à 26 periodes
    double getRSI() const{return rsi;} //!< Obtenir le indicateur par defaut rsi à 9 periodes
    double getMACD() const{return macd;} //!< Obtenir le indicateur par defaut macd(12,26,9)
    double getSignalMACD() const {return signal;}//!< Obtenir l'indicateur par defaut signal à 9 periodes
     //!< Modifier les indicateur par defaut
    void setEMA12(double e){ema12=e;}//!< Changer l'indicateur par defaut ema à 12 periods
    void setEMA26(double e){ema26=e;}//!< Changer l'indicateur par defaut ema à 26 periods
    void setRSI(double r){rsi=r;}//!< Changer l'indicateur par defaut rsi à 9 periods
    void setMACD(double m){macd=m;}//!< Changer l'indicateur par defaut macd(12,26,9)
    void setDate(const QDate& d) { date=d;}
    void setSignalMACD(double s){signal=s;}//!< Changer le indicateur par defaut signal à 9 periodes
};

//! Classe avec les caracteristiques de l'evolution du cours
/**
 *  Classe de l'evolution du cours.
 */
class EvolutionCours {
    const PaireDevises* paire;
    CoursOHLC* cours = nullptr;
    unsigned int nbCours = 0;
    unsigned int nbMaxCours = 0;
    QVector<QList<double>> ema; // Qvectors de Qlists pour controler les indicateurs d'un EvolutionCours
    QVector<QList<double>> rsi;
    QVector<QList<double>> macd;
    QVector<QList<double>> signal; //On aura une correspondance entre la signalMACD et le MACD grace a macdCount
    unsigned int emaCount=0;
    unsigned int rsiCount=0;
    unsigned int macdCount=0;

public:
    EvolutionCours(const PaireDevises& p) :paire(&p),ema(10),rsi(10),macd(10),signal(10){} //!< Contructeur classe; Maximum de 10 indicateurs/type
    void addCours(double o, double h, double l, double c, double v,const QDate& d);
    ~EvolutionCours();
    EvolutionCours(const EvolutionCours& e);
    EvolutionCours& operator=(const EvolutionCours& e);
    unsigned int getNbCours() const { return nbCours; }
    const PaireDevises& getPaireDevises() const { return *paire; }
    using iterator = CoursOHLC*;
    iterator begin() { return iterator(cours); }
    iterator end() { return iterator(cours + nbCours); }
    using const_iterator = const CoursOHLC*;
    const_iterator begin() const { return cours; }
    const_iterator end() const { return cours + nbCours; }
    const_iterator cbegin() const { return cours; }
    const_iterator cend() const { return cours + nbCours; }
    iterator getCoursI(unsigned int i) {
        if(i>nbCours) throw TradingException("Le cours n'existe pas");
        return iterator(cours+i);
    }
    CoursOHLC* getCours() {return cours;}
    const PaireDevises* getPaire(){return paire;}
    void updateIndicateurs(); //!< On fait l'update des indicateurs par defaut
    void addEma(const int period); /*! Ajouter un nouveau EMA au vector ema.*/
    void addRsi(const int period); /*! Ajouter un nouveau RSI au vector rsi.*/
    void addMacd(const int periodEma1,const int periodEma2,const int periodSignal); //!< Add MACD+Signal; Ajouter un nouveau MACD au vector macd
    unsigned int getNbEmas() const {return emaCount;} //!< Function pour connaitre le nombre d'un type d'indicateur ema
    unsigned int getNbRsis() const {return rsiCount;} //!< Function pour connaitre le nombre d'un type d'indicateur rsi
    unsigned int getNbMacds() const {return macdCount;}//!< Function pour connaitre le nombre d'un type d'indicateur macd
    const QList<double>& getEmaT(unsigned int i) const {return ema[i];} //!< Obtenir la liste d'un indicateur ema
    const QList<double>& getRsiT(unsigned int i) const {return rsi[i];} //!< Obtenir la liste d'un indicateur rsi
    const QList<double>& getMacdT(unsigned int i) const {return macd[i];} //!< Obtenir la liste d'un indicateur macd
    const QList<double>& getSignalT(unsigned int i) const {return signal[i];}  //!< Obtenir la liste d'un indicateur signal


};

//! Classes qui permet de gerer les devises
/**
 *  Class pour manipuler tout les principales classes d'un trading.
 */
class DevisesManager {

    Devise** devises = nullptr; //!< tableau de pointeurs sur objets Devise
    unsigned int nbDevises = 0;
    unsigned int nbMaxDevises = 0;
    mutable PaireDevises** paires = nullptr; //!< tableau de pointeurs sur objets PaireDevises
    mutable unsigned int nbPaires = 0;
    mutable unsigned int nbMaxPaires = 0;
    mutable EvolutionCours** ecoursTab = nullptr; //!< tableau de pointeurs sur objets EvolutionCours
    mutable unsigned int nbECoursTab = 0;
    mutable unsigned int nbMaxECoursTab = 0;
    //!< empêcher la duplication par recopie ou affectation
    DevisesManager(const DevisesManager& m) = delete;
    DevisesManager& operator=(const DevisesManager& m) = delete;
    //!< pour le singleton
    DevisesManager() {}
    ~DevisesManager();
    struct Handler {
        DevisesManager* instance = nullptr;
        ~Handler() { delete instance; }
    };
    static Handler handler;
public:
    static DevisesManager& getManager() {
        if (handler.instance == nullptr)
            handler.instance = new DevisesManager;
        return *handler.instance;
    }
    static void libererManager() {
        delete handler.instance;  handler.instance = nullptr;
    }
    const Devise& creationDevise(const QString& c, const QString& m,const QString& z);
    const Devise& getDevise(const QString& c)const;
    Devise** getDevises()const {return devises;}
    unsigned int getNbDevises() const{return nbDevises;}

    PaireDevises** getPaires() {return paires;}
    const PaireDevises& getPaireDevises(const QString & c1,const QString & c2);
    unsigned int getNbPaires() const{return nbPaires;}

    EvolutionCours** getCours() {return ecoursTab;}
    EvolutionCours* creerCoursDevise(const PaireDevises*, double o, double h, double l, double c, double v,const QDate& d);
    const CoursOHLC* getCoursDevise(const PaireDevises*,const QDate& d) const;
    unsigned int getNbCoursTab() const{return nbECoursTab;}
    const PaireDevises& recupererPaire(QString c);
};

double calcEMA(double todayPrice, int numberDays, double emaYesterday);
double calcRSI(double sommeHaussiere, double sommeBaissiere);


#endif //!< TRADING_H
