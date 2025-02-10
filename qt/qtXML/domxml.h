//domxml.h
#ifndef DOMXML_H
#define DOMXML_H
#include <QString>
#include <QDomDocument>

class DomXML
{
public:
    DomXML();

    /// <summary>
    /// 根据根节点名，创建空白XML文件
    /// </summary>
    /// <param name="filePath">创建xml的路径
    /// <param name="rootName">创建xml的根节点名
    static void createXML(const QString& filePath, const QString& rootName);

    //从磁盘XML文件读取到内存xml对象
    static std::unique_ptr<QDomDocument> readXML(const QString& filePath);
    //将xml对象保存到磁盘文件
    static void saveXML(const QString& filePath, QDomDocument& xml);

    //从xml对象获取根节点
    static QDomElement getRoot(QDomDocument& xml);

    //根据节点名+属性值获取父节点下某个指定节点
    static QDomElement getChildNode(QDomElement parentNode, QString childName, QStringList childAttrs, QStringList childAttrValues);

    //向根节点中添加子节点
    // static void appendNodeRoot(const QString& filePath, QStringList nodeNames, QStringList attrNames, QStringList attrVals);

    /// <summary>
    /// 向节点node中子节点
    /// </summary>
    /// <param name="node">待添加子节点的父节点
    /// <param name="nodeNames">添加的子节点名
    /// <param name="attrNames">子节点属性名</param>
    /// <param name="attrVals">子节点属性值</param>
    static QList<QDomElement> appendNode(QDomDocument& xml, QDomElement& parentNode, QStringList& nodeNames, QStringList& attrNames, QStringList& attrVals);

    /// <summary>
    /// 向节点node中添加内容
    /// </summary>
    /// <param name="node">添加内容节点的父节点</param>
    /// <param name="contentNodeNames">内容节点名</param>
    /// <param name="contents">内容</param>
    static void writeContent(QDomDocument& xml, QDomElement& node, QStringList& contentNodeNames, QStringList& contents);

    //XML解析。获取某个节点下的内容。
    static void getContent(QDomElement& node, QStringList& contentNodeNames, QStringList& contents);
};

#endif
