#ifndef CALIGNE5_H
#define CALIGNE5_H

#include <QMainWindow>

#include "constante.h"
#include "enumeration.h"

class QLabel;
class CJeu;
class SDLPlayer;

class CAligne5 : public QMainWindow
{
    Q_OBJECT

public:
    CAligne5(QWidget *parent = 0);
    ~CAligne5();

private slots:
    void slotAbout();
    void slotAboutQt();
    void slotAide();
    void slotArretPartie();
    void slotDebutPartie();
    void slotPreferences();
    void slotQuitterProg();

protected:
    void mouseReleaseEvent( QMouseEvent *event );
    void closeEvent( QCloseEvent *event );

private:
    void createActions();
    void createMenus();
    void createStatusBar();
    void loadImage(const QString &fileName, QImage *image);
    void afficherImageDebutJeu();
    void clicBoutonGauche();
    void OrdiJoue();
    void clicBoutonDroit();
    void cloturePartie( const CODEFIN codefin );
    void afficheBouleOrdi( const QRect r, const COULEURBOULE couleurboule );
    void afficheUneBoule( const QRect r, const COULEURBOULE couleurboule );
    void afficherMsgDebuterJeu();
    void afficherMsgDebutPartie();
    void afficherMsgFinPartie();
    void afficherMsgJoueurJoue();
    void afficherMsgNbPointJoueur();
    void afficherMsgNbPointOrdi();
    void afficherMsgOrdiJoue();
    void afficherStatusBar();
    void afficherMsgNiveauJeu();
    void afficherImageFinJeu();
    void afficherImageLabel();
    void afficherMsgOrdiGagne();
    void afficherMsgFermerAppli();
    void faitTemporisation();
    void faitClignoter( const QRect r, const COULEURBOULE couleurboule );
    void dessineUneBoule( const QRect r, const COULEURBOULE couleurboule );
    void ecrireMsgFinJeu( const CODEFIN codefin );

    QMenu    *m_jeuMenu;
    QMenu    *m_optionsMenu;
    QMenu    *m_aideMenu;

    QAction  *m_aboutAct;
    QAction  *m_aideAct;
    QAction  *m_arretpartieAct;
    QAction  *m_debutpartieAct;
    QAction  *m_preferenceAct;
    QAction  *m_quitterAct;
    QAction  *m_aboutQtAct;

    QLabel  *m_imageLabel;

    QLabel  *m_pLabel0;
    QLabel  *m_pLabel1;
    QLabel  *m_pLabel2;

    int		m_heightMenuBar;
    QString	m_messagestatusbar;
    QSize	resultSize;

    QImage	m_imgMemPlateau;
    QImage	m_imgPlateau;
    QPixmap	m_pmMemPlateau;
    QImage	m_imgCopie;

    QImage	m_imgFinJeu;
    QImage	m_imgDebutJeu;
    QImage	m_imgDessinBoule;

    CJeu	*m_pcJeu;
    bool	m_fPartie;
    int		m_posClicX;
    int		m_posClicY;

    SDLPlayer	*mySDLPlayer;

};

#endif // CALIGNE5_H
