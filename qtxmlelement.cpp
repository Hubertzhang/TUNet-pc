#include "qtxmlelement.h"

QtXMLElement::QtXMLElement(QString raw, QString content, QString tagName, QMap<QString, QString> attributes, QVector<QtXMLElement *>children)
{
    this->raw = raw;
    this->content = content;
    this->tagName = tagName;
    this->attributes = attributes;
    this->children = children;
}

QtXMLElement::~QtXMLElement()
{
    foreach (QtXMLElement *child, children) {
        delete child;
        child = NULL;
    }
}

const QString& QtXMLElement::getRaw() {
    return raw;
}

const QString& QtXMLElement::getContent() {
    return content;
}

const QString& QtXMLElement::getTagName() {
    return tagName;
}

const QMap<QString, QString>& QtXMLElement::getAttributes() {
    return attributes;
}

const QVector<QtXMLElement *>& QtXMLElement::getChildren() {
    return children;
}
