#include "cdaylabel.h"
#include "ccalendar.h"
#include <QVariant>

int Day,Month,Year;

bool CDayLabel::GetSelect(){//获得是否被选中
    return Select;
}

void CDayLabel::SetSelect(bool value){//设置是否被选中
    Select=value;
}

void CDayLabel::SetColor(const int &type)//设置颜色
{
    // 设置控件属性类型
    this->SetSelect(CURRENT_DAY == type);



    // 其他月
    if ((PREV_MONTH_DAY == type) || (NEXT_MONTH_DAY == type)) {
        this->setStyleSheet("background: #ffffff; border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; color: #999999;");
    }
    // 当前月
    else if (CURR_MONTH_DAY == type) {
        this->setStyleSheet("background: #ffffff; border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; color: #000000;");
    }
    // 周末
    else if (WEEKEND_DAY == type) {
        this->setStyleSheet("background: #ffffff; border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; color: #ff0000;");
    }
}

void CDayLabel::ShowDay(int day){//显示日期
    QString text=QString::number(day);
//    Day=day;
    this->setText(text);
}

void CDayLabel::EnterEvent(QEvent *e)//鼠标移入
{
    int nProperty = this->property("type").toInt();
    if (PREV_MONTH_DAY == nProperty || NEXT_MONTH_DAY == nProperty) return;

    this->setStyleSheet("background: #c8b9a6; border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3;");
    QLabel::enterEvent(e);
}

void CDayLabel::LeaveEvent(QEvent *e){//鼠标移出
    int nProperty = this->property("type").toInt();
    if (PREV_MONTH_DAY == nProperty || NEXT_MONTH_DAY == nProperty) return;

    if (Select) {
        this->setStyleSheet("background: #ffffff; border: 1px solid red;");
    }
    else {
        this->setStyleSheet("background: #ffffff; border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3;");
    }
    QLabel::leaveEvent(e);
}
