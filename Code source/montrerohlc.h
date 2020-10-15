#ifndef MONTREROHLC_H
#define MONTREROHLC_H
#include "headerp.h"
#include "evolutionviewer.h"
#include "addindicateur.h"

//! Classe d'interface pour visualiser les cours OHLC
/**
 *  Classe d'interface pour selectionner la paire de devise pour laquelle on veut voir ses cours
 */
class MontrerOHLC: public QDialog{
    Q_OBJECT
    QLabel* dPaire;
    QLabel* paireL;
    QLabel* resultat;
    QComboBox* paireC;
    QPushButton* ok;
    QPushButton* cancel;
    DevisesManager& dm;
public:
    explicit MontrerOHLC(DevisesManager&,QWidget *parent = nullptr);
signals:
private slots:
    void okAction();
};


//! Classe d'interface pour voir des cours
/**
 *   Interface pour voir les cours d'un paire devise + ajouter des indicateurs pour le meme paire + bouton pour voir les graphiques de cette paire de devise.
 */
class tableCours: public QDialog{
    Q_OBJECT
    QLabel* coursL;
    QLabel* resultat;
    QTableWidget* tableC;
    QPushButton* retourner;
    QPushButton* viewerBougies;
    QPushButton* addIndicateur; //!< Bouton pour ajouter un indicateur
    QLabel* resultBougies;
    QComboBox* typeIndicateur; //!< Type d'indicateur qu'on veut ajouter
    const PaireDevises& paireDev;
    DevisesManager& dm;
    EvolutionCours* ec=nullptr;
public:
    explicit tableCours(DevisesManager&,const PaireDevises&,QWidget *parent = nullptr);
signals:
private slots:
    //Bouton-Action pour voir les graphiques
    void bougiesViewerAction();
    // Bouton-Action pour le bouton de ajouter indicateur
    void addIndicateurAction();
    void closeAction();
};



#endif // MONTREROHLC_H
