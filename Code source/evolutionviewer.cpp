#include "evolutionviewer.h"

EvolutionViewer::EvolutionViewer(EvolutionCours* e,QWidget *parent):QDialog(parent),evolution(e){

    //QtCreateStickSeries
    series= new QCandlestickSeries(this);
    series->setName("Bougies");
    series->setIncreasingColor(QColor(Qt::green));
    series->setDecreasingColor(QColor(Qt::red));

    seriesBar=new QBarSeries();
    setBar = new QBarSet("Volume");
    setBar->setColor(QColor(Qt::black));

    ema12 = new QLineSeries();
    ema12->setName("EMA 12 Periods");
    ema26 = new QLineSeries();
    ema26->setName("EMA 26 Periods");

    rsiSerie = new QLineSeries();
    rsiSerie->setName("RSI");

    rsiLimiteSup = new QLineSeries();
    rsiLimiteSup->setName("RSI 70");

    rsiLimiteInf = new QLineSeries();
    rsiLimiteInf->setName("RSI 30");
    rsiLimiteInf->setColor(QColor(Qt::red));

    seriesHistogrammeMACD=new QBarSeries();
    setBarHistogrammeMACD= new QBarSet("Historgramme MACD");
    setBarHistogrammeMACD->setColor(QColor(Qt::darkGray));

    macd1226 = new QLineSeries();
    macd1226->setName("MACD(12,26)");
    signal = new QLineSeries();
    signal->setName("Signal EMA(9,MACD)");

    int day=0;
    for (EvolutionCours::iterator it=evolution->begin();it!=evolution->end();++it) {
        //Pour chaque cours OHLC:
        CoursOHLC &cours=*it;
        //Creer une bougie(QCandleStickSets)
        Bougie* bougie=new Bougie(cours.getOpen(),cours.getHigh(),cours.getLow(),cours.getClose(),&cours);
        bougie->analyseBougie();
        //Ajouter la bougie a la QCandleStickSeries(methode append)
        series->append(bougie);

        *setBar<<cours.getVolume();
        categories<<cours.getDate().toString("dd.MM.yy");


        ema12->append(day,cours.getEMA12());
        ema26->append(day,cours.getEMA26());
        rsiSerie->append(day,cours.getRSI());
        rsiLimiteSup->append(day,70);
        rsiLimiteInf->append(day,30);
        macd1226->append(day,cours.getMACD());

        signal->append(day,cours.getSignalMACD());
        *setBarHistogrammeMACD<<cours.getMACD()-cours.getSignalMACD();

        day++;
        connect(bougie, SIGNAL(clickBougie(Bougie*)), this, SLOT(viewCoursOHLC(Bougie*)));
    }



    //QTCharts et QTChartsView pour les bougies + ema 12 et 26 periods
    chart =new QChart();
    chart->addSeries(series);
    chart->addSeries(ema12);
    chart->addSeries(ema26);
    chart->setTitle("Cours OHLC");
    chart->createDefaultAxes();
    axisX=new QBarCategoryAxis;
    axisX->append(categories);
    chart->setAxisX(axisX);
    series->attachAxis(axisX);
    axisX->setRange(categories[0],categories[16]);
    ema12->attachAxis(axisX);
    ema26->attachAxis(axisX);
    axisY= qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
    axisY->setMax(axisY->max() * 1.10);
    axisY->setMin(axisY->min() * 0.50);
    chartView = new QChartView(chart,this);
    chartView->setFixedSize(1100,550);

    //QTCharts et QTChartsView Volume
    seriesBar->append(setBar);
    chartBar =new QChart();
    chartBar->addSeries(seriesBar);
    chartBar->createDefaultAxes();
    axisXBar = qobject_cast<QBarCategoryAxis *>(chartBar->axes(Qt::Horizontal).at(0));
    axisXBar->setCategories(categories);
    axisXBar->setRange(categories[0],categories[16]);
    axisYBar= qobject_cast<QValueAxis *>(chartBar->axes(Qt::Vertical).at(0));
    axisYBar->setMax(axisYBar->max()*1.10);
    axisYBar->setMin(0);
    chartViewBar = new QChartView(chartBar,this);
    chartViewBar->setFixedSize(1100,250);

    //QTCharts et QTChartsView RSI
    chartRSI =new QChart();
    chartRSI->addSeries(rsiSerie);
    chartRSI->addSeries(rsiLimiteSup);
    chartRSI->addSeries(rsiLimiteInf);
    chartRSI->createDefaultAxes();
    axisXrsi=new QBarCategoryAxis;
    axisXrsi->append(categories);
    axisXrsi->setRange(categories[0],categories[16]);
    chartRSI->setAxisX(axisXrsi);
    rsiSerie->attachAxis(axisXrsi);
    rsiLimiteSup->attachAxis(axisXrsi);
    rsiLimiteInf->attachAxis(axisXrsi);
    axisYRSI= qobject_cast<QValueAxis *>(chartRSI->axes(Qt::Vertical).at(0));
    axisYRSI->setMax(100);
    axisYRSI->setMin(0);
    chartViewRSI = new QChartView(chartRSI,this);
    chartViewRSI->setFixedSize(1100,250);

    //QTCharts et QTChartsView MACD(12,26) + signal + histogramme
    seriesHistogrammeMACD->append(setBarHistogrammeMACD);
    chartMACD =new QChart();
    chartMACD->addSeries(macd1226);
    chartMACD->addSeries(signal);
    chartMACD->addSeries(seriesHistogrammeMACD);
    chartMACD->createDefaultAxes();
    axisXMACD=new QBarCategoryAxis;
    axisXMACD->append(categories);
    axisXMACD->setRange(categories[0],categories[16]);
    chartMACD->setAxisX(axisXMACD);
    macd1226->attachAxis(axisXMACD);
    seriesHistogrammeMACD->attachAxis(axisXMACD);
    signal->attachAxis(axisXMACD);
    axisYMACD= qobject_cast<QValueAxis *>(chartMACD->axes(Qt::Vertical).at(0));
    axisYMACD->setMax(axisYMACD->max()*1.1);
    axisYMACD->setMin(axisYMACD->min()*1.1);
    chartViewMACD = new QChartView(chartMACD,this);
    chartViewMACD->setFixedSize(1100,450);



    resultat=new QLabel(this);
    resultat->setFixedSize(180,50);
    openl =new QLabel("Open",this);
    highl =new QLabel("High",this);
    lowl =new QLabel("Low",this);
    closel =new QLabel("Close",this);
    volumel=new QLabel("Volume",this);
    informationBougie=new QLabel("Informations\nBougie",this);
    informationBougie->setFixedSize(180,200);


    open= new QLineEdit(this);
    high= new QLineEdit(this);
    low= new QLineEdit(this);
    close= new QLineEdit(this);
    volume= new QLineEdit(this);

    //QComboBox et QLabel pour les dates des graphiques
    dateDebutL= new QLabel("Date Debut Graphiques: ");
    dateFinL= new QLabel("Date Fin Graphiques: ");
    dateFinC= new QComboBox();
    dateDebutC= new QComboBox();

    dateFinC->addItems(categories);
    dateDebutC->addItems(categories);

    QString str;
    indicateursBox=new QComboBox();
    for(unsigned int i=0;i<evolution->getNbEmas();i++){
        indicateursBox->addItem("EMA "+str.setNum(i));
    }
    for(unsigned int i=0;i<evolution->getNbRsis();i++){
        indicateursBox->addItem("RSI "+str.setNum(i));
    }
    for(unsigned int i=0;i<evolution->getNbMacds();i++){
        indicateursBox->addItem("MCD "+str.setNum(i));
    }
    afficherInd=new QPushButton("Afficher Indicateurs");


    ok= new QPushButton("OK");
    updateDateGraphs= new QPushButton("Update Graphs");
    QHBoxLayout *layoutHOpen = new QHBoxLayout;
    QHBoxLayout *layoutHHigh = new QHBoxLayout;
    QHBoxLayout *layoutHLow = new QHBoxLayout;
    QHBoxLayout *layoutHClose = new QHBoxLayout;
    QHBoxLayout *layoutHVolume = new QHBoxLayout;

    QVBoxLayout *layoutVOHLCInfo = new QVBoxLayout;
    QVBoxLayout *layoutVUpdateDate = new QVBoxLayout;
    QVBoxLayout *layoutVButtonsRes = new QVBoxLayout;

    QVBoxLayout *layoutV = new QVBoxLayout;
    QVBoxLayout *layoutVCharts = new QVBoxLayout;
    fenetre = new QHBoxLayout;

    /*QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);*/

    layoutHOpen->addWidget(openl);
    layoutHOpen->addWidget(open);

    layoutHHigh->addWidget(highl);
    layoutHHigh->addWidget(high);

    layoutHLow->addWidget(lowl);
    layoutHLow->addWidget(low);

    layoutHClose->addWidget(closel);
    layoutHClose->addWidget(close);

    layoutHVolume->addWidget(volumel);
    layoutHVolume->addWidget(volume);

    layoutVOHLCInfo->addLayout(layoutHOpen);
    layoutVOHLCInfo->addLayout(layoutHHigh);
    layoutVOHLCInfo->addLayout(layoutHLow);
    layoutVOHLCInfo->addLayout(layoutHClose);
    layoutVOHLCInfo->addLayout(layoutHVolume);
    layoutVOHLCInfo->addWidget(informationBougie);
    layoutVUpdateDate->addWidget(dateDebutL);
    layoutVUpdateDate->addWidget(dateDebutC);
    layoutVUpdateDate->addWidget(dateFinL);
    layoutVUpdateDate->addWidget(dateFinC);
    layoutVUpdateDate->addWidget(indicateursBox);
    layoutVUpdateDate->addWidget(afficherInd);
    layoutVButtonsRes->addWidget(resultat);
    layoutVButtonsRes->addWidget(updateDateGraphs);
    layoutVButtonsRes->addWidget(ok);
    layoutV->addLayout(layoutVOHLCInfo);
    layoutV->addLayout(layoutVUpdateDate);
    layoutV->addLayout(layoutVButtonsRes);
    layoutV->setSpacing(10);


    layoutVCharts->addWidget(chartView);
    layoutVCharts->addWidget(chartViewMACD);
    layoutVCharts->addWidget(chartViewRSI);
    layoutVCharts->addWidget(chartViewBar);


    QScrollArea *scrollarea = new QScrollArea(this);
    scrollarea->setWidgetResizable(true);
    QFrame* inner =new QFrame(scrollarea);
    inner->setLayout(layoutVCharts);
    scrollarea->setWidget(inner);
    scrollarea->setMinimumSize( QSize( 1150, 300 ) );

    fenetre->addWidget(scrollarea);
    //fenetre->addWidget(chartView);
    fenetre->addLayout(layoutV);

    setLayout(fenetre);
    connect(ok,SIGNAL(clicked()),this,SLOT(saveCoursOHLC()));
    connect(updateDateGraphs,SIGNAL(clicked()),this,SLOT(updateGraphsScroll()));
    connect(afficherInd,SIGNAL(clicked()),this,SLOT(afficherIndicateur()));
}

void EvolutionViewer::viewCoursOHLC(Bougie *b){
    QString str,strI,strS,ema,rsi,macd,ema26,signal;
    str.setNum(b->getCoursOHLC().getOpen());
    open->setText(str);
    str.setNum(b->getCoursOHLC().getHigh());
    high->setText(str);
    str.setNum(b->getCoursOHLC().getLow());
    low->setText(str);
    str.setNum(b->getCoursOHLC().getClose());
    close->setText(str);
    str.setNum(b->getCoursOHLC().getVolume());
    volume->setText(str);

    informationBougie->setText("Informations\nBougie: "+b->getCoursOHLC().getDate().toString("dd/MM/yyyy")+
                               "\nType: "+b->getType()+
                               "\nTendence: "+b->getTendence()+
                               "\nTaille Corps: "+str.setNum(b->getCorps())+
                               "\nMeche Inferieur: "+strI.setNum(b->getMechI())+
                               "\nMeche Superieur: "+strS.setNum(b->getMechS())+
                               "\nEMA 12 Periods: "+ema.setNum(b->getCoursOHLC().getEMA12())+
                               "\nEMA 26 Periods: "+ema26.setNum(b->getCoursOHLC().getEMA26())+
                               "\nRSI 9 Periods: "+rsi.setNum(b->getCoursOHLC().getRSI())+
                               "\nMACD(12,26): "+macd.setNum(b->getCoursOHLC().getMACD())+
                               "\nSignal(9): "+signal.setNum(b->getCoursOHLC().getSignalMACD()));

    lastBougieClicked = b;
}
void EvolutionViewer::saveCoursOHLC(){
    try {
    QString e="Remplissez toutes les\ninformations demandées";
    if(open->text().isEmpty()||high->text().isEmpty()||low->text().isEmpty()||close->text().isEmpty()
            ||volume->text().isEmpty())
        throw e;
    double o=open->text().toDouble();
    double h=high->text().toDouble();
    double l=low->text().toDouble();
    double c=close->text().toDouble();
    double v=volume->text().toDouble();
    lastBougieClicked->getCoursOHLC().setCours(o,h,l,c);
    lastBougieClicked->getCoursOHLC().setVolume(v);
    lastBougieClicked->setOpen(o);
    lastBougieClicked->setHigh(h);
    lastBougieClicked->setLow(l);
    lastBougieClicked->setClose(c);
    evolution->updateIndicateurs();
    updateGraphsSet();
    resultat->setText("Modification bien reussi");
    } catch(const QString e){
        resultat->setText(e);
    }catch (TradingException e){
        resultat->setText(e.getInfo());
    }
}

void Bougie::analyseBougie(){
    Bougie* b=this;
    double openBougie = b->cours->getOpen();
    double closeBougie = b->cours->getClose();
    double highBougie = b->cours->getHigh();
    double lowBougie = b->cours->getLow();
    if(openBougie<=closeBougie){  //Tendance haussiere
        mechS = highBougie-closeBougie;
        mechI = openBougie-lowBougie;
        corpsTaille = closeBougie-openBougie;
        tendence="Haussiere";
        //Type de Bougie
        if(corpsTaille<mechS || corpsTaille<mechI){ //Toupie
            type="Toupie";
            if(openBougie==closeBougie)  //->Doji
                type="Doji";
            else if (lowBougie<openBougie && closeBougie==highBougie)
                type="Pendu";
            else if (highBougie>closeBougie && openBougie==lowBougie)   //->Etoile filante
                type="Etoile filante";
        }

    }else {  //Tendance baissiere
        mechS = highBougie-openBougie;
        mechI = closeBougie-lowBougie;
        corpsTaille = openBougie-closeBougie;
        tendence="Baissiere";
        if(corpsTaille<mechS || corpsTaille<mechI){ //Toupie
            type="Toupie";
            if(openBougie==closeBougie)  //->Marteau
                type="Marteau.";
        }
    }
}

void EvolutionViewer::updateGraphsScroll(){
    QString dateD,dateF;
    unsigned int dDebut=0,dFin=0;
    dateD=dateDebutC->currentText();
    dateF=dateFinC->currentText();
    try{
        axisX->setRange(dateD,dateF);
        axisXBar->setRange(dateD,dateF);
        axisXrsi->setRange(dateD,dateF);

        for(QStringList::iterator it=categories.begin();it!=categories.end();++it){
            if(*it==dateD) break;
            dDebut++;
        }
        for(QStringList::iterator it=categories.begin();it!=categories.end();++it){
            if(*it==dateF) break;
            dFin++;
        }
        double max,min,maxV,maxMACD,minMACD;
        EvolutionCours::iterator c;
        c=evolution->getCoursI(dDebut);
        max=(*c).getHigh();
        min=(*c).getLow();
        maxV=(*c).getVolume();
        maxMACD=(*macd1226).at(dDebut).y();
        minMACD=(*macd1226).at(dDebut).y();
        for (unsigned int i=dDebut;i<=dFin;i++){
            c=evolution->getCoursI(i);
            if((*c).getHigh()>max) max=(*c).getHigh();
            if((*c).getLow()<min) min=(*c).getLow();
            if((*c).getVolume()>maxV) maxV=(*c).getVolume();
            if((*macd1226).at(i).y()>maxMACD) maxMACD=(*macd1226).at(i).y();
            if((*macd1226).at(i).y()<minMACD) minMACD=(*macd1226).at(i).y();
        }

        axisY->setMax(max*1.2);
        axisY->setMin(min*0.50);
        axisYBar->setMax(maxV*1.2);
        axisYMACD->setMax(maxMACD*1.2);
        axisYMACD->setMin(minMACD);
        axisXMACD->setRange(dateD,dateF);
        resultat->setText("Recommandation: intervalle compris  \
                        \nentre 1 et 30 cours\npour un mieux affichage");
    }catch(const QString e){
        resultat->setText(e);
    }

}

void EvolutionViewer::updateGraphsSet(){
    int day=0;
    for (EvolutionCours::iterator it=evolution->begin();it!=evolution->end();++it){
        CoursOHLC &cours=*it;
        ema12->replace(day,day,cours.getEMA12());
        ema26->replace(day,day,cours.getEMA26());
        macd1226->replace(day,day,cours.getMACD());
        rsiSerie->replace(day,day,cours.getRSI());
        setBar->replace(day,cours.getVolume());
        day++;
    }
    seriesBar->insert(0,setBar);
}

void EvolutionViewer::afficherIndicateur(){
    QString e="Il n'y a aucune indicateur, desole";
    QString numT,type;
    QLineSeries *serie = new QLineSeries();
    int i=0;
    try {
         if(indicateursBox->currentText().isEmpty()) throw e;
         for(unsigned int i=0;i<3;i++) type[i]=indicateursBox->currentText()[i];
         numT=indicateursBox->currentText()[4];
         int num=numT.toInt();
         if(type=="EMA"){
            serie->setName("EMA "+numT);
            for (QList<double>::const_iterator  it=evolution->getEmaT(num).begin();
                 it!=evolution->getEmaT(num).end(); ++it){
                serie->append(i,*it);
                i++;
            }
            chart->addSeries(serie);
            serie->attachAxis(axisX);
         }else if(type=="RSI"){
             serie->setName("SRI "+numT);
             for (QList<double>::const_iterator it=evolution->getRsiT(num).begin();
                  it!=evolution->getRsiT(num).end(); ++it){
                 serie->append(i,*it);
                 i++;
             }
             chartRSI->addSeries(serie);
             serie->attachAxis(axisXrsi);
         }else{
             QLineSeries *signal = new QLineSeries();
             serie->setName("MACD "+numT);
             signal->setName("Signal MACD "+numT);
             for (QList<double>::const_iterator it=evolution->getMacdT(num).begin();
                  it!=evolution->getMacdT(num).end(); ++it){
                 serie->append(i,*it);
                 i++;
             }
             for (QList<double>::const_iterator it=evolution->getSignalT(num).begin();
                  it!=evolution->getSignalT(num).end(); ++it){
                 signal->append(i,*it);
                 i++;
             }
             chartMACD->addSeries(serie);
             chartMACD->addSeries(signal);
             serie->attachAxis(axisXMACD);
             signal->attachAxis(axisXMACD);

        }

    } catch(const QString e){
        resultat->setText(e);
    }
}


