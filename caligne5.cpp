#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QPainter>
#include <QTime>

#include "caligne5.h"
#include "cpreference.h"
#include "cjeu.h"
#include "sdlplayer.h"

CAligne5::CAligne5(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle( NOM_PROG );
    setWindowIcon( QIcon( ":/icons/IconeProg.png") );

    createActions();
    createMenus();
    createStatusBar();

/// creation Layout
    QWidget *widget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;

    widget = new QWidget(this);

    vboxLayout = new QVBoxLayout(widget);
    vboxLayout->setSpacing(6);
/// qt6    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));

    resultSize = QSize( W_PLATEAU, H_PLATEAU );
    loadImage( ":/images/Plateau.png", &m_imgPlateau );
    m_imgMemPlateau = m_imgPlateau;
    m_pmMemPlateau = QPixmap::fromImage(m_imgMemPlateau);

    m_imageLabel = new QLabel(this);
    m_imageLabel->setObjectName(QString::fromUtf8("imageLabel"));
    m_imageLabel->setPixmap( m_pmMemPlateau );

    vboxLayout->addWidget(m_imageLabel);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
/// qt6    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));

    m_pLabel0 = new QLabel(this);
    m_pLabel0->setObjectName(QString::fromUtf8("pLabel0"));
    QFont font0;
    font0.setPointSize(10);
    font0.setWeight(QFont::Medium);
    m_pLabel0->setFont(font0);
    m_pLabel0->setFrameShape(QFrame::WinPanel);
    m_pLabel0->setFrameShadow(QFrame::Sunken);
    m_pLabel0->setText(tr("POINTS JOUEUR : "));

    hboxLayout1->addWidget(m_pLabel0);

    m_pLabel1 = new QLabel(this);
    m_pLabel1->setObjectName(QString::fromUtf8("pLabel1"));
    QFont font1;
    font1.setPointSize(10);
    font1.setWeight(QFont::Medium);
    m_pLabel1->setFont(font1);
    m_pLabel1->setFrameShape(QFrame::WinPanel);
    m_pLabel1->setFrameShadow(QFrame::Sunken);
    m_pLabel1->setText(tr("POINTS ORDI : "));

    hboxLayout1->addWidget(m_pLabel1);

    m_pLabel2 = new QLabel(this);
    m_pLabel2->setObjectName(QString::fromUtf8("pLabel2"));
    QFont font2;
    font2.setPointSize(10);
    font2.setWeight(QFont::Medium);
    m_pLabel2->setFont(font2);
    m_pLabel2->setFrameShape(QFrame::WinPanel);
    m_pLabel2->setFrameShadow(QFrame::Sunken);
    m_pLabel2->setText(tr("NIVEAU : "));

    hboxLayout1->addWidget(m_pLabel2);

    vboxLayout->addLayout(hboxLayout1);

    setCentralWidget(widget);

    QPoint pos = QPoint( 100, 100 );
    QSize size = QSize( W_PLATEAU, H_PLATEAU+31 );
    setMaximumSize(size);
    resize(size);
    move(pos);

    srand ( time (0) );

/// Initialise Images et Son
    resultSize = QSize( W_DEBUTJEU, H_DEBUTJEU );
    loadImage( ":/images/DebutJeu.png", &m_imgDebutJeu );
    loadImage( ":/images/FinJeu.png", &m_imgFinJeu );
    resultSize = QSize( W_DESSINBOULE, H_DESSINBOULE );
    loadImage( ":/images/DessinBoule.png", &m_imgDessinBoule );

    mySDLPlayer = new SDLPlayer();

/// Création de JEU
    m_pcJeu = new CJeu();

    afficherImageDebutJeu();

    m_fPartie = false;
}

CAligne5::~CAligne5()
{
    delete m_pcJeu;
}

/// ORDI JOUE
void CAligne5::OrdiJoue()
{
    afficherMsgOrdiJoue();
    QRect	rect;
    COULEURBOULE	couleur;
    CODEFIN retour = m_pcJeu->joueurJoue( ORDI );
    switch( retour )
    {
        case ORDIFIN :
            afficherMsgOrdiGagne();
            rect = m_pcJeu->fournirRectCalcule();
            couleur = m_pcJeu->fournirCouleurBoule( ORDI );
            afficheBouleOrdi( rect, couleur );
            faitTemporisation();
            // QMessageBox msgBox1(QMessageBox::Information, NOM_PROG + tr(" - Perdu"),
            //                    QString(tr(" DÉSOLÉ !"
            //                               "\n\n Partie gagnée par l'ordinateur. \n")),
            //                    { },
            //                    this);
            // msgBox1.exec();
            cloturePartie( ORDIFIN );
            break;
        case PARTIENULLE :
            // QMessageBox msgBox2(QMessageBox::Information, NOM_PROG + tr(" - Égalité"),
            //                    QString(tr(" PARTIE À ÉGALITÉ !"
            //                               "\n\n Aucune case intéressante à choisir. \n")),
            //                    { },
            //                    this);
            // msgBox2.exec();
            cloturePartie( PARTIENULLE );
            break;
        case CONTINUE :
            rect = m_pcJeu->fournirRectCalcule();
            couleur = m_pcJeu->fournirCouleurBoule( ORDI );
            afficheBouleOrdi( rect, couleur );
            afficherMsgJoueurJoue();
            m_pcJeu->definirPeriodeJeu ( HUMAINJOUE );
            break;
        default:
            break;
    }
}

void CAligne5::mouseReleaseEvent( QMouseEvent *event )
{
    if( m_pcJeu->fournirPeriodeJeu() == HUMAINJOUE )
    {
        m_posClicX = event->position().x();
        m_posClicY = event->position().y();
//		m_posClicY -= (m_heightMenuBar + 2);
        m_posClicY -= (m_heightMenuBar);
        m_pcJeu->definirPositionClicXY( m_posClicX, m_posClicY );

        switch ( event->button() )
        {
            case Qt::LeftButton :	clicBoutonGauche();	break;
            case Qt::RightButton :	clicBoutonDroit();	break;
            default:
            break;
        }
    }
}

void CAligne5::clicBoutonGauche()
{
    QRect	rect;
    COULEURBOULE	couleur;
    CODEFIN retour = m_pcJeu->joueurJoue( HUMAIN );
    switch( retour )
    {
        case HUMAINFIN :
            rect = m_pcJeu->fournirRectCalcule();
            couleur = m_pcJeu->fournirCouleurBoule( HUMAIN );
            afficheUneBoule( rect, couleur );
            faitTemporisation();
            // QMessageBox msgBox1(QMessageBox::Information, NOM_PROG + tr(" - Gagné"),
            //                    QString(tr(" BRAVO !"
            //                               "\n\n Partie gagnée par le joueur. \n")),
            //                    { },
            //                    this);
            // msgBox1.exec();
            cloturePartie( HUMAINFIN );
            break;
        case PARTIENULLE :
            // QMessageBox msgBox2(QMessageBox::Information, NOM_PROG + tr(" - Égalité"),
            //                    QString(tr(" PARTIE À ÉGALITÉ !"
            //                               "\n\n Aucune case vide à choisir. \n")),
            //                    { },
            //                    this);
            // msgBox2.exec();
            cloturePartie( PARTIENULLE );
            break;
        case CONTINUE :
            rect = m_pcJeu->fournirRectCalcule();
            couleur = m_pcJeu->fournirCouleurBoule( HUMAIN );
            afficheUneBoule( rect, couleur );
            afficherMsgOrdiJoue();
            m_pcJeu->definirPeriodeJeu ( ORDIJOUE );
            OrdiJoue();
            break;
        default:
            mySDLPlayer->playSound("jndqaligne5_err");
            break;
    }
}

void CAligne5::clicBoutonDroit()
{
    bool fclic = m_pcJeu->testerClicDansCadre();
    if( true == fclic )
    {
        bool fpos = m_pcJeu->fournirMeilleurEmplacement();
        if( true == fpos )
        {
            m_pcJeu->definirFlagEchange( true );
            QImage imgCopie = m_imgMemPlateau;
            QRect	rect = m_pcJeu->fournirRectCalcule();
            COULEURBOULE cb = m_pcJeu->fournirCouleurBoule( HUMAIN );
            faitClignoter( rect, cb );
            m_imgMemPlateau = imgCopie;
            afficherImageLabel();
        }
    }
    else
    {
        m_pcJeu->echangeJeu();
        m_pcJeu->definirFlagEchange( true );
        m_imgMemPlateau = m_imgPlateau;
        QRect	rect;
        int numcase;
        quint8 contenucase;
        COULEURBOULE couleur;
        for(int i = 0; i < HV_NBRECT; i++)
        {
            for(int j = 0; j < HV_NBRECT; j++)
            {
                numcase = (i * HV_NBRECT) + j;
                contenucase = m_pcJeu->fournirContenuCase( numcase );
                rect = m_pcJeu->fournirRectTrou( i, j );
                if( contenucase == CHUMAIN )
                    couleur = m_pcJeu->fournirCouleurBoule( HUMAIN );
                if( contenucase == CORDI )
                    couleur = m_pcJeu->fournirCouleurBoule( ORDI );
                if( contenucase != CVIDE )
                    afficheUneBoule( rect, couleur );
            }
        }
        afficherImageLabel();
        afficherMsgOrdiJoue();
        m_pcJeu->definirPeriodeJeu ( ORDIJOUE );
        OrdiJoue();
    }
}

void CAligne5::slotDebutPartie()
{
    if ( true == m_fPartie )
    {
        QMessageBox msgBox(QMessageBox::Information, NOM_PROG + tr(" - Jouer"),
                            QString(tr("Partie en cours..."
                                    "\n\nFaire d'abord Menu Jeu : Arrêter ou F5"
                                    "\net ensuite Menu Jeu : Jouer ou F2\n")),
                            { },
                            this);
        msgBox.exec();
    }
    else
    {
        m_preferenceAct->setEnabled( false );
        m_fPartie = true;
        m_pcJeu->definirFlagEchange( false );
        m_pcJeu->definirQuiGagne( PERSONNE );

        afficherMsgDebutPartie();

        afficherMsgNbPointJoueur();
        afficherMsgNbPointOrdi();
        afficherMsgNiveauJeu();

        m_pcJeu->initialiserCaseJeu();

        m_imgMemPlateau = m_imgPlateau;
        afficherImageLabel();

        if( m_pcJeu->fournirQuiCommence() == HUMAIN )
        {
            afficherMsgJoueurJoue();
            m_pcJeu->definirPeriodeJeu( HUMAINJOUE );
        }
        else
        {
            afficherMsgOrdiJoue();
            m_pcJeu->definirPeriodeJeu( ORDIJOUE );
            OrdiJoue();
        }
    }
}

void CAligne5::createActions()
{
    m_debutpartieAct = new QAction( tr("Jouer"), this );
    m_debutpartieAct->setShortcut( tr("F2") );
    m_debutpartieAct->setStatusTip( tr("Débuter une partie") );
    connect( m_debutpartieAct, SIGNAL(triggered()), this, SLOT(slotDebutPartie()) );

    m_arretpartieAct = new QAction( tr("Arrêter"), this );
    m_arretpartieAct->setShortcut( tr("F5") );
    m_arretpartieAct->setStatusTip( tr("Arrêter une partie") );
    connect( m_arretpartieAct, SIGNAL(triggered()), this, SLOT(slotArretPartie()) );

    m_quitterAct = new QAction( tr("&Quitter"), this );
    m_quitterAct->setShortcut( tr("Ctrl+Q") );
    m_quitterAct->setStatusTip( tr("Quitter Aligne5") );
    connect( m_quitterAct, SIGNAL(triggered()), this, SLOT(slotQuitterProg()) );

    m_preferenceAct = new QAction( tr("&Préférences..."), this );
    m_preferenceAct->setShortcut( tr("Ctrl+P") );
    m_preferenceAct->setStatusTip( tr("Choisir les préférences") );
    connect( m_preferenceAct, SIGNAL(triggered()), this, SLOT(slotPreferences()) );

    m_aideAct = new QAction( tr("Aide"), this );
    m_aideAct->setShortcut( tr("F1") );
    m_aideAct->setStatusTip( tr("Affiche l'aide de Aligne5") );
    connect( m_aideAct, SIGNAL(triggered()), this, SLOT(slotAide()) );

    m_aboutAct = new QAction( tr("À Propos de : Aligne5"), this );
//	m_aboutAct->setShortcut( tr("Ctrl+A") );
    m_aboutAct->setStatusTip( tr("À Propos de : Aligne5") );
    connect( m_aboutAct, SIGNAL(triggered()), this, SLOT(slotAbout()) );

    m_aboutQtAct = new QAction( tr("À Propos de Qt"), this );
//	m_aboutQtAct->setShortcut( tr("Ctrl+A") );
    m_aboutQtAct->setStatusTip( tr("À Propos de Qt") );
    connect( m_aboutQtAct, SIGNAL(triggered()), this, SLOT(slotAboutQt()) );
}

void CAligne5::createMenus()
{
    m_jeuMenu = menuBar()->addMenu(tr("&Jeu"));
    m_jeuMenu->addAction(m_debutpartieAct);
    m_jeuMenu->addAction(m_arretpartieAct);
    m_jeuMenu->addSeparator();
    m_jeuMenu->addAction(m_quitterAct);

    m_optionsMenu = menuBar()->addMenu(tr("&Options"));
    m_optionsMenu->addAction(m_preferenceAct);

    m_aideMenu = menuBar()->addMenu(tr("&Aide"));
    m_aideMenu->addAction(m_aideAct);
    m_aideMenu->addSeparator();
    m_aideMenu->addAction(m_aboutAct);
    m_aideMenu->addAction(m_aboutQtAct);

    m_heightMenuBar = menuBar()->height();
}

void CAligne5::createStatusBar()
{
    QFont font;
    font.setBold( true );
    statusBar()->setFont(font);

    statusBar()->showMessage(tr("Prêt"));
}

/// FONCTIONS SLOTS

void CAligne5::slotAbout()
{
    QMessageBox::about ( this, tr("À propos de ") + NOM_PROG,
                        tr("<h2>%1 %2</h2>"
                        "<p><h3>Simple petit jeu de logique...</h3>"
                        "<p>Copyright %3."
                        "<p>Ce programme est distribué selon les termes de la GPL v2."
                        "<p>")
                         .arg( NOM_PROG )
                         .arg( VERSION_PROG )
                         .arg( COPYRIGHT )
                         );
}

void CAligne5::slotAboutQt()
{
    QMessageBox::aboutQt ( this, tr("About Qt") );
}

void CAligne5::slotAide()
{
    QMessageBox msgBox(QMessageBox::Information, NOM_PROG + tr(" - Aide"),
                       QString(tr("Il faut aligner 5 boules"
                               "\nde la même couleur et c'est gagné!"
                               "\n\n(Pour tricher : bouton droit)\n")),
                       { },
                       this);
    msgBox.exec();
}

void CAligne5::slotArretPartie()
{
    if( m_pcJeu->fournirPeriodeJeu() == HUMAINJOUE )
    {
        QMessageBox msgBox(QMessageBox::Question, NOM_PROG + tr(" - Arrêter"),
                           tr(" Arrêter la partie en cours ? \n"),
                           { },
                           this);
        //        msgBox.setInformativeText(tr(" Texte information "));
        msgBox.addButton(QMessageBox::No);
        msgBox.addButton(QMessageBox::Yes);
        int reponse = msgBox.exec();
        switch (reponse)
        {
            case QMessageBox::No:           /// Continuer
                break;
            case QMessageBox::Yes:          /// Arrêter
                cloturePartie ( ARRETPARTIE );
                break;
            default:
                break;
        }
    }
}

void CAligne5::slotPreferences()
{
    NOMJOUEUR nom = m_pcJeu->fournirQuiCommence();
    COULEURBOULE couleur = m_pcJeu->fournirCouleurBoule( HUMAIN );
    NIVEAUJEU niveau = m_pcJeu->fournirNiveauJeu();

    CPreference	pref( nom, couleur, niveau, this );
    bool reponse = pref.exec();
    if( true == reponse )
    {
        nom = pref.fournitCommence();
        couleur = pref.fournitCouleur();
        niveau = pref.fournitNiveau();

        m_pcJeu->definirQuiCommence( nom );
        m_pcJeu->definirNiveauJeu( niveau );
        m_pcJeu->definirCouleurBoule( HUMAIN, couleur );

        afficherMsgNiveauJeu();
    }
}

void CAligne5::slotQuitterProg()
{
    QMessageBox msgBox(QMessageBox::Question, NOM_PROG + tr(" - Quitter"),
                       tr(" Quitter le jeu %1 ? \n").arg( NOM_PROG ),
                       { },
                       this);
    //        msgBox.setInformativeText(tr(" Texte information "));
    msgBox.addButton(QMessageBox::No);
    msgBox.addButton(QMessageBox::Yes);
    int reponse = msgBox.exec();
    switch (reponse)
    {
        case QMessageBox::No:           /// Continuer
            break;
        case QMessageBox::Yes:          /// Arrêter
            qApp->exit();
            break;
        default:
            break;
    }
}

///FONCTIONS GENERALES

void CAligne5::closeEvent( QCloseEvent *event )
{
    QString msg = statusBar()->currentMessage();
    afficherMsgFermerAppli();
    QMessageBox msgBox(QMessageBox::Question, NOM_PROG + tr(" - Fermer"),
                       tr(" Fermer le jeu %1 ? \n").arg( NOM_PROG ),
                       { },
                       this);
    //        msgBox.setInformativeText(tr(" Texte information "));
    msgBox.addButton(QMessageBox::No);
    msgBox.addButton(QMessageBox::Yes);
    int reponse = msgBox.exec();
    switch (reponse)
    {
        case QMessageBox::No:           /// Continuer
            statusBar()->showMessage( msg );
            event->ignore();
            break;
        case QMessageBox::Yes:          /// Arrêter
            event->accept();
            break;
        default:
            break;
    }
}

void CAligne5::loadImage(const QString &fileName, QImage *image)
{
    image->load(fileName);

    QImage fixedImage(resultSize, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&fixedImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(fixedImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage( 0, 0, *image );
    painter.end();

    *image = fixedImage;
}

void CAligne5::cloturePartie( const CODEFIN codefin )
{
    afficherMsgFinPartie();
    int nbpointjoueur = m_pcJeu->fournirNbPoint( HUMAIN );
    int nbpointordi = m_pcJeu->fournirNbPoint( ORDI );
    switch(codefin)
    {
        case ORDIFIN :
            nbpointordi += ( 2 * m_pcJeu->fournirNiveauJeu() );
            break;
        case HUMAINFIN :
            if( false == m_pcJeu->fournirFlagEchange() )
            {
                nbpointjoueur += ( 2 * m_pcJeu->fournirNiveauJeu() );
            }
            else
            {
                nbpointjoueur += 1;
            }
            break;
        case PARTIENULLE :
            nbpointordi += 1;
            nbpointjoueur += 1;
            break;
        case ARRETPARTIE  :
            nbpointordi += 0;
            nbpointjoueur += 0;
            break;
        default :
            nbpointordi += 0;
            nbpointjoueur += 0;
    }

    m_pcJeu->definirPeriodeJeu ( ATTENTE );
    m_pcJeu->definirQuiGagne( PERSONNE );
    m_pcJeu->definirNbPoint( HUMAIN, nbpointjoueur );
    m_pcJeu->definirNbPoint( ORDI, nbpointordi );

    m_preferenceAct->setEnabled( true );
    m_fPartie = false;
    afficherMsgNbPointJoueur();
    afficherMsgNbPointOrdi();

    if( ARRETPARTIE == codefin )
    {
        afficherImageDebutJeu();
    }
    else
    {
        ecrireMsgFinJeu( codefin );
    }
}

void CAligne5::afficheBouleOrdi( const QRect r, const COULEURBOULE couleurboule )
{
    faitClignoter( r, couleurboule );
    afficheUneBoule( r, couleurboule );
}

void CAligne5::afficheUneBoule( const QRect r, const COULEURBOULE couleurboule )
{
    dessineUneBoule( r, couleurboule );
    afficherImageLabel();
}

void CAligne5::dessineUneBoule( const QRect r, const COULEURBOULE couleurboule )
{
    m_imgCopie = m_imgMemPlateau;
    QPainter painter(&m_imgCopie);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage( r.x(), r.y(), m_imgDessinBoule, (couleurboule * INCX_BOULE), 0, WH_BOULE, WH_BOULE );
    painter.end();
    m_imgMemPlateau = m_imgCopie;
}

void CAligne5::faitClignoter( const QRect r, const COULEURBOULE couleurboule )
{
    QPixmap	pmMemPlateau;

    QImage imgCopie;
    imgCopie = m_imgMemPlateau;

    QImage imgPlateauSansBoule;
    imgPlateauSansBoule = m_imgMemPlateau;

    QImage imgPlateauAvecBoule;
    dessineUneBoule( r, couleurboule );
    imgPlateauAvecBoule = m_imgMemPlateau;

    NIVEAUJEU niveau = m_pcJeu->fournirNiveauJeu();
    // long n;
    // QTime t;
    int nbfois;

    if( niveau == FORT )	nbfois = NBFOISFORT;
    if( niveau == MOYEN )	nbfois = NBFOISMOYEN;
    if( niveau == FAIBLE )	nbfois = NBFOISFAIBLE;

    for( int i = 0; i < nbfois; i++ )
    {
        pmMemPlateau = QPixmap::fromImage( imgPlateauAvecBoule );
        m_imageLabel->setPixmap( pmMemPlateau );

        double aa = 0.0;
        double bb = 0.0;

        for( int i = 0; i < TEMPSHOW; i++ )
        {
            for( int i = 0; i < 20; i++ )
            {
                for( int i = 0; i < 20; i++ )
                {
                    aa = 11.11;
                    bb = 11.11;
                    aa = aa * bb;
                    bb = bb * 1.1;
                    aa = aa * bb;
                    bb = bb / 2.2;
                    aa = aa * bb;
                    bb = bb * 3.3;
                    aa = aa * bb;
                    bb = bb / 4.4;
                    aa = aa * bb;
                    qApp->processEvents( QEventLoop::ExcludeUserInputEvents );
                }
            }
        }
        // t.start();
        // while ( true )
        // {
        //     n = t.elapsed();
        //     if ( n > TEMPSHOW )	break;
        //     qApp->processEvents( QEventLoop::ExcludeUserInputEvents);
        // }

        pmMemPlateau = QPixmap::fromImage( imgPlateauSansBoule );
        m_imageLabel->setPixmap( pmMemPlateau );

        for( int i = 0; i < TEMPHIDE; i++ )
        {
            for( int i = 0; i < 20; i++ )
            {
                for( int i = 0; i < 20; i++ )
                {
                    aa = 11.11;
                    bb = 11.11;
                    aa = aa * bb;
                    bb = bb * 1.1;
                    aa = aa * bb;
                    bb = bb / 2.2;
                    aa = aa * bb;
                    bb = bb * 3.3;
                    aa = aa * bb;
                    bb = bb / 4.4;
                    aa = aa * bb;
                    qApp->processEvents( QEventLoop::ExcludeUserInputEvents );
                }
            }
        }
        // t.start();
        // while ( true )
        // {
        //     n = t.elapsed();
        //     if ( n > TEMPHIDE )	break;
        //     qApp->processEvents( QEventLoop::ExcludeUserInputEvents);
        // }
    }

    m_imgMemPlateau = imgCopie;
    afficherImageLabel();
}

void CAligne5::faitTemporisation()
{
    NIVEAUJEU niveau = m_pcJeu->fournirNiveauJeu();
    long temporisation;		/// en milliseconde (1000 = 1 seconde)

    if( niveau == FORT )	temporisation = TEMPOFORT;
    if( niveau == MOYEN )	temporisation = TEMPOMOYEN;
    if( niveau == FAIBLE )	temporisation = TEMPOFAIBLE;

    double aa = 0.0;
    double bb = 0.0;

    for( long i = 0; i < temporisation; i++ )
    {
        for( int i = 0; i < 20; i++ )
        {
            for( int i = 0; i < 20; i++ )
            {
                aa = 11.11;
                bb = 11.11;
                aa = aa * bb;
                bb = bb * 1.1;
                aa = aa * bb;
                bb = bb / 2.2;
                aa = aa * bb;
                bb = bb * 3.3;
                aa = aa * bb;
                bb = bb / 4.4;
                aa = aa * bb;
                qApp->processEvents( QEventLoop::ExcludeUserInputEvents );
            }
        }
    }
    // long n;
    // QTime t;
    // t.start();

    // while ( true )
    // {
    //     n = t.elapsed();
    //     if ( n > temporisation )	break;
    //     qApp->processEvents( QEventLoop::ExcludeUserInputEvents);
    // }
}

void CAligne5::afficherImageDebutJeu()
{
    m_imgCopie = m_imgMemPlateau;
    QPainter painter(&m_imgCopie);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(X_DEBUTJEU, Y_DEBUTJEU, m_imgDebutJeu);
    painter.end();
    m_imgMemPlateau = m_imgCopie;
    afficherImageLabel();

    afficherMsgDebuterJeu();
}

void CAligne5::afficherImageFinJeu()
{
    m_pcJeu->definirPeriodeJeu( ATTENTE );

    m_imgCopie = m_imgMemPlateau;
    QPainter painter(&m_imgCopie);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(X_FINJEU, Y_FINJEU, m_imgFinJeu);
    painter.end();
    m_imgMemPlateau = m_imgCopie;
    afficherImageLabel();

    afficherMsgDebuterJeu();
}

void CAligne5::afficherMsgDebuterJeu()
{
    m_messagestatusbar = tr( "Pour jouer, menu Jeu : Jouer ou F2" );
    afficherStatusBar();
}

void CAligne5::afficherMsgDebutPartie()
{
    m_messagestatusbar = tr( "Début de la partie" );
    afficherStatusBar();
}

void CAligne5::afficherMsgFinPartie()
{
    m_messagestatusbar = tr( "Fin de la partie..." );
    afficherStatusBar();
}

void CAligne5::afficherMsgJoueurJoue()
{
    m_messagestatusbar = tr( "JOUEUR JOUE..." );
    afficherStatusBar();
}

void CAligne5::afficherMsgOrdiJoue()
{
    m_messagestatusbar = tr( "ORDI JOUE..." );
    afficherStatusBar();
}

void CAligne5::afficherMsgOrdiGagne()
{
    m_messagestatusbar = tr( "ORDI À GAGNÉ!!!" );
    afficherStatusBar();
}

void CAligne5::afficherMsgNbPointJoueur()
{
    QString message;
    message = QString(tr( "POINTS JOUEUR : %1")).arg( m_pcJeu->fournirNbPoint( HUMAIN ) ); /// PARTIE
    m_pLabel0->setText( message );
}

void CAligne5::afficherMsgNbPointOrdi()
{
    QString message;
    message = QString(tr( "POINTS ORDI : %1")).arg( m_pcJeu->fournirNbPoint( ORDI ) ); /// PARTIE
    m_pLabel1->setText( message );
}

void CAligne5::afficherMsgNiveauJeu()
{
    QString message;
    message = QString(tr( "NIVEAU : %1")).arg( m_pcJeu->fournirNiveauJeu() ); /// Niveau
    m_pLabel2->setText( message );
}

void CAligne5::afficherMsgFermerAppli()
{
    m_messagestatusbar = tr( "Fermer le jeu?" );
    afficherStatusBar();
}

void CAligne5::afficherStatusBar()
{
    statusBar()->showMessage( m_messagestatusbar );
}

void CAligne5::afficherImageLabel()
{
    m_pmMemPlateau = QPixmap::fromImage(m_imgMemPlateau);
    m_imageLabel->setPixmap( m_pmMemPlateau );
}

void CAligne5::ecrireMsgFinJeu( const CODEFIN codefin )
{
    QString msg;

    m_imgCopie = m_imgMemPlateau;
    QPainter painter( &m_imgCopie );

    painter.setPen( QColor( 255, 255, 212, 255 ) );
    painter.setFont(QFont("Sans", 72, QFont::Bold));
    painter.drawText( 166, 66, 471, 91, Qt::AlignCenter, tr( "ALIGNE5" ) );

    painter.setFont(QFont("Sans", 22, QFont::Bold));
    painter.drawText( 166, 467, 471, 69, Qt::AlignCenter, tr( "Pour jouer, menu Jeu : Jouer\nou appuyer sur F2" ) );

    switch(codefin)
    {
        case ORDIFIN :
            msg = tr("PARTIE GAGNÉE PAR\nORDINATEUR");
            break;
        case HUMAINFIN :
            msg = tr("PARTIE GAGNÉE PAR\nJOUEUR");
            break;
        default :
            msg = tr("PARTIE À ÉGALITÉ");
    }

    painter.setPen( QColor( 255, 0, 0, 255 ) );
    painter.setFont(QFont("Sans", 30, QFont::Bold));
    painter.drawText( 166, 256, 471, 86, Qt::AlignCenter, msg );

    painter.end();
    m_imgMemPlateau = m_imgCopie;
    afficherImageLabel();

    afficherMsgDebuterJeu();
}
