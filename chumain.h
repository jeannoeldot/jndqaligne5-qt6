#ifndef CHUMAIN_H
#define CHUMAIN_H

#include "cjoueur.h"
#include "enumeration.h"
#include "constante.h"


class CHumain : public CJoueur
{
public:
    CHumain();
    CHumain( COULEURBOULE, int );
    ~CHumain();

    CODEFIN     verifierChoix( quint8 aCases[] );
    void		initialiserCasesDifficulte( quint8 aCases[], int aDifficulte[] );
    bool		testerSi1CaseVide();
    CODEFIN     calculerMeilleurEmplacement( quint8 aCases[], int aDifficulte[] );
};

#endif // CHUMAIN_H
