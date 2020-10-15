#ifndef MODESELECTION_H
#define MODESELECTION_H
#include "headerp.h"
#include "menu.h"
#include "menucsv.h"
#include <QDialog>

namespace Ui {
class ModeSelection;
}

/*! \class ModeSelection
 *  \brief Classe permettant de gérer l'interface graphique du mode de saisie des données (CSV ou manuel).
 */

class ModeSelection : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief ModeSelection
     *
     * Constructeur de la classe ModeSelection
     *
     * \param parent : parent de l'objet créé
     */
    explicit ModeSelection(QWidget *parent = nullptr);
    ~ModeSelection();

private slots:
    void on_okButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::ModeSelection *ui;
};

#endif // MODESELECTION_H
