#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ASD.h"

class ASD : public QMainWindow
{
    Q_OBJECT

public:
    ASD(QWidget *parent = nullptr);
    ~ASD();

private:
    Ui::ASDClass ui;
};
