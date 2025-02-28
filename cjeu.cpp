#include "cjeu.h"

CJeu::CJeu()
{
    /// Crée les deux joueurs +  Initialise vars Joueurs
        m_cOrdi = new COrdi( NOIR, 0 );
        m_cHumain  = new CHumain( BLANC, 0 );

    /// Initialise vars JEU
        QRect r2(X_RECTCASE, Y_RECTCASE, WH_RECT, WH_RECT), r3;
        for(int i = 0; i < HV_NBRECT; i++)
        {
            r3 = r2;
            for(int j = 0; j < HV_NBRECT; j++)
            {
                m_pRectTrous[i][j] = new QRect(r3);
                r3.translate(INCX_RECT, 0);
            }
            r2.translate(0, INCY_RECT);
        }

        m_QuiCommence = HUMAIN;
        m_NiveauJeu = FORT;
        m_PeriodeJeu = ATTENTE;
        m_QuiGagne = PERSONNE;

        initialiserDifficulte( m_NiveauJeu );
        initialiserCaseJeu();
}

CJeu::~CJeu()
{
    for(int i = 0; i < HV_NBRECT; i++)
    {
        for(int j = 0; j < HV_NBRECT; j++)
        {
            delete m_pRectTrous[i][j];
        }
    }
}

CODEFIN CJeu::joueurJoue( NOMJOUEUR nom )
{
    CODEFIN code;
    if( nom == HUMAIN )
    {
        m_cHumain->initialiserCasesDifficulte( m_aCaseJeu, m_aDifficulte );
        if( false == m_cHumain->testerSi1CaseVide() )		return PARTIENULLE;

        bool ftest = false;
        for( int i = 0; i < HV_NBRECT; i++ )
        {
            for( int j = 0; j < HV_NBRECT; j++ )
            {
                ftest = m_pRectTrous[i][j]->contains( m_posClicX, m_posClicY );
                if( true == ftest )
                {
                    int numcase = (i * HV_NBRECT) + j;
                    if( m_aCaseJeu[numcase] == CVIDE )
                    {
                        m_aCaseJeu[numcase] = CHUMAIN;
                        m_rectangle = *m_pRectTrous[i][j];
                        code = m_cHumain->verifierChoix( m_aCaseJeu );
                    }
                    else
                    {
                        code = HUMAINERREUR;
                    }
                    return code;
                }
            }
        }
        code = HUMAINERREUR;
    }
    else
    {
        code = m_cOrdi->ordiJoue( m_aCaseJeu, m_aDifficulte );
        int i, j, index;
        switch( code )
        {
            case ORDIFIN :
                index = m_cOrdi->cherche5emeCase();
                i = index / HV_NBRECT;
                j = index - (i * HV_NBRECT);
                m_rectangle = *m_pRectTrous[i][j];
                break;
            case PARTIENULLE :
                break;
            case CONTINUE :
                index = m_cOrdi->choixMeilleureCase();
                m_aCaseJeu[index] = CORDI;
                i = index / HV_NBRECT;
                j = index - (i * HV_NBRECT);
                m_rectangle = *m_pRectTrous[i][j];
                break;
            default :
                break;
        }
    }
    return code;
}

bool CJeu::fournirMeilleurEmplacement()
{
    bool retour = false;
    int	aDiffFort[SIZEDIFF];
    for(int i = 0; i < SIZEDIFF; i++)
    {
        aDiffFort[i] = DIFF_FORT[i];
    }
    CODEFIN	code = m_cHumain->calculerMeilleurEmplacement( m_aCaseJeu, aDiffFort );
    int i, j, index;
    switch( code )
    {
        case HUMAINFIN :
            index = m_cHumain->cherche5emeCase();
            i = index / HV_NBRECT;
            j = index - (i * HV_NBRECT);
            m_rectangle = *m_pRectTrous[i][j];
            retour = true;
            break;
        case PARTIENULLE :
            retour = false;
            break;
        case CONTINUE :
            index = m_cHumain->choixMeilleureCase();
            i = index / HV_NBRECT;
            j = index - (i * HV_NBRECT);
            m_rectangle = *m_pRectTrous[i][j];
            retour = true;
            break;
        default :
            retour = false;
            break;
    }
    return retour;
}

bool CJeu::testerClicDansCadre()
{
    QRect cadre(X_TROUS, Y_TROUS, W_TROUS, H_TROUS);
    return cadre.contains( m_posClicX, m_posClicY );
}

void CJeu::echangeJeu()
{
    quint8 contenucase;
    for( int i = 0; i < NBRECT; i++ )
    {
        contenucase = m_aCaseJeu[i];
        if( contenucase == CHUMAIN )	m_aCaseJeu[i] = CORDI;
        if( contenucase == CORDI )		m_aCaseJeu[i] = CHUMAIN;
    }
}

QRect CJeu::fournirRectTrou( int i, int j )
{
    QRect	rect = *m_pRectTrous[i][j];
    return rect;
}

COULEURBOULE CJeu::fournirCouleurBoule( NOMJOUEUR nom )
{
    if( nom == HUMAIN )		return ( m_cHumain->fournirCouleurBoule() );
    else	return ( m_cOrdi->fournirCouleurBoule() );
}

int CJeu::fournirNbPoint( NOMJOUEUR nom )
{
    if( nom == HUMAIN )		return ( m_cHumain->fournirNbPoint() );
    else	return ( m_cOrdi->fournirNbPoint() );
}

quint8 CJeu::fournirContenuCase( int numcase )
{
    return m_aCaseJeu[numcase];
}

void CJeu::definirNbPoint( NOMJOUEUR nom, int point )
{
    if( nom == HUMAIN )		m_cHumain->definirNbPoint( point );
    else		m_cOrdi->definirNbPoint( point );
}

void CJeu::definirCouleurBoule( NOMJOUEUR nom, COULEURBOULE couleur )
{
    if( nom == HUMAIN )		m_cHumain->definirCouleurBoule( couleur );
    else		m_cOrdi->definirCouleurBoule( couleur );

    if( m_cHumain->fournirCouleurBoule() == BLANC )		m_cOrdi->definirCouleurBoule( NOIR );
    if( m_cHumain->fournirCouleurBoule() == NOIR )		m_cOrdi->definirCouleurBoule( BLANC );
}

void CJeu::definirPositionClicXY( int x, int y )
{
    m_posClicX = x;
    m_posClicY = y;
}

void CJeu::definirPeriodeJeu( PERIODEJEU quand )
{
    m_PeriodeJeu = quand;
}

void CJeu::definirFlagEchange( bool f )
{
    m_fEchange = f;
}

void CJeu::definirQuiGagne( NOMJOUEUR nom )
{
    m_QuiGagne = nom;
}

void CJeu::definirQuiCommence( NOMJOUEUR nom )
{
    m_QuiCommence = nom;
}

void CJeu::definirNiveauJeu( NIVEAUJEU niveau )
{
    m_NiveauJeu = niveau;
    initialiserDifficulte( m_NiveauJeu );
}

void CJeu::initialiserCaseJeu()
{
    for(int i = 0; i < NBRECT; i++)
    {
        m_aCaseJeu[i] = CVIDE;
    }
}

void CJeu::initialiserDifficulte( const NIVEAUJEU niveaujeu )
{
    switch( niveaujeu )
    {
        case( FAIBLE ):
            for(int i = 0; i < SIZEDIFF; i++)
            {
                m_aDifficulte[i] = DIFF_FAIBLE[i];
            }
            break;
        case( MOYEN ):
            for(int i = 0; i < SIZEDIFF; i++)
            {
                m_aDifficulte[i] = DIFF_MOYEN[i];
            }
            break;
        case( FORT ):
            for(int i = 0; i < SIZEDIFF; i++)
            {
                m_aDifficulte[i] = DIFF_FORT[i];
            }
            break;
    }
}
