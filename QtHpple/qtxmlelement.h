#ifndef QTXMLELEMENT_H
#define QTXMLELEMENT_H

#include "qthpple_global.h"
#include <QObject>
#include <QMap>
#include <QVector>

class QTHPPLESHARED_EXPORT QtXMLElement : public QObject
{
    Q_OBJECT
    QString raw;
    QString content;
    QString tagName;
    QMap<QString, QString> attributes;
    QVector<QtXMLElement *> children;
public:
//    explicit QtXMLElement(QObject *parent = 0);
    QtXMLElement(QString raw, QString content, QString tagName, QMap<QString, QString> attributes, QVector<QtXMLElement *> children);
    ~QtXMLElement();
    const QString& getRaw();
    const QString& getContent();
    const QString& getTagName();
    const QMap<QString, QString>& getAttributes();
    const QVector<QtXMLElement *>& getChildren();
signals:

public slots:
};

#endif // QTXMLELEMENT_H
