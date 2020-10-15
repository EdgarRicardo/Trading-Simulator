#ifndef MENU_H
#define MENU_H
#include "cdevise.h"
#include "cpaires.h"
#include "ccours.h"
#include "montrerohlc.h"
#include "simulationselection.h"

//! Classe du menu des options

class Menu: public QMainWindow{
    Q_OBJECT
    //QWidget fenetre;
    QLabel*  menuO;
    QPushButton* addDev;
    QPushButton* addCours;
    QPushButton* addPaireD;
    QPushButton* montrerOHLC;
    QPushButton* simulationSelection;
    QPushButton* exit;

    DevisesManager& dm;
public:
    explicit Menu(DevisesManager&,QWidget *parent = nullptr);
signals:
private slots:
    // Action pour la creation de Devises, Paires et Cours et une derniere
    // pour les voir tous les cours et graphiques
    void addDeviseAction();
    // Bouton-Action pour ouvrir l'interface de creer un paire
    void addPaireAction();
     // Bouton-Action pour ouvrir l'interface de ajouter un cours
    void addCoursAction();
     // Bouton-Action pour ouvrir l'interface pour voir les cours d'un paire
    void montrerOHCLAction();
    // Bouton-Action pour ouvrir l'interface pour de selection d'un type de selection
    void simulationSelectionAction();

};

#endif // MENU_H
