#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <vector>
#include <string>
#include <algorithm>
#include "headerp.h"

using namespace std;
/*!
 * \class SimulationException
 * \brief Classe permettant de gérer les exception de la classe Simulation.

*/

class SimulationException {
public:
    SimulationException (const QString& message) :info(message) {}
    QString getInfo() const { return info; }
private:
    QString info;
};

/*! \class Simulation
 *  \brief Classe permettant de gérer les transactions des différents modes de simulation,
 *  c'est à dire achat et vente des devises ainsi que le stockage des transactions et la restitution
 *  des informations demandées par un utilisateur.
 *
*/

class Simulation{

    double devisesBase; //!< Montant courant de la devise de base
    double devisesContrepartie; //!< Montant courant de la devise de contrepartie
    double tauxCommission; //!< Taux de commission

    const PaireDevises& paireDev; //!< Objet PaireDevises
    const DevisesManager& dm; //!< Objet DevisesManager

    vector<double> tabDevisesBase; //!< Vecteur contenant toutes les valeurs de la devises de base en fonction des tranaction
    vector<double> tabDevisesContrepartie; //!< Vecteur contenant toutes les valeurs de la devises de contrepartie en fonction des tranaction
    vector <QDate> dateTransactions; //!< Vecteur contenant toutes les dates des transactions

    string deviseBase;
    string deviseContrepartie;

    int nbtabDevisesB;
    int nbtabDevisesC;
    int nbtabDates;

    QString dir; //!< Path pour travailler pendant la simulation

public:

    /*!
     * \brief Simulation
     *
     * Constructeur de la classe Simualtion
     *
     * \param dContrepartie : Montant initiale des devises de contrepartie
     * \param dBase : Montant initiale des devises de bases
     * \param commission : Taux de commission
     * \param date : Date de début de la simulation
     * \param pDev : Objet PaireDevises pour gérer les devises
     * \param dM : Objet DeviseManager
     */

    Simulation(const double& dContrepartie, const double& dBase,const double& commission, const QDate& date, const PaireDevises& pDev, const DevisesManager& dM):
        devisesBase(dBase), devisesContrepartie(dContrepartie), tauxCommission(commission), paireDev(pDev), dm(dM)
    {dateTransactions.push_back(date); // on ajoute les valeurs de date, dBase, dContrepartie à leur liste respectif
    tabDevisesBase.push_back(dBase);
    tabDevisesContrepartie.push_back(dContrepartie);}

    int getNumberTransactions() const {return tabDevisesBase.size();} //!< Retourne le nombre de transactions effectuées

    QString getDBase() const {return paireDev.getBase().getCode();} //!< Retourne le nom de la devise de base
    QString getDContrepartie() const {return paireDev.getContrepartie().getCode();} //!< Retourne le nom de la devise de contrepartie
    double getDevisesBase() const {return tabDevisesBase.back();} //!< Retourne le montant actuel de la devise de base
    double getDevisesContrepartie() const {return tabDevisesContrepartie.back();} //!< Retourne le montant actuel de la devise de contrepartie

    double getdoubleDevisesBase() const {return devisesBase;}//!< Retourne la quantité de Devises de Base
    double getdoubleDevisesContrepartie() const {return devisesContrepartie;}//!< Retourne la quantité de Devises de Contrepartie
    double getTauxCommission () const {return tauxCommission;} //!< Retourne la valeur du taux de commission

    double getDeviseBaseInitiales() const {return tabDevisesBase[0];} //!< Retourne la valeur initiale de la devise de base
    double getDeviseContrepartieInitiales() const {return tabDevisesContrepartie[0];} //!< Retourne la valeur initiale de la devise de contrepartie

    QDate getDate(unsigned int index) const {return dateTransactions[index];} //!< Retourne la date de la transaction correspondant à l'index

    double getDeviseBaseIndex(unsigned int index) const {return tabDevisesBase[index];} //!< Retourne la valeur de la devise de base correpondant à l'index
    double getDeviseContrepartieIndex(unsigned int index) const {return tabDevisesContrepartie[index];} //!< Retourne la valeur de la devise de contrepartie correspondant à l'index

    double getMontantTotalActuel(const QDate& date) const; //!< Retourne le montant total actuel (convertit en devise de contrepartie)

    double getConversionDBase (unsigned int index, const QDate& date) const; //!< Retourne la conversion du montant de la devise de base situé à l'index donné en devise de contrepartie

    void effectuerAchat(double dContrepartie,const QDate& date); //!< Effectue un achat et stock les valeurs dans les vecteurs
    void effectuerVente(double dContrepartie, const QDate& date); //!< Effectue une vente et stock les valeurs dans les vecteurs

    void supprimerTransactions(const QDate& date); //!< Supprime les transactions antérieurs à une date donnée

    double getCurrentOpen(const QDate& date); //!< Retourne le prix d'ouverture pour la date choisie

    void annulerDerniereOperation(); //!< Supprime la dernière transaction

    void effectuerTransactionsRSI(double dContrepartie, const QDate& date); //!< Effectue une transaction en fonction de l'indicateur RSI

    void effectuerTransactionsEMA(double dContrepartie, const QDate& date); //!< Effectue une transaction en fonction de l'indicateur EMA

    void effectuerTransactionsMACD(double dContrepartie, const QDate& date); //!< Effectue une transaction en fonction de l'indicateur MACD

    void setdoublesvalues(double base, double contre, double taux) { devisesBase=base; devisesContrepartie=contre; tauxCommission=taux;} //!< Saisir les valeurs respectifs pour le bouton charger

    void pushbacktabvalues(double base, double contre, QDate date) { tabDevisesBase.push_back(base); tabDevisesContrepartie.push_back(contre); dateTransactions.push_back(date); }

    void garderDeviseManager();//!< Stocke le DEVISE MANAGER pour pouvoir être chargé après.

    double getROI(int index) const; //!< Retourne le retour sur investissement correspondant à l'index donné

    void setPathSimulation(QString path){ dir=path;} //!< Set le Path pour travailler

    QString getPathSimulation(){return dir; } //!< Retourne le path qu'on a selectionné

    /*!
      \brief ~Simulation()

      Destructeur de la classe Simulation

    */
    ~Simulation() {}

};

#endif // SIMULATION_H_INCLUDED
