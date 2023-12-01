/********************************************************************************
** Form generated from reading UI file 'QtWidgetsApplication1.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSAPPLICATION1_H
#define UI_QTWIDGETSAPPLICATION1_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplication1Class
{
public:
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QTextBrowser *textBrowser;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *IPlineEdit;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QRadioButton *radioButton1;
    QRadioButton *radioButton2;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *FilelineEdit;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QRadioButton *radioButton3;
    QRadioButton *radioButton4;
    QPushButton *pushButton_2;

    void setupUi(QWidget *QtWidgetsApplication1Class)
    {
        if (QtWidgetsApplication1Class->objectName().isEmpty())
            QtWidgetsApplication1Class->setObjectName(QString::fromUtf8("QtWidgetsApplication1Class"));
        QtWidgetsApplication1Class->resize(800, 400);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        QtWidgetsApplication1Class->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("D:/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        QtWidgetsApplication1Class->setWindowIcon(icon);
        QtWidgetsApplication1Class->setAutoFillBackground(false);
        QtWidgetsApplication1Class->setStyleSheet(QString::fromUtf8("#QtWidgetsApplication1Class{background-color:rgb(240, 240, 240)}\n"
""));
        pushButton = new QPushButton(QtWidgetsApplication1Class);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(520, 10, 181, 91));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        pushButton->setFont(font1);
        layoutWidget = new QWidget(QtWidgetsApplication1Class);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 170, 741, 211));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        label_5->setFont(font2);

        verticalLayout->addWidget(label_5);

        textBrowser = new QTextBrowser(layoutWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setFont(font);

        verticalLayout->addWidget(textBrowser);

        layoutWidget1 = new QWidget(QtWidgetsApplication1Class);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 10, 341, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font2);

        horizontalLayout->addWidget(label);

        IPlineEdit = new QLineEdit(layoutWidget1);
        IPlineEdit->setObjectName(QString::fromUtf8("IPlineEdit"));
        IPlineEdit->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(IPlineEdit->sizePolicy().hasHeightForWidth());
        IPlineEdit->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(IPlineEdit);

        layoutWidget2 = new QWidget(QtWidgetsApplication1Class);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 50, 341, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font2);

        horizontalLayout_2->addWidget(label_2);

        radioButton1 = new QRadioButton(layoutWidget2);
        radioButton1->setObjectName(QString::fromUtf8("radioButton1"));
        radioButton1->setFont(font);

        horizontalLayout_2->addWidget(radioButton1);

        radioButton2 = new QRadioButton(layoutWidget2);
        radioButton2->setObjectName(QString::fromUtf8("radioButton2"));
        radioButton2->setFont(font);

        horizontalLayout_2->addWidget(radioButton2);

        layoutWidget3 = new QWidget(QtWidgetsApplication1Class);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(30, 90, 341, 31));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font2);

        horizontalLayout_3->addWidget(label_3);

        FilelineEdit = new QLineEdit(layoutWidget3);
        FilelineEdit->setObjectName(QString::fromUtf8("FilelineEdit"));
        sizePolicy.setHeightForWidth(FilelineEdit->sizePolicy().hasHeightForWidth());
        FilelineEdit->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(FilelineEdit);

        layoutWidget4 = new QWidget(QtWidgetsApplication1Class);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(30, 130, 341, 31));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);

        horizontalLayout_4->addWidget(label_4);

        radioButton3 = new QRadioButton(layoutWidget4);
        radioButton3->setObjectName(QString::fromUtf8("radioButton3"));
        radioButton3->setFont(font);

        horizontalLayout_4->addWidget(radioButton3);

        radioButton4 = new QRadioButton(layoutWidget4);
        radioButton4->setObjectName(QString::fromUtf8("radioButton4"));
        radioButton4->setFont(font);

        horizontalLayout_4->addWidget(radioButton4);

        pushButton_2 = new QPushButton(QtWidgetsApplication1Class);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(520, 110, 181, 41));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        pushButton_2->setFont(font3);

        retranslateUi(QtWidgetsApplication1Class);

        QMetaObject::connectSlotsByName(QtWidgetsApplication1Class);
    } // setupUi

    void retranslateUi(QWidget *QtWidgetsApplication1Class)
    {
        QtWidgetsApplication1Class->setWindowTitle(QApplication::translate("QtWidgetsApplication1Class", "TFTP Client by Tora416", nullptr));
        pushButton->setText(QApplication::translate("QtWidgetsApplication1Class", "Execute", nullptr));
        label_5->setText(QApplication::translate("QtWidgetsApplication1Class", "Process\357\274\232", nullptr));
        label->setText(QApplication::translate("QtWidgetsApplication1Class", "Sever IP\357\274\232", nullptr));
        label_2->setText(QApplication::translate("QtWidgetsApplication1Class", "Operation\357\274\232", nullptr));
        radioButton1->setText(QApplication::translate("QtWidgetsApplication1Class", "Download", nullptr));
        radioButton2->setText(QApplication::translate("QtWidgetsApplication1Class", "Upload", nullptr));
        label_3->setText(QApplication::translate("QtWidgetsApplication1Class", "Filename\357\274\232", nullptr));
        label_4->setText(QApplication::translate("QtWidgetsApplication1Class", "Mode\357\274\232", nullptr));
        radioButton3->setText(QApplication::translate("QtWidgetsApplication1Class", "netascii", nullptr));
        radioButton4->setText(QApplication::translate("QtWidgetsApplication1Class", "octet", nullptr));
        pushButton_2->setText(QApplication::translate("QtWidgetsApplication1Class", "File location", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsApplication1Class: public Ui_QtWidgetsApplication1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSAPPLICATION1_H
