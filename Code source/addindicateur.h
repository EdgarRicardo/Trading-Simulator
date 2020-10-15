#ifndef ADDINDICATEUR_H
#define ADDINDICATEUR_H
#include "headerp.h"

//! Classe d'interface AddEMA
/**
 *   Classe pour ajouter des indicateurs EMA.
 */
class addEMA: public QDialog{
    Q_OBJECT
    QLabel* addI;
    QLabel* periodsL;
    QLabel* resultat;
    QLineEdit* periodsLE;
    QPushButton* ok;
    QPushButton* cancel;
    EvolutionCours* ec;
public:
    explicit addEMA(EvolutionCours*,QWidget *parent = nullptr); //!< Ajout des indicateurs EMA
signals:
private slots:
     void okAction(); //!< Bouton pour ajouter l'indicateur
};

//! Classe d'interface AddRSI
/**
 *  Classe pour ajouter des indicateur RSI.
 */
class addRSI: public QDialog{
    Q_OBJECT
    QLabel* addI;
    QLabel* periodsL;
    QLabel* resultat;
    QLineEdit* periodsLE;
    QPushButton* ok;
    QPushButton* cancel;
    EvolutionCours* ec;
public:
    explicit addRSI(EvolutionCours*,QWidget *parent = nullptr);
signals:
private slots:

     void okAction(); //!< Bouton pour ajouter l'indicateur
};

//! Classe d'interface AddMACD
/**
 *  Classe pour ajouter des indicateur MACD + Signal.
 */
class addMACD: public QDialog{
    Q_OBJECT
    QLabel* addI;
    QLabel* periodsEma1L;
    QLabel* periodsEma2L;
    QLabel* periodsSignalL;
    QLabel* resultat;
    QLineEdit* periodsEma1LE;
    QLineEdit* periodsEma2LE;
    QLineEdit* periodsSignalLE;
    QPushButton* ok;
    QPushButton* cancel;
    EvolutionCours* ec;
public:
    explicit addMACD(EvolutionCours*,QWidget *parent = nullptr);
signals:
private slots:
    void okAction(); //!< Bouton-Action pour ajouter l'indicateur
};
#endif // ADDINDICATEUR_H
