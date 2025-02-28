#include "cordi.h"

COrdi::COrdi()
    : CJoueur()
{

}

COrdi::COrdi( COULEURBOULE couleur, int nbpoint )
 : CJoueur()
{
    m_CouleurBoule = couleur;
    m_NbPoint = nbpoint;
}

COrdi::~COrdi()
{

}

CODEFIN COrdi::ordiJoue( quint8 aCases[], int aDifficulte[] )
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

    m_quiJoue = ORDI;
    razTableauNote();
    bool gagne = false;
    if( gagne == false )	testLigne();
    if( m_quiGagne == ORDI )	gagne = true;
    if( gagne == false )	testColonne();
    if( m_quiGagne == ORDI )	gagne = true;
    if( gagne == false )	testSens1();
    if( m_quiGagne == ORDI )	gagne = true;
    if( gagne == false )	testSens2();
    if( m_quiGagne == ORDI ) 	gagne = true;
    if( gagne == true )
    {
        code = ORDIFIN;
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
