#ifndef CDAYLABEL_H
#define CDAYLABEL_H

#include <QObject>
#include <QLabel>
#include <QLayout>

extern int Day;
extern int Month;
extern int Year;

typedef enum {
    PREV_MONTH_DAY,     // 上月剩余天数
    NEXT_MONTH_DAY,     // 下个月的天数
    CURR_MONTH_DAY,     // 当月天数
    WEEKEND_DAY,        // 周末
    CURRENT_DAY,        // 当天
} g_Day;

typedef enum {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Week
} g_Week;

class CDayLabel:public QLabel{
public:
    void ShowDay(int day);//展示日期
    void SetColor(const int &type);//设置label颜色


private:

    bool Select;
    bool GetSelect();//返回是否被选中
    void SetSelect(bool value);//设置是否被选中
    void EnterEvent(QEvent *e);
    void LeaveEvent(QEvent *e);
};

#endif // CDAYLABEL_H
