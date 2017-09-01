#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);

    static QString getLocalName();
    static void setLocalName(const QString &name);
    static QStringList findQmFiles();
    static QString findQmFile(const QString &localName);

signals:

public slots:
};

#endif // UTILS_H
