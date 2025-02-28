#include "cjoueur.h"

CJoueur::CJoueur()
{

}

CJoueur::~CJoueur()
{

}

void CJoueur::definirCouleurBoule( COULEURBOULE couleur )
{
    m_CouleurBoule = couleur;
}

void CJoueur::definirNbPoint( int point )
{
    m_NbPoint = point;
}

int CJoueur::choixMeilleureCase()
{
    m_indexcaseajouer = 0;
    for( int i = 0; i < NBRECT; i++ )
    {
        if( m_anotecase[i] == m_notemaxi )
        {
            m_indexcaseajouer = i;
            break;
        }
    }
    return m_indexcaseajouer;
}

int CJoueur::cherche5emeCase()
{
    if( m_acasejeu[m_indexcase1] == CVIDE )			m_index5emecase = m_indexcase1;
    else if( m_acasejeu[m_indexcase2] == CVIDE )	m_index5emecase = m_indexcase2;
    else if( m_acasejeu[m_indexcase3] == CVIDE )	m_index5emecase = m_indexcase3;
    else if( m_acasejeu[m_indexcase4] == CVIDE )	m_index5emecase = m_indexcase4;
    else m_index5emecase = m_indexcase5;
    return m_index5emecase;
}

void CJoueur::razTableauNote()
{
    m_notemaxi = 0;
    m_quiGagne = PERSONNE;
    for(int i = 0; i < NBRECT; i++)
    {
        m_anotecase[i] = 0;
    }
}

void CJoueur::testLigne()
{
    int nbligne, nbquintet, index, inc;
    index = 0;
    inc = 1;
    nbligne = 10;
    while( nbligne > 0 )
    {
        nbquintet = 6;
        while( nbquintet > 0 )
        {
            noteQuintet( index, inc );
            if( m_quiJoue == m_quiGagne )		break;
            noteCase( index, inc );
            nbquintet -= 1;
            if( nbquintet != 0 ) index += 1;
        }
        if( m_quiJoue == m_quiGagne )		break;
        nbligne -= 1;
        if( nbligne != 0 )	index += 5;
    }
}

void CJoueur::testColonne()
{
    int nbcol, nbquintet, index1, index2, inc;
    index2 = 0;
    inc = 10;
    nbcol = 10;
    while( nbcol > 0 )
    {
        index1 = index2;
        nbquintet = 6;
        while( nbquintet > 0 )
        {
            noteQuintet( index1, inc );
            if( m_quiJoue == m_quiGagne )		break;
            noteCase( index1, inc );
            nbquintet -= 1;
            if( nbquintet != 0 )		index1 += 10;
        }
        if( m_quiJoue == m_quiGagne )		break;
        nbcol -= 1;
        if( nbcol != 0 )		index2 += 1;
    }
}

void CJoueur::testSens1()
{
    int nbdiag, nbquintet, nq, index1, index2, inc;
    index2 = 4;
    inc = 9;
    nq = 1;
    nbdiag = 6;
    while( nbdiag > 0 && m_quiJoue != m_quiGagne )
    {
        index1 = index2;
        nbquintet = nq;
        while( nbquintet > 0 )
        {
            noteQuintet( index1, inc );
            if( m_quiJoue == m_quiGagne )		break;
            noteCase( index1, inc );
            nbquintet -= 1;
            index1 += 9;
        }
        if( m_quiJoue == m_quiGagne )		break;
        nbdiag -= 1;
        index2 += 1;
        nq += 1;
    }

    index2 = 19;
    nq = 5;
    nbdiag = 5;
    while( nbdiag > 0 && m_quiJoue != m_quiGagne )
    {
        index1 = index2;
        nbquintet = nq;
        while( nbquintet > 0 )
        {
            noteQuintet( index1, inc );
            if( m_quiJoue == m_quiGagne )	break;
            noteCase( index1, inc );
            nbquintet -= 1;
            index1 += 9;
        }
        if( m_quiJoue == m_quiGagne )		break;
        nbdiag -= 1;
        index2 += 10;
        nq -= 1;
    }
}

void CJoueur::testSens2()
{
    int nbdiag, nbquintet, nq, index1, index2, inc;
    index2 = 0;
    inc = 11;
    nq = 6;
    nbdiag = 6;
    while( nbdiag > 0 && m_quiJoue != m_quiGagne )
    {
        index1 = index2;
        nbquintet = nq;
        while( nbquintet > 0 )
        {
            noteQuintet( index1, inc );
            if( m_quiJoue == m_quiGagne )		break;
            noteCase( index1, inc );
            nbquintet -= 1;
            index1 += 11;
        }
        if( m_quiJoue == m_quiGagne )		break;
        nbdiag -= 1;
        index2 += 10;
        nq -= 1;
    }

    index2 = 1;
    nq = 5;
    nbdiag = 5;
    while( nbdiag > 0 && m_quiJoue != m_quiGagne )
    {
        index1 = index2;
        nbquintet = nq;
        while( nbquintet > 0 )
        {
            noteQuintet( index1, inc );
            if( m_quiJoue == m_quiGagne )		break;
            noteCase( index1, inc );
            nbquintet -= 1;
            index1 += 11;
        }
        if( m_quiJoue == m_quiGagne )		break;
        nbdiag -= 1;
        index2 += 1;
        nq -= 1;
    }
}

void CJoueur::noteQuintet(int index, int inc)
{
    m_notepourquintet = 0;
    m_indexcase1 = index;
    compare( index );
    index += inc;
    m_indexcase2 = index;
    compare( index );
    index += inc;
    m_indexcase3 = index;
    compare( index );
    index += inc;
    m_indexcase4 = index;
    compare( index );
    index += inc;
    m_indexcase5 = index;
    compare( index );
    choixNote();
}

void CJoueur::compare( int index )
{
    switch( m_acasejeu[index] )
    {
        case CVIDE :		m_notepourquintet += 0; break;
        case CHUMAIN :		m_notepourquintet += 6; break;
        case CORDI :		m_notepourquintet += 5; break;
    }
}

void CJoueur::choixNote()
{
    switch( m_notepourquintet )
    {
        case 30:	m_quiGagne = HUMAIN; break;
        case 0:		m_notepourcase = m_adifficulte[0]; break;
        case 6:		m_notepourcase = m_adifficulte[1]; break;
        case 12:	m_notepourcase = m_adifficulte[3]; break;
        case 18:	m_notepourcase = m_adifficulte[5]; break;
        case 24:	m_notepourcase = m_adifficulte[7]; break;
        case 5:		m_notepourcase = m_adifficulte[2]; break;
        case 10:	m_notepourcase = m_adifficulte[4]; break;
        case 15:	m_notepourcase = m_adifficulte[6]; break;
        case 20:	m_quiGagne = ORDI; break;
        default:	m_notepourcase = 0; break;
    }
}

void CJoueur::noteCase(int index, int inc)
{
    int note;
    for( int i = 0; i < 5; i++ )
    {
        if( m_acasejeu[index] == CVIDE )
        {
            note = m_anotecase[index];
            note = note + m_notepourcase;
            m_anotecase[index] = note;
            if( note > m_notemaxi )		m_notemaxi = note;
        }
        index = index + inc;
    }
}
