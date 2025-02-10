#include "mainwindow.h"
#include <QApplication>
#include "domxml.h"
#include <QStringList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QString path = R"(C:\Users\Administrator\Desktop\test.xml)";//C++11原始字面量
    DomXML::createXML(path, "info");
    std::unique_ptr<QDomDocument> xml = DomXML::readXML(path);
    QDomElement root = DomXML::getRoot(*(xml.get()));

    QStringList nodes1;
    nodes1 << "Date";
    QStringList attrs1;
    attrs1 << "date" << "iii";
    QStringList attrvals1;
    attrvals1 << "2024-12-21" << "hh";
    DomXML::appendNode(*(xml->get()), root, nodes1, attrs1, attrvals1);

    QStringList attrvals2;
    attrvals2 << "2024-12-23" << "ww";
    DomXML::appendNode(*(xml->get()), root, nodes1, attrs1, attrvals2);

    QDomElement dateNode = DomXML::getChildNode(root, "Date", QStringList()<<"date", QStringList()<<"2024-12-21");

    QStringList nodes3;
    nodes3 << "Time";
    QStringList attrs3;
    attrs3 << "time";
    QStringList attrvals3;
    attrvals3 << "20:47:30";
    QList<QDomElement> timeNodes = DomXML::appendNode(*(xml->get()), dateNode, nodes3, attrs3, attrvals3);


    // QDomElement timeNode = DomXML::getChildNode(dateNode, "Time", QStringList()<< "time", QStringList()<< "20:47:30");
    // DomXML::writeContent(*xml, timeNode, QStringList()<<"name"<<"sex"<<"score", QStringList()<<"aaa"<<"male"<<"100");
    QDomElement timeNode = timeNodes.at(0);
    DomXML::writeContent(*(xml->get()), timeNode, QStringList()<<"name"<<"sex"<<"score", QStringList()<<"aaa"<<"male"<<"100");

    DomXML::saveXML(path, *(xml->get()));


    return a.exec();
}
