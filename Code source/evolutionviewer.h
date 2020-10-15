#ifndef EVOLUTIONVIEWER_H
#define EVOLUTIONVIEWER_H
#include "headerp.h"

//! Classe des bougies
/**
 *  Classe pour les caracteristiques d'une bougie.
 */
class Bougie : public QCandlestickSet {
    Q_OBJECT
    CoursOHLC* cours;
    double mechS=0; //!<Meche superieure de la bougie
    double mechI=0; //!<Meche inferieure de la bougie
    double corpsTaille=0;
    QString tendence=nullptr;
    QString type="Inconnue";
    public:
    Bougie(qreal open, qreal high, qreal low, qreal close,CoursOHLC* c, qreal
    timestamp = 0.0, QObject *parent = nullptr):
    QCandlestickSet(open, high, low, close, timestamp, parent), cours(c){
    connect(this,SIGNAL(clicked()),this, SLOT( viewCoursOHLC()));
    }
    CoursOHLC& getCoursOHLC() { return *cours; }
    const CoursOHLC& getCoursOHLC() const { return *cours; }

    void analyseBougie(); //!< Function pour obtenir les valeurs des caracteristiques d'une bougie
    double getMechI() const {return mechI;}   //!< Function pour obtenir la meche inferieure
    double getMechS() const {return mechS;}   //!< Function pour obtenir la meche superieure
    QString getTendence() const {return tendence;} //!< Function pour obtenir la tendance de la bougie
    double getCorps() const {return corpsTaille;} //!< Function pour obtenir la taille du corps de la bougie
    QString getType() const {return type;} //!< Function pour obtenir le type de bougie
    signals:
    void clickBougie(Bougie* c);
    private slots:
    void viewCoursOHLC(){ emit clickBougie(this); } //!< Bouton pour voir toutes les caracteristiques d'une bougie
};

//! Classe d'interface graphique generale
/**
 *   Voir des graphique de bougies + graphique volume + graphiques indicateurs
 */
class EvolutionViewer : public QDialog{
        Q_OBJECT
        EvolutionCours* evolution=nullptr;
        QCandlestickSeries* series; //!< un ensemble de bougies
        QChart *chart; //!< un graphique sur un ensemble de bougies
        QChartView *chartView; //!< un viewer de graphique
        QLineEdit* open; //!< barres d’édition
        QLineEdit* high;
        QLineEdit* low;
        QLineEdit* close;
        QLineEdit* volume;
        QLabel* openl; //!< labels
        QLabel* highl;
        QLabel* lowl;
        QLabel* closel;
        QLabel* volumel;
        QPushButton* save; //!< bouton
        QHBoxLayout* layoutHOpen; //!< couches de placement
        QHBoxLayout* layoutHHigh;
        QHBoxLayout* layoutHLow;
        QHBoxLayout* layoutHClose;
        QHBoxLayout* layoutHVolume;
        QVBoxLayout* coucheCours;
        QVBoxLayout* layoutVCharts;
        QHBoxLayout* fenetre;
        Bougie* lastBougieClicked;
        QPushButton *ok;

        QStringList categories;

        QLabel* informationBougie;

        QBarSeries *seriesBar;
        QBarSet * setBar;

        QLineSeries *ema12;
        QLineSeries *ema26;

        QLineSeries *rsiSerie;
        QChart *chartRSI;
        QLineSeries* rsiLimiteSup;
        QLineSeries* rsiLimiteInf;

        QChart *chartMACD;
        QLineSeries *macd1226;
        QLineSeries *signal;
        QBarSeries *seriesHistogrammeMACD;
        QBarSet * setBarHistogrammeMACD;

        QChart *chartBar; //!< un graphique sur un ensemble de bougies
        QChartView *chartViewBar; //!< un viewer de graphique de volume
        QChartView *chartViewRSI;
        QChartView *chartViewMACD;

        QLabel *resultat;


        QLabel* dateDebutL; //!< Attributs pour l'ajustement des graphiques
        QLabel* dateFinL; //!< Attributs pour l'ajustement des graphiques
        QComboBox* dateDebutC; //!< Attributs pour l'ajustement des graphiques
        QComboBox* dateFinC; //!< Attributs pour l'ajustement des graphiques

        QPushButton* updateDateGraphs;

        QBarCategoryAxis *axisX; //!< L'axe des X d'un graphique des bougies + indicateurs EMA
        QBarCategoryAxis *axisXBar; //!< L'axe des X d'un graphique des volumes
        QBarCategoryAxis *axisXrsi; //!< L'axe des X d'un graphique des indicateurs RSI
        QBarCategoryAxis *axisXMACD; //!< L'axe des X d'un graphique des indicateurs MACD+Signal
        QValueAxis* axisY; //!< L'axe des Y d'un graphique des bougies + indicateurs EMA
        QValueAxis* axisYBar; //!< L'axe des Y d'un graphique des volumes
        QValueAxis* axisYRSI; //!< L'axe des Y d'un graphique des indicateurs RSI
        QValueAxis* axisYMACD; //!< L'axe des Y d'un graphique des indicateurs MACD+Signal

        QComboBox* indicateursBox; //!< QComboBox pour voir les indicateurs ajoutés par l'utilsateur
        QPushButton* afficherInd; //!< Bouton pour voir les indicateurs

public:
    explicit EvolutionViewer(EvolutionCours* e,QWidget *parent = nullptr);
    void updateGraphsSet();
signals:
private slots:
        void viewCoursOHLC(Bougie *b); //!< Mise a jour des champs de la partie droite
        void saveCoursOHLC();
        void updateGraphsScroll();//!< Faire un ajustement des graphiques selon dateDebutC et dateFinC
        void afficherIndicateur();//!< Si on change une valeur d'un cours on doit aussi changer les valeurs des Indicateurs par defaut
public slots:
};




#endif //EVOLUTIONVIEWER_H
