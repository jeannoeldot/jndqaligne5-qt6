#ifndef CPREFERENCE_H
#define CPREFERENCE_H

#include "ui_dlgpreference.h"

#include "enumeration.h"

class CPreference : public QDialog, private Ui::DlgPreference
{
    Q_OBJECT

public:
    explicit CPreference(QWidget *parent = 0);
    explicit CPreference(NOMJOUEUR, COULEURBOULE, NIVEAUJEU, QWidget *parent = 0);
    ~CPreference();

    void	setCommence( NOMJOUEUR );
    void	setCouleur( COULEURBOULE );
    void	setNiveau( NIVEAUJEU );

    NOMJOUEUR		fournitCommence()	const	{ return m_commence; }
    COULEURBOULE	fournitCouleur()	const	{ return m_couleur; }
    NIVEAUJEU		fournitNiveau()     const	{ return m_niveau; }

private:
    void	setValeur( NOMJOUEUR, COULEURBOULE, NIVEAUJEU );

    NOMJOUEUR		m_commence;
    COULEURBOULE	m_couleur;
    NIVEAUJEU		m_niveau;


protected slots:
    virtual void          reject();
    virtual void          accept();
};

#endif // CPREFERENCE_H
