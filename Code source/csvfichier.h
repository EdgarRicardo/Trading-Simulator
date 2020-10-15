#ifndef CSVFICHIER_H
#define CSVFICHIER_H
#include "headerp.h"

//! Classe de gestion des données des fichiers dans le repertoire "Fichierscsv"
/*!
 *  Classe permettant de gérer les données des fichiers dans le directoire "Fichierscsv", en permetant de charger des données d'une autre source.
 */

class ListeFichiers{
    int taille;
    vector <string> liste1;
    QString dir;
public:

    void montrerliste();//!< Fonction pour montrer la liste avant de l'utiliser
    int getTaille(){return taille;} //!< Retourne la taille des quantités de fichiers ou de Cours dependant de l'usage que on veut
    explicit ListeFichiers(QComboBox *liste,QString d);//!< Constructeur par defaut

    /*! \brief  ListeFichiers
     *   Constructeur par default qui saisi dans le ComboBox du Menu CSV les noms des fichiers dans le directoire courrant.
     */
    explicit ListeFichiers(){}//!< Pour acceder a la methode getListeBougies


    /*! \brief  getListeBougies
     *   Fonction qui saisit le Devise Manager du Menu CSV avec les données du fichier selectionné pour le ComboBox.
     *  \param dManager : Devise Manager pour gérer les données des Paires-Devises.
     *  \param nomfichier : Nom du fichier selectionné pour le ComboBox
     *  \param deviseutilisateur : CODE de la Devise qu'utilise l'utilisateur, saisi dans le QLineEdit du Menu CSV
     *  \param editeur : QLineEdit qui envoie des messages de réussit ou d'échec.
     */
    void getListeBougies(DevisesManager &dManager, QString &nomfichier, QString &deviseutilisateur, QLineEdit *editeur,QString dir);



};

#endif //CSVFICHIER_H
