#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtWidgetsApplication1.h"
#include <QButtonGroup>
#include <qpushbutton.h>
#include <qapplication.h>
#include <qdesktopservices.h>
#include <qurl.h>
#include <qpalette.h>

namespace Ui {
    class QtWidgetsApplication1;
}

class QtWidgetsApplication1 : public QWidget
{
    Q_OBJECT

public:
    explicit QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();

private slots:
    void on_PushButton_clicked();

    void on_PushButton_2_clicked();

private:
    Ui::QtWidgetsApplication1Class ui;
};
