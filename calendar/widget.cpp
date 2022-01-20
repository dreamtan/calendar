#include "widget.h"
#include "ui_widget.h"
#include "cdaylabel.h"
#include <QDate>
#include <QString>
#include "ccalendar.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Year=QDate::currentDate().year();
    Month=QDate::currentDate().month();
    Day=QDate::currentDate().day();
    InitWidget();
    InitStyle();
    InitDate();
//    LabelShowDay = new QLabel();
//    LabelShowWeek = new QLabel();
//    LabelShowYear = new QLabel();
//    LabelShowToday= new QLabel();
}

void Widget::InitWidget(){//初始化界面
    this->resize(430,350);
    this->setObjectName("日历");
    VBoxlayout = new QVBoxLayout();
    Gridlayout = new QGridLayout();
    VBoxlayout ->setContentsMargins(2,2,2,2);
    VBoxlayout->setSpacing(0);
    CalendarTitle= new QWidget();
    BtnPrevMonth =new QPushButton("上月",CalendarTitle);
    BtnNextMonth = new QPushButton("下月",CalendarTitle);
    LabelTitle = new QLabel(CalendarTitle);
    HBoxlayout = new QHBoxLayout(CalendarTitle);

    Year= QDate::currentDate().year();
    Month=QDate::currentDate().month();
    Day=QDate::currentDate().day();

    LabelTitle->setText(tr("%1 年 %2 月").arg(Year, 2, 10, QChar('0')).arg(Month, 2, 10, QChar('0')));

    HBoxlayout->addWidget(BtnPrevMonth,1);
    HBoxlayout->addWidget(LabelTitle,3);
    HBoxlayout->addWidget(BtnNextMonth,1);

    VBoxlayout->addWidget(CalendarTitle,1,Qt::AlignCenter);

//    connect(&BtnPrevMonth,&QPushButton::clicked(),&this,&ShowPrevMonth());//
    connect(BtnPrevMonth,SIGNAL(clicked(bool)),this,SLOT(ShowPrevMonth()));
    connect(BtnNextMonth,SIGNAL(clicked(bool)),this,SLOT(ShowNextMonth()));

    Gridlayout=new QGridLayout();
    for(int i=0;i<7;i++){
        WeekLabel[i]= new QLabel();
        WeekLabel[i]->setText(s_strWeek[i]);
        if ((0 == i) || (6 == i)) {
            WeekLabel[i]->setProperty("weekend", true);
        }
        WeekLabel[i]->setAlignment(Qt::AlignCenter);
        Gridlayout->addWidget(WeekLabel[i],0,i);
    }
    for(int i=0;i<6;i++){//周
        for(int j=0;j<7;j++){//日
            DayLabel[i*7+j]= new CDayLabel();
            DayLabel[i*7+j]->setText(QString::number(j));
            if ((0 == j) || (6 ==j)) {
                DayLabel[i]->setProperty("weekend", true);
            }
            DayLabel[i*7+j]->setAlignment(Qt::AlignCenter);
            Gridlayout->addWidget(DayLabel[i*7+j],i+1,j);
        }
    }

    VBoxlayout->addLayout(Gridlayout,4);
    this->setLayout(VBoxlayout);
}

void Widget::InitDate(){//初始日期
    // 首先判断当前月的第一天是星期几
    int nWeek  = this->Get1stDayOfWeek(Year, Month);
    int nMonthDays =this->GetMonthDays(Year, Month);
    // 上月天数
    int nPreMonDays = this->GetMonthDays(1 == Month ? Year - 1 : Year, 1 == Month ? 12 : Month - 1);
    // 显示当前年月
    LabelTitle->setText(tr("%1 年 %2 月").arg(Year, 2, 10, QChar('0')).arg(Month, 2, 10, QChar('0')));
    if (0 == nWeek) {
        // 显示上月天数
        for (int i = 0; i < 7; i++) {
            DayLabel[i]->ShowDay((nPreMonDays - 7 + i + 1));
            DayLabel[i]->SetColor(PREV_MONTH_DAY);
        }
        // 显示下月天数
        for (int i = 0; i < (42 - nMonthDays - 7); i++) {
            DayLabel[nMonthDays + 7 + i]->ShowDay((i + 1));
            DayLabel[nMonthDays + 7 + i]->SetColor(NEXT_MONTH_DAY);
        }
    }
    else {
        for (int i = 0; i < nWeek; i++) {//显示上月天数
            DayLabel[i]->ShowDay((nPreMonDays - nWeek + i + 1));
            DayLabel[i]->SetColor(PREV_MONTH_DAY);
        }

        // 显示下月天数
        for (int i = (nWeek + nMonthDays); i < 42; i++) {
            DayLabel[i]->ShowDay((i - (nWeek + nMonthDays) + 1));
            DayLabel[i]->SetColor(NEXT_MONTH_DAY);
        }
    }

    // 显示当前月
    int nProperty = 1;
//    QStringList strPlan;
    int index = 0;
    for (int i = nWeek; i < (nMonthDays + nWeek); i++) {
        index = 0 == nWeek ? (i + 7) : i;
        DayLabel[index]->ShowDay(i - nWeek + 1);
        nProperty = ((0 == (i % 7)) || (6 == (i% 7))) ? WEEKEND_DAY : CURR_MONTH_DAY;
        DayLabel[index]->SetColor(nProperty);

    }

    // 显示当前天数
    DayLabel[Day + nWeek - 1]->SetColor(CURRENT_DAY);
    // 发送更新信号
    Q_EMIT SignalDayChanged();
}

/**
 * @brief CalendarWidget::sltDayClicked 点击响应
 * @param type  类型 0 表示上月 1表示下月
 * @param day  当前点击的天数
 */
void Widget::SltDayClicked(int type, int day)//点击日期
{
    // 上月
    if (PREV_MONTH_DAY == type) {
        ShowPrevMonth();
    }
    // 下月
    else if (NEXT_MONTH_DAY == type) {
        ShowNextMonth();
    }
    // 当天/周末/当月天数都显示在右边
    else if ((CURR_MONTH_DAY == type)
             || (WEEKEND_DAY == type)
             || (CURRENT_DAY == type)) {
        // 选中当天
        Q_EMIT SignalDayClicked(day);
    }
}

/**
 * @brief CalendarWidget::SltShowPrevMonth 显示上月日期
 */
void Widget::ShowPrevMonth()//显示上月
{
    Month--;
    if (Month < 1) {
        Month = 12;
        Year--;
    }

    InitDate();
}

/**
 * @brief CalendarWidget::SltShowNextMonth 显示下月日期
 */
void Widget::ShowNextMonth()//显示下月
{
    Month++;
    if (Month > 12) {
        Month = 1;
        Year++;
    }
    InitDate();
}

int Widget::Get1stDayOfWeek(int year,int month){//当月第一天是星期几
    int week = 0;
    // 获取当年1月1日是星期几
    week = (year + (year- 1) / 4 -(year - 1) / 100 + (year - 1) / 400) % 7;
    week += GetTotalMonthDays(year, month);
    return week % 7;
}

int Widget::GetTotalMonthDays(int year, int month){//一共有多少天
    int nDays = 0;
    int nLoopDay = IsLoopYaer(year) ? 1 : 0;
    switch (month) {
    case  1: nDays =   0;            break;
    case  2: nDays =  31;            break;
    case  3: nDays =  59 + nLoopDay; break;
    case  4: nDays =  90 + nLoopDay; break;
    case  5: nDays = 120 + nLoopDay; break;
    case  6: nDays = 151 + nLoopDay; break;
    case  7: nDays = 181 + nLoopDay; break;
    case  8: nDays = 212 + nLoopDay; break;
    case  9: nDays = 243 + nLoopDay; break;
    case 10: nDays = 273 + nLoopDay; break;
    case 11: nDays = 304 + nLoopDay; break;
    case 12: nDays = 334 + nLoopDay; break;
    default: nDays = 0; break;
    }
    return nDays;
}

int Widget::GetMonthDays(int year, int month){//当月有多少天
    int nDays = 0;
    int nLoopDay = IsLoopYaer(year) ? 1 : 0;
    switch (month) {
        case  1: nDays = 31;            break;
        case  2: nDays = 28 + nLoopDay; break;
        case  3: nDays = 31;            break;
        case  4: nDays = 30;            break;
        case  5: nDays = 31;            break;
        case  6: nDays = 30;            break;
        case  7: nDays = 31;            break;
        case  8: nDays = 31;            break;
        case  9: nDays = 30;            break;
        case 10: nDays = 31;            break;
        case 11: nDays = 30;            break;
        case 12: nDays = 31;            break;
        default: nDays = 30;            break;
        }

    return nDays;
}

bool Widget::IsLoopYaer(int year)//是否闰年
{
    return (((0 == (year % 4)) && (0 != (year % 100))) || (0 == (year % 400)));
}

void Widget::InitStyle(){//初始化样式
    QString strStyle = "";
    strStyle += QString(".CalendarWidget {border: 1px solid #ff00ff;}");
    strStyle += QString(".Window {background: black;}");
    strStyle += QString(".DayLabel{font: 24px; font-family: 隶书;}");
    strStyle += QString("QWidget#widgetCalendar{ background-color: white;}");
    strStyle += QString("QWidget#widgetTitle{ background-color: #c8b9a6;}");
    strStyle += QString("QWidget#widgetWeek{ background-color: #efefef;}");
    strStyle += QString("QLabel#labelTitle {border: none; font: bold 18px;}");
    strStyle += QString("QLabel#labelWeek {border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; font: bold 12px;}");
    strStyle += QString("QLabel#labelDay[weekend=true],QLabel#labelWeek[weekend=true]{color: red;}");
    strStyle += QString("QLabel#labelDay {border-top: 1px solid #c3c3c3; border-left: 1px solid #c3c3c3; font-size: 14px;}");
    strStyle += QString("QLabel#labelShowDay {color: yellow; font: bold 64px;}");
    strStyle += QString("QLabel#labelCommon {color: #ffffff;}");
    strStyle += QString("QLabel#labelSchedule {color: #ffffff; border: 1px solid #ffffff;}");
    strStyle += QString("QLabel#labelSpacer {border: 1px solid #ffffff;}");
    strStyle += QString("QLineEdit {border: 1px solid #ffffff; border-radius: 5px; font-size: 20px;}");

    this->setStyleSheet(strStyle);
}

Widget::~Widget()
{
    delete ui;
}

