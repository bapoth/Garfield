/********************************************************************************
** Form generated from reading UI file 'map.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAP_H
#define UI_MAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_map
{
public:
    QTextEdit *AlfPosX;
    QTextEdit *AlfPosY;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QTextEdit *textEdit_3;
    QTextEdit *textEdit_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton;
    ClickableLabel *label_map;
    QLabel *label_alf;
    QLabel *label_destination;
    QTextBrowser *AlfTheta;
    QLabel *label_7;

    void setupUi(QWidget *map)
    {
        if (map->objectName().isEmpty())
            map->setObjectName(QStringLiteral("map"));
        map->setEnabled(true);
        map->resize(1004, 800);
        AlfPosX = new QTextEdit(map);
        AlfPosX->setObjectName(QStringLiteral("AlfPosX"));
        AlfPosX->setGeometry(QRect(850, 70, 101, 31));
        AlfPosY = new QTextEdit(map);
        AlfPosY->setObjectName(QStringLiteral("AlfPosY"));
        AlfPosY->setGeometry(QRect(850, 120, 101, 31));
        label = new QLabel(map);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(850, 40, 91, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(map);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(850, 220, 81, 16));
        label_2->setFont(font);
        label_3 = new QLabel(map);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(830, 80, 16, 16));
        label_4 = new QLabel(map);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(830, 130, 21, 16));
        textEdit_3 = new QTextEdit(map);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));
        textEdit_3->setGeometry(QRect(850, 250, 104, 31));
        textEdit_4 = new QTextEdit(map);
        textEdit_4->setObjectName(QStringLiteral("textEdit_4"));
        textEdit_4->setGeometry(QRect(850, 300, 104, 31));
        label_5 = new QLabel(map);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(820, 260, 21, 16));
        label_6 = new QLabel(map);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(820, 310, 21, 16));
        pushButton = new QPushButton(map);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(850, 350, 101, 41));
        label_map = new ClickableLabel(map);
        label_map->setObjectName(QStringLiteral("label_map"));
        label_map->setEnabled(true);
        label_map->setGeometry(QRect(0, 0, 800, 800));
        label_map->setCursor(QCursor(Qt::PointingHandCursor));
        label_map->setMouseTracking(false);
        label_map->setContextMenuPolicy(Qt::CustomContextMenu);
        label_map->setPixmap(QPixmap(QString::fromUtf8("../../../../../Dokumente/BreezySLAM-master/examples/exp2.pgm")));
        label_map->setScaledContents(true);
        label_alf = new QLabel(map);
        label_alf->setObjectName(QStringLiteral("label_alf"));
        label_alf->setGeometry(QRect(150, 300, 40, 30));
        label_alf->setPixmap(QPixmap(QString::fromUtf8("../../../../../Downloads/auto.png")));
        label_alf->setScaledContents(true);
        label_destination = new QLabel(map);
        label_destination->setObjectName(QStringLiteral("label_destination"));
        label_destination->setGeometry(QRect(440, 280, 71, 51));
        label_destination->setPixmap(QPixmap(QString::fromUtf8("../../../../../Downloads/fahne3.png")));
        label_destination->setScaledContents(true);
        AlfTheta = new QTextBrowser(map);
        AlfTheta->setObjectName(QStringLiteral("AlfTheta"));
        AlfTheta->setGeometry(QRect(850, 170, 101, 31));
        label_7 = new QLabel(map);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(820, 180, 21, 16));

        retranslateUi(map);

        QMetaObject::connectSlotsByName(map);
    } // setupUi

    void retranslateUi(QWidget *map)
    {
        map->setWindowTitle(QApplication::translate("map", "Map", 0));
        label->setText(QApplication::translate("map", "Alf Position:", 0));
        label_2->setText(QApplication::translate("map", "Destination:", 0));
        label_3->setText(QApplication::translate("map", "X:", 0));
        label_4->setText(QApplication::translate("map", "Y:", 0));
        label_5->setText(QApplication::translate("map", "X:", 0));
        label_6->setText(QApplication::translate("map", "Y:", 0));
        pushButton->setText(QApplication::translate("map", "DRIVE!", 0));
        label_map->setText(QString());
        label_alf->setText(QString());
        label_destination->setText(QString());
        label_7->setText(QApplication::translate("map", "dir:", 0));
    } // retranslateUi

};

namespace Ui {
    class map: public Ui_map {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAP_H
