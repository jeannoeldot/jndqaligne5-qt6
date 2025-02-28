#ifndef CORDI_H
#define CORDI_H

#include "cjoueur.h"
#include "enumeration.h"
#include "constante.h"

class COrdi : public CJoueur
{
public:
    COrdi();
    COrdi( COULEURBOULE, int );
    ~COrdi();

    CODEFIN		ordiJoue( quint8 aCases[], int aDifficulte[] );
};

#endif // CORDI_H
