#ifndef SIMULATIONMANUALPAP_H
#define SIMULATIONMANUALPAP_H

#include <QMainWindow>
#include "simulation.h"
#include "evolutionviewer.h"
#include "headerp.h"


namespace Ui {
class SimulationManualPaP;
}


/*! \class SimulationManualPaP
 *  \brief Classe permettant de gérer l'interface graphique du mode de simulation manuel classique
 */
class SimulationManualPaP : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief simulationAuto
     *
     * Constructeur de la classe simulationAuto
     *
     * \param sim : objet de type simulation permettant d'effectuer les transactions
     * \param d : date de début de la simulation
     * \param parent : parent de l'objet créé
     */
    explicit SimulationManualPaP(Simulation& sim,DevisesManager &, QDate d, QWidget *parent);
    ~SimulationManualPaP();

private slots:
    void on_pushButton_buy_clicked();

    void on_pushButton_nextDay_clicked();

    void on_pushButton_confirm_clicked();

    void on_pushButton_sell_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_load_clicked();

private:
    Ui::SimulationManualPaP *ui;
    Simulation s; //!< Objet de type Simulation pour gérer les transactions
    DevisesManager &dm; //!< Objet de type DeviseManager
    EvolutionCours* ec = nullptr;
    QDate dateJ; //!< date du jour (incrémenté à chaque fois que le bouton 'Jour Suivant' est cliqué
};

#endif // SIMULATIONMANUALPAP_H
