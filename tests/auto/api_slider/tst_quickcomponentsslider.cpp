/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <QtDeclarative/qdeclarativecontext.h>
#include <QDeclarativeView>

#include "tst_quickcomponentstest.h"

class tst_quickcomponentsslider : public QObject

{
    Q_OBJECT
private slots:
    void initTestCase();
    void value();
    void stepSize();
    void minimumValue();
    void maximumValue();
    void orientation();
    void updateValueWhileDragging();
    void pressed();

private:
    QObject *componentObject;
};


void tst_quickcomponentsslider::initTestCase()
{
    QString errors;
    componentObject = tst_quickcomponentstest::createComponentFromFile("tst_quickcomponentsslider.qml", &errors);
    QVERIFY2(componentObject, qPrintable(errors));
}

void tst_quickcomponentsslider::value()
{
    // minimum setup to set a value
    componentObject->setProperty("minimumValue", 0.0);
    componentObject->setProperty("maximumValue", 100.0);

    // test if setting/getting value works properly
    QVERIFY(componentObject->setProperty("value", 10.0));
    QCOMPARE(componentObject->property("value").toReal(), 10.0);
}

void tst_quickcomponentsslider::stepSize()
{
    // test if setting/getting stepSize works properly
    QVERIFY(componentObject->setProperty("stepSize", 10.0));
    QCOMPARE(componentObject->property("stepSize").toReal(), 10.0);

    // test if stepSize if working properly (sometimes it may not use
    // the range model and that's why it's a valid test)
    componentObject->setProperty("value", 19.0);
    QCOMPARE(componentObject->property("value").toReal(), 20.0);
}

void tst_quickcomponentsslider::minimumValue()
{
    // test if setting/getting minimumValue works properly
    QVERIFY(componentObject->setProperty("minimumValue", 0.0));
    QCOMPARE(componentObject->property("minimumValue").toReal(), 0.0);

    // small setup to test the set of values below minimum
    componentObject->setProperty("maximumValue", 100.0);
    componentObject->setProperty("value", 50.0);

    // try to set value below minimum (0)
    componentObject->setProperty( "value", -15.0 );

    // the value should be equal to the minimum
    QVERIFY(componentObject->property("value").toReal() ==
            componentObject->property("minimumValue").toReal());
}

void tst_quickcomponentsslider::maximumValue()
{
    // test if setting/getting maximumValue works properly
    QVERIFY(componentObject->setProperty("maximumValue", 200.0));
    QCOMPARE(componentObject->property("maximumValue").toReal(), 200.0);

    // small setup to test the set of values above maximum
    componentObject->setProperty("minimumValue", 0.0);
    componentObject->setProperty("value", 50.0 );

    // try to set a value above the maximum
    componentObject->setProperty("value", 210.0 );

    // the value should be equal to the maximum
    QVERIFY(componentObject->property("value").toReal() ==
            componentObject->property("maximumValue").toReal());
}

void tst_quickcomponentsslider::orientation()
{
    // test if setting/getting the orientation works properly
    QVERIFY(componentObject->setProperty("orientation", Qt::Vertical));
    QCOMPARE(componentObject->property("orientation").toInt(),
             (int)Qt::Vertical);

    QVERIFY(componentObject->setProperty("orientation", Qt::Horizontal));
    QCOMPARE(componentObject->property("orientation").toInt(),
             (int)Qt::Horizontal);

    // try to set a higher value
    componentObject->setProperty("orientation", 3);
    QEXPECT_FAIL("", "Not yet blocked by enum range,"
                 "http://bugreports.qt.nokia.com/browse/QTCOMPONENTS-414",
                 Continue);
    QVERIFY(componentObject->property("orientation").toInt()
            <= (int)Qt::Vertical);

    // try to set a lower value
    componentObject->setProperty("orientation", 0);
    QEXPECT_FAIL("", "Not yet blocked by enum range,"
                 "http://bugreports.qt.nokia.com/browse/QTCOMPONENTS-414",
                 Continue);
    QVERIFY(componentObject->property("orientation").toInt()
            >= (int)Qt::Horizontal);

    // try to set random value
    componentObject->setProperty("orientation", qrand());
    QEXPECT_FAIL("", "Not yet blocked by enum range,"
                 "http://bugreports.qt.nokia.com/browse/QTCOMPONENTS-414",
                 Continue);
    QVERIFY(componentObject->property("orientation").toInt()
            <= (int)Qt::Horizontal
            && componentObject->property("orientation").toInt()
            >= (int)Qt::Vertical);
}

void tst_quickcomponentsslider::pressed()
{
    // as the implementation can change, we can't test the
    // emission of this signal without relying in specific
    // internal members of the slider
}

void tst_quickcomponentsslider::updateValueWhileDragging()
{
    // test if setting/getting stepSize works properly
    QVERIFY(componentObject->setProperty("updateValueWhileDragging", true));
    QCOMPARE(componentObject->property("updateValueWhileDragging").toBool(),
             true);
}

QTEST_MAIN(tst_quickcomponentsslider)

#include "tst_quickcomponentsslider.moc"
