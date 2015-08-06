#include "qtxpathquery.h"
#include <libxml/tree.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <QtCore>
#include <QMap>

//NSDictionary *DictionaryForNode(xmlNodePtr currentNode, NSMutableDictionary *parentResult,BOOL parentContent);
//NSArray *PerformXPathQuery(xmlDocPtr doc, NSString *query);

QtXMLElement* ElementForNode(xmlNodePtr currentNode)
{
    //  NSMutableDictionary *resultForNode = [NSMutableDictionary dictionary];
    QString tagName;
    QString content;
//    QMap<QString, QString> resultForNode;

    if (currentNode->name)
    {
        tagName = QString::fromUtf8((const char *)currentNode->name);
    }

    if (currentNode->content && currentNode->content != (xmlChar *)-1)
    {
        content = QString::fromUtf8((const char *)currentNode->content);
    }

    xmlAttr *attribute = currentNode->properties;
    QMap<QString, QString>attributeMap;
    while(attribute && attribute->name && attribute->children)
    {
      xmlChar* value = xmlNodeListGetString(currentNode->doc, attribute->children, 1);
      //do something with value
      attributeMap[QString((const char*)attribute->name)] = QString::fromUtf8((const char*)value);

      xmlFree(value);
      attribute = attribute->next;
    }

    xmlNodePtr childNode = currentNode->children;
    QVector<QtXMLElement *> children;
    if (childNode)
    {
        while (childNode)
        {
            children.append(ElementForNode(childNode));
            childNode = childNode->next;
        }
    }

    xmlBufferPtr buffer = xmlBufferCreate();
    xmlNodeDump(buffer, currentNode->doc, currentNode, 0, 0);

    QString raw = QString::fromUtf8((const char *)buffer->content);

    xmlBufferFree(buffer);

    return new QtXMLElement(raw, content, tagName, attributeMap, children);
}

QVector<QtXMLElement *> PerformXPathQuery(xmlDocPtr doc, QString query)
{
    QVector<QtXMLElement *> result;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;

    /* Create xpath evaluation context */
    xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL)
    {
//        NSLog(@"Unable to create XPath context.");
        throw "Unable to create XPath context.";
//        return nil;
    }

    /* Evaluate xpath expression */
    xpathObj = xmlXPathEvalExpression((xmlChar *)query.toLatin1().data(), xpathCtx);
    if(xpathObj == NULL) {
//        NSLog(@"Unable to evaluate XPath.");
        xmlXPathFreeContext(xpathCtx);
        throw "Unable to evaluate XPath.";
        return result;
    }

    xmlNodeSetPtr nodes = xpathObj->nodesetval;
    if (!nodes)
    {
//        NSLog(@"Nodes was nil.");
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtx);
        throw "Nodes was nil.";
        return result;
    }

    for (int i = 0; i < nodes->nodeNr; i++)
    {
        result.append(ElementForNode(nodes->nodeTab[i]));
    }

    /* Cleanup */
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);

    return result;
}

QVector<QtXMLElement *> PerformHTMLXPathQuery(QByteArray *document, QString query)
{
    xmlDocPtr doc;

    /* Load XML document */
    doc = htmlReadMemory(document->data(), document->length(), "", "UTF8", HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR);

    if (doc == NULL)
    {
        throw "Unable to parse.";
        //      NSLog(@"Unable to parse.");
//        return result;
    }

    QVector<QtXMLElement *> result = PerformXPathQuery(doc, query);
    xmlFreeDoc(doc);

    return result;
}

QVector<QtXMLElement *> PerformXMLXPathQuery(QByteArray *document, QString query)
{
    xmlDocPtr doc;

    /* Load XML document */
    doc = htmlReadMemory(document->data(), document->length(), "", "UTF8", XML_PARSE_RECOVER);

    if (doc == NULL)
    {
        throw "Unable to parse.";
        //      NSLog(@"Unable to parse.");
//        return result;
    }

    QVector<QtXMLElement *> result = PerformXPathQuery(doc, query);
    xmlFreeDoc(doc);

    return result;
}

