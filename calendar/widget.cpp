#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    InitWidget();
    InitStyle();
}

void Widget::InitWidget(){//初始化界面
    this->resize(430,350);
    this->setObjectName("日历");
    VBoxlayout = new QVBoxLayout;
    Gridlayout = new QGridLayout;

}

Widget::~Widget()
{
    delete ui;
}

