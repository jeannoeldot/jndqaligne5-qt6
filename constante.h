#ifndef CONSTANTE
#define CONSTANTE

#include <QString>

const QString VERSION_PROG = "0.6.0";
const QString NOM_PROG = "Aligne5";
const QString ORGANISATION = "JND-Software";
const QString COPYRIGHT = "© 2007-2025 JND-Software Inc";


const int W_PLATEAU = 800;
const int H_PLATEAU = 600;

const int X_DEBUTJEU = 147;
const int Y_DEBUTJEU = 47;
const int W_DEBUTJEU = 506;
const int H_DEBUTJEU = 506;

const int X_FINJEU = 147;
const int Y_FINJEU = 47;
const int W_FINJEU = 506;
const int H_FINJEU = 506;

const int W_DESSINBOULE = 87;
const int H_DESSINBOULE = 40;
const int INCX_BOULE = 46;
const int WH_BOULE = 40;


const int X_TROUS = 166;
const int Y_TROUS = 66;
const int W_TROUS = 471;
const int H_TROUS = 471;


const int TEMPOFORT = 500;				// en millisecondes
const int TEMPOMOYEN = 1000;
const int TEMPOFAIBLE = 1500;
const int NBFOISFORT = 3;				// pour clignotement
const int NBFOISMOYEN = 5;
const int NBFOISFAIBLE = 7;
const int TEMPSHOW = 200;
const int TEMPHIDE = 100;


const int X_RECTCASE = 172;
const int Y_RECTCASE = 72;
const int WH_RECT = 40;
const int INCX_RECT = 46;
const int INCY_RECT = 46;

const int HV_NBRECT = 10;
const int NBRECT = 100;


const int SIZEDIFF = 8;

const int DIFF_FAIBLE[SIZEDIFF] = {1,2,3,4,5,8,20,50};
const int DIFF_MOYEN[SIZEDIFF] = {1,2,4,6,10,20,40,100};
const int DIFF_FORT[SIZEDIFF] = {1,2,10,20,100,200,1000,5000};


#endif // CONSTANTE

