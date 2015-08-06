#include "qthpple.h"
#include "qtxpathquery.h"

QtHpple::QtHpple(QByteArray *data, bool isDataXML) {
    this->data = data;
    this->isXML = isDataXML;
}

QVector<QtXMLElement *> QtHpple::search(QString XPathQuery) {
      if (isXML) {
        return PerformXMLXPathQuery(data, XPathQuery);
      } else {
        return PerformHTMLXPathQuery(data, XPathQuery);
      }
}

QtXMLElement * QtHpple::peekAtSearch(QString XPathQuery) {
    QVector<QtXMLElement *> elements = this->search(XPathQuery);
      if (elements.count() >= 1) {
        return elements[0];
      }
    return NULL;
}
