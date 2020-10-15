#include "csvfichier.h"
#include "headerp.h"
#include "cdevise.h"


ListeFichiers::ListeFichiers(QComboBox * liste,QString d):dir(d){// Constructeur par defaut

    QDir dirfich;
    /*dirfich.currentPath();
    dirfich.cd("..");
    dirfich.cd("OHLC");
    dirfich.cd("Fichierscsv");*/
    dirfich.cd(dir);
    dirfich.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dirfich.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dirfich.entryInfoList();

    for(int i=0; i<list.size(); ++i){
        QFileInfo fileInfo= list.at(i);
        if(fileInfo.fileName().right(4)==".csv")
            liste->addItem(fileInfo.fileName());
    }

}

void ListeFichiers::getListeBougies(DevisesManager &dManager, QString& nomfichier, QString &deviseutilisateur, QLineEdit *editeur,QString dir){
    DevisesManager& dm(dManager);
    int cestposible=0;
    string nom= nomfichier.toLocal8Bit().constData();
    QString base, contrepartie;
    if((nomfichier.length()==11)&&(nomfichier.at(3)=='-')){// le cas où le fichier est de deux devises
        base=nomfichier.left(3);
        contrepartie=nomfichier.right(7).left(3);
        int erreur=0;
        if((contrepartie.size()<4)&&(base.size()<4)){
            for (int t = 0; t < contrepartie.length(); t++) {
                if (contrepartie[t] < 'A' || contrepartie[t] > 'Z') erreur=1;
            }
            for (int t = 0; t < contrepartie.length(); t++) {
                if (base[t] < 'A' || base[t] > 'Z') erreur=1;
            }
            if(erreur==0){
                dm.creationDevise(base,"","");
                dm.creationDevise(contrepartie,"","");
                dm.getPaireDevises(base,contrepartie);// creer la paire
                editeur->setText("La creation a reussi");
                cestposible=1;
            }
            else
                editeur->setText("Il y a un erreur");
        }
    }
    else if(nomfichier.length()>3){//le cas d'une entreprise avec un code d'une lettre ou plus.
        // base=deviseutilisateur;
        base=deviseutilisateur;
        contrepartie=nomfichier.left(nomfichier.length()-4);
        int erreur=0;
        if((contrepartie.size()<5)&&(base.size()<4)){
            for (int t = 0; t < contrepartie.length(); t++) {
                if (contrepartie[t] < 'A' || contrepartie[t] > 'Z'){ erreur=1; std::cout<<"Lettre mal:"<<contrepartie.toStdString()<<"AQUI";}
            }
            for (int t = 0; t < base.length(); t++) {
                if (base[t] < 'A' || base[t] > 'Z') erreur=1;
            }
            std::cout<<erreur;
            if(erreur==0){
                dm.creationDevise(base,"","");
                dm.creationDevise(contrepartie,"","");
                dm.getPaireDevises(base,contrepartie);// creer le paire
                editeur->setText("La creation a reussi");
                cestposible=1;
            }
            else
                editeur->setText("Il y a un erreur");
        }
    }
    //Bougie BTC_USD;

    if(cestposible==1){
        ifstream lectura;
        QDir dirfich;
        dirfich.cd(dir);
        //std::cout<<dir.toStdString();
        string path=dirfich.path().toStdString();
        string pathplusfichier=path+'/'+nom;
        double o=0,h=0,l=0,c=0,v=0;
        lectura.open(pathplusfichier,ios::in);
        QDate date;
        for (string linea; getline(lectura, linea); )
        {
            stringstream registro(linea);
            string dato;
            QString pD,e="Remplissez toutes les\ninformations demandées";
            for (int columna = 0; getline(registro, dato, ','); ++columna)
            {
                QString qdato=QString::fromStdString(dato);
                switch (columna)
                {
                    case 0: //Date
                        date=QDate::fromString(qdato,"dd/MM/yyyy");
                        if(date.isNull()){
                            QString tourne=qdato.right(2)+'/'+qdato.right(5).left(2)+'/'+qdato.left(4);
                            date=QDate::fromString(tourne,"dd/MM/yyyy");

                        }
                            //BTC_USD.date = QDate::fromString(dato,"dd/MM/yyyy");
                    break;
                    case 1: // Open
                        o=qdato.toDouble();
                        // BTC_USD.open = stod(dato);
                    break;
                    case 2: // High
                        h=qdato.toDouble();
                        //BTC_USD.high = stod(dato);
                    break;
                    case 3: //Low
                        l=qdato.toDouble();
                        //BTC_USD.low = stod(dato);
                    break;
                    case 4: //  Close
                        c=qdato.toDouble();
                    // BTC_USD.close = stod(dato);
                    break;
                    case 5: // Adj on n'utilise pas

                        // BTC_USD.volume = stod(dato);
                    break;
                    case 6: //Volume
                        v=qdato.toDouble();
                    break;
                }
            }
            if(date.isNull()) continue;
            //cout<<base.toStdString()<<"-"<<contrepartie.toStdString()<<":"<<o<<" "<<h<<" "<<l<<" "<<c<<" "<<v<<" "<<date.toString().toStdString()<<endl;
            dm.creerCoursDevise(&dm.getPaireDevises(base,contrepartie),o,h,l,c,v,date);
        }
    }
    else
        editeur->setText("Il y a un erreur");
}
