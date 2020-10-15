#ifndef CPAIRES_H
#define CPAIRES_H
#include "headerp.h"

//! Interface/class pour creer paires
/**
 *  Classe d'interface CreatePaires. Classe pour créer une une Paire de Devises.
 */
class CreatePaire : public QDialog{
    Q_OBJECT
    //QWidget fenetre;
    QLabel*  cPaire;
    QPushButton* ok;
    QPushButton* cancel;

    QLabel*  devise1L;
    QComboBox* devise1;

    QLabel*  devise2L;
    QComboBox* devise2;

    QLabel* resultat;

    DevisesManager&dm;
public:
    explicit CreatePaire(DevisesManager &,QWidget *parent = nullptr);
signals:
private slots:
    //! Bouton-Action pour créer le paire de devise
    void okAction();
};


#endif // CPAIRES_H
