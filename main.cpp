#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QSettings>
#include <QTranslator>

#include "utils.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // set locale
    QLocale locale(Utils::getLocalName());
    QLocale::setDefault(locale);

    qDebug() << Utils::getLocalName();

    // set translator
    QTranslator translator;
    QStringList qmFiles = Utils::findQmFiles();
    QString languageCode = locale.name().left(2);
    qDebug() << qmFiles << languageCode;
    foreach (const QString &qmFile, qmFiles) {
        QFileInfo info(qmFile);
        if (info.baseName() == QString("%1_%2").arg(a.applicationName(), languageCode)) {
            qDebug() << qmFile;
            translator.load(qmFile);
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.show();

    return a.exec();
}
