#include "chumain.h"

CHumain::CHumain()
    : CJoueur()
{

}

CHumain::CHumain( COULEURBOULE couleur, int nbpoint )
    : CJoueur()
{
    m_CouleurBoule = couleur;
    m_NbPoint = nbpoint;
}

CHumain::~CHumain()
{

}

CODEFIN CHumain::verifierChoix( quint8 aCases[] )
{
    for( int i = 0; i < NBRECT; i++ )
    {
        m_acasejeu[i] = aCases[i];
    }

    CODEFIN code = HUMAINERREUR;

    m_quiJoue = HUMAIN;
    razTableauNote();
    bool gagne = false;
    if( gagne == false )	testLigne();
    if( m_quiGagne == HUMAIN )	gagne = true;
    if( gagne == false )	testColonne();
    if( m_quiGagne == HUMAIN )	gagne = true;
    if( gagne == false )	testSens1();
    if( m_quiGagne == HUMAIN )	gagne = true;
    if( gagne == false )	testSens2();
    if( m_quiGagne == HUMAIN ) 	gagne = true;
    if( gagne == true )
    {
        code = HUMAINFIN;
    }
    else
    {
        code = CONTINUE;
    }
    return code;
}

void CHumain::initialiserCasesDifficulte( quint8 aCases[], int aDifficulte[] )
{
    for( int i = 0; i < NBRECT; i++ )
    {
        m_acasejeu[i] = aCases[i];
    }
    for( int i = 0; i < SIZEDIFF; i++ )
    {
        m_adifficulte[i] = aDifficulte[i];
    }
}

bool CHumain::testerSi1CaseVide()
{
    bool fvide = false;
    for( int i = 0; i < NBRECT; i++)
    {
        if( m_acasejeu[i] == CVIDE )		fvide = true;
    }
    return fvide;
}

CODEFIN CHumain::calculerMeilleurEmplacement( quint8 aCases[], int aDifficulte[] )
{
    CODEFIN code;
    for( int i = 0; i < NBRECT; i++ )
    {
        m_acasejeu[i] = aCases[i];
    }
    for( int i = 0; i < SIZEDIFF; i++ )
    {
        m_adifficulte[i] = aDifficulte[i];
    }

    m_quiJoue = HUMAIN;
    razTableauNote();
    bool gagne = false;
    if( gagne == false )	testLigne();
    if( m_quiGagne == HUMAIN )	gagne = true;
    if( gagne == false )	testColonne();
    if( m_quiGagne == HUMAIN )	gagne = true;
    if( gagne == false )	testSens1();
    if( m_quiGagne == HUMAIN )	gagne = true;
    if( gagne == false )	testSens2();
    if( m_quiGagne == HUMAIN ) gagne = true;
    if( gagne == true )
    {
        code = HUMAINFIN;
    }
    else
    {
        if( m_notemaxi == 0 )	///Partie Nulle
        {
            code = PARTIENULLE;
        }
        else
        {
            code = CONTINUE;
        }
    }

    return code;

}
