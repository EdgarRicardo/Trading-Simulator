#ifndef SIMULATIONMANUALC_H
#define SIMULATIONMANUALC_H

#include <QMainWindow>
#include "simulation.h"
#include "evolutionviewer.h"
#include "headerp.h"

namespace Ui {
class SimulationManualC;
}

/*! \class SimulationManualC
 *  \brief Classe permettant de gérer l'interface graphique du mode de simulation manuel classique
 */

class SimulationManualC : public QMainWindow
{
    Q_OBJECT
    QLabel* erreur;

public:
    /*!
     * \brief SimulationManualC
     *
     * Constructeur de la classe SimulationMannualC
     *
     * \param sim : objet de type simulation permettant d'effectuer les transactions
     * \param d : date de début de la simulation
     * \param parent : parent de l'objet créé
     *
     */
    explicit SimulationManualC(Simulation& sim,DevisesManager &,QDate d, QWidget *parent);
    ~SimulationManualC();

private slots:
    void on_pushButton_Quit_clicked();

    void on_pushButton_Buy_clicked();

    void on_pushButton_Sell_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_Load_clicked();

    void on_pushButton_Save_clicked();

private:
    Ui::SimulationManualC *ui;
    Simulation s; //!< Objet de type Simulation pour gérer les transactions
    DevisesManager &dm; //!< Objet de type DeviseManager
    QDate dateDebut;
};

#endif // SIMULATIONMANUALC_H
