#ifndef CDEVISE_H
#define CDEVISE_H
#include "headerp.h"

//! Interface/classe pour creer de devises 
class CreateDevise : public QDialog{
    Q_OBJECT
    //QWidget fenetre;
    QLabel*  cd;
    QPushButton* ok;
    QPushButton* cancel;

    QLabel*  code;
    QLineEdit* codeLE;
    QLabel*  monnaie;
    QLineEdit* monnaieLE;
    QLabel*  zone;
    QLineEdit* zoneLE;

    QLabel* resultat;

    DevisesManager&dm;
public:
    explicit CreateDevise(DevisesManager&,QWidget *parent = nullptr);
signals:
private slots:
    //! Bouton-Action pour créer la devise
    void okAction();
    void cancelAction();
};


#endif // CDEVISE_H
