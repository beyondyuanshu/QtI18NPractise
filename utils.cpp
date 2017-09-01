#include "utils.h"

#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QStringList>
#include <QMutableStringListIterator>
#include <QSettings>
#include <QLocale>

Utils::Utils(QObject *parent) : QObject(parent)
{

}

QString Utils::getLocalName()
{
    QString localDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QDir dir(localDataLocation);
    dir.mkpath(localDataLocation);

    QSettings settings(QString("%1/%2.ini").arg(localDataLocation, qApp->applicationName()),
                       QSettings::IniFormat);

    QString localName = settings.value("locale").toString();
    if (localName.isEmpty()) {
        localName = QLocale::system().name();
        settings.setValue("locale", localName);
    }

    return localName;
}

void Utils::setLocalName(const QString &name)
{
    QString localDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QDir dir(localDataLocation);
    dir.mkpath(localDataLocation);

    QSettings settings(QString("%1/%2.ini").arg(localDataLocation, qApp->applicationName()),
                       QSettings::IniFormat);
    settings.setValue("locale", name);
}

QStringList Utils::findQmFiles()
{
    QDir dir(":/translations");
    QStringList fileNames = dir.entryList(QStringList("*.qm"), QDir::Files,
                                          QDir::Name);
    QMutableStringListIterator i(fileNames);
    while (i.hasNext()) {
        i.next();
        i.setValue(dir.filePath(i.value()));
    }
    return fileNames;
}

QString Utils::findQmFile(const QString &localName)
{
    QStringList qmFiles = Utils::findQmFiles();
    QString languageCode = localName.left(2);
    foreach (const QString &qmFile, qmFiles) {
        QFileInfo info(qmFile);
        if (info.baseName() == QString("%1_%2").arg(qApp->applicationName(), languageCode)) {
            return qmFile;
        }
    }

    return QString();
}
