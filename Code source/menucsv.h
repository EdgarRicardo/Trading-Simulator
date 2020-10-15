#ifndef MENUCSV_H
#define MENUCSV_H

#include "headerp.h"
#include "csvfichier.h"
#include "montrerohlc.h"
#include "simulationselection.h"

//! Classe pour l'affichage du Menu CSV
/*! \class Menucsv
 *   Classe pour l'affichage du Menu CSV
 */
class Menucsv: public QMainWindow{
    Q_OBJECT
    QLabel*  menucsv;
    QComboBox* nomcsv; //!< Lieu où la liste de fichiers seront montrés
    QLineEdit* nombase; //!< En cas de que l'utilisateur veut acheter des investissements, il faut écrire le Devise de Base
    QPushButton* csvdefault; //!< Bouton pour charger
    QPushButton* simulationSelection;
    QPushButton* graphique;
    QString dir;
    QPushButton* exit;

    DevisesManager& dm; //!< Il faut avoir présent le Devise Manager dans de QMainWindow
public:
    /*! \brief Menucsv
     *   Constructeur qui sera appelé par le premier menu
     * \param &DevisesManager : Devise Manager avant crée pour pouvoir l'utiliser
     * \param parent : Widget pour recevoir des fonctionalités du parent.
     */
    explicit Menucsv(DevisesManager&, QWidget *parent = nullptr);
signals:
private slots:
    /*! \brief  chargercsvdefault
     *   Fonction qui s'active avec le click sur le bouton csvdefault, il charge le fichier décrit dans le ComboBox
     */
    void chargercsvdefault();
    void montrerOHCLAction();
    void simulationSelectionAction();
};



#endif // MENUCSV_H
