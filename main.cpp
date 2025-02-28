#include "caligne5.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load ("qt_" + QLocale::system().name(), QLibraryInfo::path(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator appTranslator;
    appTranslator.load( "jndqaligne5_" + QLocale::system().name(), ":/translations");
    app.installTranslator( &appTranslator );

    CAligne5 w;
    w.show();

    return app.exec();
}
