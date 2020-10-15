#ifndef SIMULATIONAUTO_H
#define SIMULATIONAUTO_H

#include <QMainWindow>
#include "simulation.h"
#include "evolutionviewer.h"
#include "headerp.h"

namespace Ui {
class simulationAuto;
}

/*! \class simulationAuto
 *  \brief Classe permettant de gérer l'interface graphique du mode de simulation automatique
 */

class simulationAuto : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief simulationAuto
     *
     * Constructeur de la classe simulationAuto
     *
     * \param sim : objet de type simulation permettant d'effectuer les transactions
     * \param dateD : date de début de la simulation
     * \param dateF
     * \param mode
     * \param parent : parent de l'objet créé
     */
    explicit simulationAuto(Simulation& sim,DevisesManager &, QDate dateD, const PaireDevises& pDev, QWidget *parent);
    ~simulationAuto();

private slots:
    void on_pushButton_begin_clicked();
    
    void on_pushButton_New_clicked();

    void on_pushButton_Cancel_clicked();

    void on_dateEdit_debut_dateTimeChanged(const QDateTime &dateTime);

    void on_pushButton_Load_clicked();

    void on_pushButton_Save_clicked();

private:
    Ui::simulationAuto *ui;
    Simulation s; //!< Objet de type Simulation pour gérer les transactions
    DevisesManager &dm; //!< Objet de type DeviseManager
    QDate dateDebut; //!< date de début de la simulation
    QDate dateFin; //!< date de fin de la simulation
    QString modeS;

    const PaireDevises& paireDev; //!< Objet PaireDevises


};

#endif // SIMULATIONAUTO_H
