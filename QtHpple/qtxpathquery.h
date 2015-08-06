#ifndef QTXPATHQUERY_H
#define QTXPATHQUERY_H

#include "qtxmlelement.h"
QVector<QtXMLElement *> PerformXMLXPathQuery(QByteArray *document, QString query);
QVector<QtXMLElement *> PerformHTMLXPathQuery(QByteArray *document, QString query);
#endif // QTXPATHQUERY_H
