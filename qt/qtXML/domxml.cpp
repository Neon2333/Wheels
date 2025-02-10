//domxml.cpp
#include "domxml.h"
#include <QFile>
#include <QDomDocument>
#include <QDomProcessingInstruction>
#include <QDomElement>
#include <QTextStream>
#include <QDateTime>

DomXML::DomXML(){}

void DomXML::createXML(const QString& filePath, const QString& rootName)
{
    //打开文件
    QFile file(filePath);
    //XML存在则返回
    if(true==file.exists())
    {
        qDebug()<<"xml文件已存在..";
        return;
    }
    //只写方式打开,不存在则创建
    bool isOK = file.open(QIODevice::WriteOnly);
    if(!isOK)
    {
        qDebug()<<"createXML 打开xml失败..";
        return;
    }

    //创建xml对象doc
    QDomDocument doc;
    //创建XML头<?xml version="1.0" encoding="UTF-8"?>
    QDomProcessingInstruction ins;
    ins=doc.createProcessingInstruction("xml", "version=\'1.0\' encoding=\'utf-8\'");
    //添加XML头
    doc.appendChild(ins);
    //创建root元素
    QDomElement root = doc.createElement(rootName);	//根节点是什么就写什么rootName
    //添加root元素
    doc.appendChild(root);

    //xml对象保存到磁盘文件
    QTextStream st(&file);	//文本流关联文件对象
    doc.save(st, 4);	//4表示缩进为4个字符
    file.close();		//关闭文件
}

std::unique_ptr<QDomDocument> DomXML::readXML(const QString& filePath)
{
    QFile file(filePath);
    if(!file.exists())
    {
        return nullptr;
    }

    bool isOK = file.open(QIODevice::ReadOnly);	//只读打开
    if(!isOK)
    {
        qDebug()<<"readXML 打开xml失败..";
        return nullptr;
    }

    //读取磁盘xml文件内容到内存xml对象doc
    std::unique_ptr<QDomDocument> docPtr(new QDomDocument);
    isOK = static_cast<bool>(docPtr->setContent(&file));
    if(!isOK)
    {
        qDebug()<<"读取xml文件内容到内存失败..";
        return nullptr;
    }

    return docPtr;
    file.close();
}


void DomXML::saveXML(const QString& filePath, QDomDocument& xml)
{
    QFile file(filePath);
    bool isOK = file.open(QIODevice::WriteOnly);    //只写方式打开,不存在则创建
    if(!isOK)
    {
        qDebug()<<"saveXML 打开xml失败..";
    }
    QTextStream st(&file);
    xml.save(st, 4);
    file.close();
}

QDomElement DomXML::getRoot(QDomDocument& xml)
{
    return xml.documentElement();
}

QDomElement DomXML::getChildNode(QDomElement parentNode, QString childName, QStringList childAttrs, QStringList childAttrValues)
{
    if(childAttrs.count() != childAttrValues.count())
    {
        qDebug()<<"count parameters not match..";
        return QDomElement();
    }

    QDomNodeList childs = parentNode.elementsByTagName(childName);
    for(int i=0;i<childs.count();i++)
    {
        QDomElement child = childs.at(i).toElement();
        for(int j=0;j<childAttrs.count();j++)
        {
            if(child.attribute(childAttrs.at(j)) != childAttrValues.at(j))
            {
                break;
            }
        }
        return child;
    }
    return QDomElement();
}

// void DomXML::appendNodeRoot(const QString& filePath, QStringList nodeNames, QStringList attrNames, QStringList attrVals)
// {
//     if(nodeNames.count()!=attrNames.count()&&attrNames.count()!=attrVals.count())	return;

//     //读取磁盘xml文件内容到内存xml对象docPtr
//     QDomDocument* docPtr = readXML(filePath);
//     //获取根元素
//     QDomElement root = docPtr->documentElement();
//     if(!root.hasChildNodes())
//     {
//         //根元素没有子元素则直接创建子节点并添加
//         for(int i=0;i<nodeNames.count();i++)
//         {
//             //创建Date元素节点
//             QDomElement nodeEle = docPtr->createElement(nodeNames.at(i));
//             //创建属性。设置属性值，date="2024-12-21"
//             QDomAttr nodeAttr = docPtr->createAttribute(attrNames.at(i));
//             nodeAttr.setNodeValue(attrVals.at(i));
//             //将属性添加到Date元素
//             nodeEle.setAttributeNode(nodeAttr);
//             //把Date元素节点添加到root节点
//             root.appendChild(nodeEle);
//         }
//     }
//     else
//     {
//         //根元素有子元素则找到最后一个子节点，在它之后添加新创建的子节点
//         QDomElement lastNode = root.lastChildElement();
//     }
// }

QList<QDomElement> DomXML::appendNode(QDomDocument& xml, QDomElement& parentNode, QStringList& nodeNames, QStringList& attrNames, QStringList& attrVals)
{
    if(nodeNames.count()!=attrNames.count() && attrNames.count()!=attrVals.count())
    {
        qDebug()<<"count parameters not match..";
        return QList<QDomElement>();
    }

    QList<QDomElement> nodeElesAdded;

    for(int i=0;i<nodeNames.count();i++)
    {
        //创建元素节点
        QDomElement nodeEle = xml.createElement(nodeNames.at(i));
        //添加属性到元素节点。先添加的属性排在后面。
        for(int j=attrNames.count()-1;j>=0;j--)
        {
            //创建属性。设置属性值
            QDomAttr nodeAttr = xml.createAttribute(attrNames.at(j));
            nodeAttr.setNodeValue(attrVals.at(j));
            //将属性添加到Date元素
            nodeEle.setAttributeNode(nodeAttr);
        }
        //把Date元素节点添加到root节点
        parentNode.appendChild(nodeEle);
        nodeElesAdded.append(nodeEle);
    }

    return nodeElesAdded;
}

void DomXML::writeContent(QDomDocument& xml, QDomElement& node, QStringList& contentNodeNames, QStringList& contents)
{
    if(contentNodeNames.count()!=contents.count())
    {
        qDebug()<<"count parameters not match..";
        return;
    }

    for(int i=0;i<contents.count();i++)
    {
        QDomElement nodeEle = xml.createElement(contentNodeNames.at(i));
        QDomText contentNode = xml.createTextNode(contents.at(i));
        nodeEle.appendChild(contentNode);
        node.appendChild(nodeEle);
    }
}

void DomXML::getContent(QDomElement &node, QStringList &contentNodeNames, QStringList &contents)
{
    QDomNodeList childs = node.childNodes();

    for(int i=0;i<childs.count();i++)
    {
        QDomElement child = childs.at(i).toElement();
        contentNodeNames.append(child.nodeName());
        contents.append(child.text());
    }
}
