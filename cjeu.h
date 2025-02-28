#ifndef CJEU_H
#define CJEU_H

#include <QRect>

#include "enumeration.h"
#include "constante.h"
#include "chumain.h"
#include "cordi.h"

class CHumain;
class COrdi;
class QRect;

class CJeu
{
public:
    CJeu();
    ~CJeu();

    CODEFIN         joueurJoue( NOMJOUEUR );
    void			echangeJeu();
    void			initialiserCaseJeu();
    bool 			fournirMeilleurEmplacement();
    bool 			testerClicDansCadre();

    QRect			fournirRectTrou( int, int );
    COULEURBOULE	fournirCouleurBoule( NOMJOUEUR );
    quint8			fournirContenuCase( int );
    int				fournirNbPoint( NOMJOUEUR );
    QRect			fournirRectCalcule()	const { return m_rectangle; }
    PERIODEJEU		fournirPeriodeJeu()		const { return m_PeriodeJeu; }
    NOMJOUEUR		fournirQuiCommence()	const { return m_QuiCommence; }
    NIVEAUJEU		fournirNiveauJeu()		const { return m_NiveauJeu; }
    bool			fournirFlagEchange()	const { return m_fEchange; }

    void			definirPeriodeJeu( PERIODEJEU );
    void			definirPositionClicXY( int, int );
    void			definirFlagEchange( bool );
    void			definirQuiGagne( NOMJOUEUR );
    void			definirQuiCommence( NOMJOUEUR );
    void			definirNiveauJeu( NIVEAUJEU );
    void			definirCouleurBoule( NOMJOUEUR, COULEURBOULE );
    void			definirNbPoint( NOMJOUEUR, int );

private:
    COrdi		*m_cOrdi;
    CHumain     *m_cHumain;


/// Vars CASES
    QRect		*m_pRectTrous[HV_NBRECT][HV_NBRECT];

/// Vars JEU
    NOMJOUEUR	m_QuiCommence;
    NIVEAUJEU	m_NiveauJeu;
    PERIODEJEU	m_PeriodeJeu;
    NOMJOUEUR	m_QuiGagne;

    int			m_aDifficulte[SIZEDIFF];
    quint8		m_aCaseJeu[NBRECT];
    int			m_posClicX;
    int			m_posClicY;

    bool 		m_fEchange;

    QRect		m_rectangle;


/// Fonctions générales
    void	initialiserDifficulte( const NIVEAUJEU niveaujeu );
};

#endif // CJEU_H
