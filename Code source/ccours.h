#ifndef CCOURS_H
#define CCOURS_H
#include "headerp.h"

//! Classe d'interface CreateCours
/**
 *   Classe pour créer une cours pour une paire specifique.
 */
class CreateCours : public QDialog{
    Q_OBJECT
    //QWidget fenetre;
    QLabel*  cCours;
    QPushButton* ok;
    QPushButton* cancel;

    QLabel*  paireL;
    QComboBox* paireC;

    QLabel* open;
    QLabel* high;
    QLabel* low;
    QLabel* closeL;
    QLabel* volume;
    QLabel* date;

    QLineEdit* openLE;
    QLineEdit* highLE;
    QLineEdit* lowLE;
    QLineEdit* closeLE;
    QLineEdit* volumeLE;
    QDateEdit* dateW;

    QLabel* resultat;
    DevisesManager&dm;
public:
    explicit CreateCours(DevisesManager&,QWidget *parent = nullptr); //!<  Constructeur  
signals:
private slots:

    void okAction(); //Bouton-Action pour créer le cours
};



#endif // CCOURS_H
