#ifndef QTHPPLE_H
#define QTHPPLE_H

#include "qthpple_global.h"
#include "qtxmlelement.h"

class QTHPPLESHARED_EXPORT QtHpple
{
    QByteArray *data;
    bool isXML;
public:
    QtHpple(QByteArray *data, bool isDataXML);

    QVector<QtXMLElement *> search(QString XPathQuery);
    QtXMLElement * peekAtSearch(QString XPathQuery);

};

#endif // QTHPPLE_H
