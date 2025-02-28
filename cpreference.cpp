#include "cpreference.h"

CPreference::CPreference(QWidget *parent)
: QDialog(parent), Ui::DlgPreference()
{
    setupUi(this);

    RBtJoueur->setChecked( true );
    RBtOrdi->setChecked( false );

    RBtBlanc->setChecked( true );
    RBtNoir->setChecked( false );

    RBtFaible->setChecked( false );
    RBtMoyen->setChecked( false );
    RBtEleve->setChecked( true );
}

CPreference::CPreference( NOMJOUEUR commence, COULEURBOULE couleur, NIVEAUJEU niveau, QWidget *parent )
: QDialog( parent ), Ui::DlgPreference()
{
    setupUi(this);

    m_commence = commence;
    m_couleur = couleur;
    m_niveau = niveau;
    setValeur( m_commence, m_couleur, m_niveau );
}

CPreference::~CPreference()
{
}

void CPreference::setCommence( NOMJOUEUR commence )
{
    m_commence = commence;
    setValeur( commence, m_couleur, m_niveau );
}
void CPreference::setCouleur( COULEURBOULE couleur )
{
    m_couleur = couleur;
    setValeur( m_commence, couleur, m_niveau );
}
void CPreference::setNiveau( NIVEAUJEU niveau )
{
    m_niveau = niveau;
    setValeur( m_commence, m_couleur, niveau );
}

void CPreference::setValeur( NOMJOUEUR commence, COULEURBOULE couleur, NIVEAUJEU niveau )
{
    switch( commence )
    {
        case( HUMAIN ):
        RBtJoueur->setChecked( true );
        RBtOrdi->setChecked( false );
        break;
        case( ORDI ):
        RBtJoueur->setChecked( false );
        RBtOrdi->setChecked( true );
        break;
        case( PERSONNE ):
        break;
    }

    switch( couleur )
    {
        case( BLANC ):
            RBtBlanc->setChecked( true );
            RBtNoir->setChecked( false );
            break;
        case( NOIR ):
            RBtBlanc->setChecked( false );
            RBtNoir->setChecked( true );
            break;
    }

    switch( niveau )
    {
        case( FAIBLE ):
            RBtFaible->setChecked( true );
            RBtMoyen->setChecked( false );
            RBtEleve->setChecked( false );
            break;
        case( MOYEN ):
            RBtFaible->setChecked( false );
            RBtMoyen->setChecked( true );
            RBtEleve->setChecked( false );
            break;
        case( FORT ):
            RBtFaible->setChecked( false );
            RBtMoyen->setChecked( false );
            RBtEleve->setChecked( true );
            break;
    }
}

void CPreference::reject()
{
  QDialog::reject();
}

void CPreference::accept()
{
    if(true == RBtJoueur->isChecked())	m_commence = HUMAIN;
    if(true == RBtOrdi->isChecked())	m_commence = ORDI;

    if(true == RBtBlanc->isChecked())	m_couleur = BLANC;
    if(true == RBtNoir->isChecked())	m_couleur = NOIR;

    if(true == RBtFaible->isChecked())	m_niveau = FAIBLE;
    if(true == RBtMoyen->isChecked())	m_niveau = MOYEN;
    if(true == RBtEleve->isChecked())	m_niveau = FORT;

  QDialog::accept();
}
