#ifndef SIMULATIONSELECTION_H
#define SIMULATIONSELECTION_H

#include <QDialog>
#include "headerp.h"
#include "simulation.h"
#include "simulationmanualc.h"


namespace Ui {
class SimulationSelection;
}

//! Choix du type de simulation
class SimulationSelection : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief SimulationSelection
     *
     * Constructeur de la classe SimulationSelection
     *
     * \param dManager : Objet de type DeviseManager
     * \param parent : parent de l'objet créé
     */
    explicit SimulationSelection(DevisesManager& dManager, QWidget *parent = nullptr);
    ~SimulationSelection();

private slots:
    void on_pushButton_Ok_clicked();

    void on_pushButton_Cancel_clicked();

    void on_comboBox_PaireDevises_currentTextChanged(const QString &arg1);

private:
    Ui::SimulationSelection *ui;
    DevisesManager&dm; //!< Objet de type DeviseManager
    QString dir;
};

#endif // SIMULATIONSELECTION_H
