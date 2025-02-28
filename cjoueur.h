#ifndef CJOUEUR_H
#define CJOUEUR_H

#include "enumeration.h"
#include "constante.h"

class CJoueur
{
public:
    CJoueur();
    ~CJoueur();

    void	definirCouleurBoule( COULEURBOULE );
    void	definirNbPoint( int );

    COULEURBOULE	fournirCouleurBoule() const { return m_CouleurBoule; }
    int				fournirNbPoint() const { return m_NbPoint; }

    int		choixMeilleureCase();
    int		cherche5emeCase();

protected:
    COULEURBOULE	m_CouleurBoule;
    int 			m_NbPoint;

    quint8		m_acasejeu[NBRECT];
    int			m_adifficulte[SIZEDIFF];

    int			m_posClicX;
    int			m_posClicY;


    NOMJOUEUR	m_quiGagne, m_quiJoue;

    int 	m_anotecase[NBRECT];
    int 	m_indexcase1, m_indexcase2, m_indexcase3, m_indexcase4, m_indexcase5;
    int 	m_notemaxi;
    int 	m_indexcaseajouer;
    int 	m_index5emecase;
    int 	m_notepourcase;
    int 	m_notepourquintet;

    void	razTableauNote();
    void	testLigne();
    void	testColonne();
    void	testSens1();
    void	testSens2();
    void	noteQuintet( int index, int inc );
    void	compare( int index );
    void	choixNote();
    void	noteCase( int index, int inc );
};

#endif // CJOUEUR_H
