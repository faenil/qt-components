/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project on Qt Labs.
**
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions contained
** in the Technology Preview License Agreement accompanying this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
****************************************************************************/

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <QDeclarativeView>
#include <QDeclarativeItem>

#include "tst_quickcomponentstest.h"

class tst_tumblerdialog : public QObject

{
    Q_OBJECT
private slots:
    void initTestCase();
    void basic();
    void selected();
    void property_enabled();
    void property_items();

private:
    QObject *componentObject;
};

void tst_tumblerdialog::initTestCase()
{
    QString errors;
    componentObject = tst_quickcomponentstest::createComponentFromFile("tst_tumblerdialog.qml", &errors);
    QVERIFY2(componentObject, qPrintable(errors));
}

void tst_tumblerdialog::basic()
{
    QObject *child;
    const QObjectList children = componentObject->children();
    // verify there is 4 children
    QCOMPARE(children.size(), 4);
    for (int i = 0; i < children.size(); ++i) {
        child = children.at(i);
        if (child->objectName().contains("td")) {
            // verify aColumn's titleText has default sting "titleText"
            QVERIFY2(child->property("titleText").isValid(), "Error, TumblerDialog's child must have title property");
            QCOMPARE(child->property("titleText").toString(), QString("titleText"));
            // verify accepted button
            QVERIFY2(child->property("acceptButtonText").isValid(), "Error, TumblerDialog's child must have acceptButtonText property");
            QCOMPARE(child->property("acceptButtonText").toString(), QString("accept"));
            // verify rejected button
            QVERIFY2(child->property("rejectButtonText").isValid(), "Error, TumblerDialog's child must have rejectButtonText property");
            QCOMPARE(child->property("rejectButtonText").toString(), QString("reject"));
        }
    }
}

void tst_tumblerdialog::selected()
{
    QObject *child;
    const QObjectList children = componentObject->children();
    // verify there is 4 children
    QCOMPARE(children.size(), 4);
    for (int i = 0; i < children.size(); ++i) {
        child = children.at(i);
        if (child->objectName().contains("aColumn")) {
            // verify aColumn's selectedIndex has default value of 0
            QVERIFY2(child->property("selectedIndex").isValid(), "Error, TumblerColumn's child must have selectedIndex property");
            QCOMPARE(child->property("selectedIndex").toInt(), 0);
            child->setProperty("selectedIndex", 2);
            QCOMPARE(child->property("selectedIndex").toInt(), 2);
        }
        if (child->objectName().contains("bColumn")) {
            // verify bColumn's selectedIndex has default value of 0
            QVERIFY2(child->property("selectedIndex").isValid(), "Error, TumblerColumn's child must have selectedIndex property");
            QCOMPARE(child->property("selectedIndex").toInt(), 0);
            child->setProperty("selectedIndex", 4);
            QCOMPARE(child->property("selectedIndex").toInt(), 4);
        }
    }
}

void tst_tumblerdialog::property_enabled()
{
    QObject *child;
    const QObjectList children = componentObject->children();
    // verify there is 4 children
    QCOMPARE(children.size(), 4);
    for (int i = 0; i < children.size(); ++i) {
        child = children.at(i);
        if (child->objectName().contains("aColumn")) {
            QVERIFY2(child->property("enabled").isValid(), "Error, TumblerColumn's child must have enabled property");
            // verify aColumn's enabled has default value true
            QCOMPARE(child->property("enabled").toBool(), true);
            child->setProperty("enabled", false);
            QCOMPARE(child->property("enabled").toBool(), false);
        }
        if (child->objectName().contains("bColumn")) {
            // verify bColumn's enabled has default value false
            QVERIFY2(child->property("enabled").isValid(), "Error, TumblerColumn's child must have enabled property");
            QCOMPARE(child->property("enabled").toBool(), false);
            child->setProperty("enabled", true);
            QCOMPARE(child->property("enabled").toBool(), true);
        }
    }
}

void tst_tumblerdialog::property_items()
{
    QObject *child;
    int modelSize;
    const QObjectList children = componentObject->children();
    // verify there is 4 children
    QCOMPARE(children.size(), 4);
    for (int i = 0; i < children.size(); ++i) {
        child = children.at(i);
        if (child->objectName().contains("model")) {
            modelSize = child->property("count").toInt();
            // verify there is 5 elements
            QCOMPARE(modelSize, 5);
        }
        if (child->objectName().contains("Column")) {
            QVariant var = child->property("items");
            QVERIFY2(child->property("items").isValid(), "Error, TumblerColumn's child must have items property");
            // TODO: The type of "items" is currently "ListModel" and conversion from QVariant
            //       to QObject does not work for that properly.
            //QObject *listmodel = var.value<QObject*>();
            //QVERIFY(listmodel);
            //QCOMPARE(listmodel->property("count").toInt(), 5);
        }
    }
}

QTEST_MAIN(tst_tumblerdialog)

#include "tst_tumblerdialog.moc"
