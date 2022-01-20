#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "cdaylabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

static const QString s_strWeek[] = {
    QObject::tr("周日"), QObject::tr("周一"), QObject::tr("周二"),
    QObject::tr("周三"), QObject::tr("周四"), QObject::tr("周五"),
    QObject::tr("周六"),
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void InitWidget();
    void InitDate();
    void InitStyle();
    ~Widget();

private:
    Ui::Widget *ui;

    int Get1stDayOfWeek(int year,int month);
    int GetTotalMonthDays(int year, int month);
    int GetMonthDays(int year, int month);
    bool IsLoopYaer(int year);

    QVBoxLayout *VBoxlayout;
    QGridLayout *Gridlayout;
    QHBoxLayout *HBoxlayout;
    QPushButton *BtnPrevMonth;
    QPushButton *BtnNextMonth;
    QWidget *CalendarTitle;
    QLabel *LabelTitle;
    CDayLabel *DayLabel[42];
    QLabel *WeekLabel[7];
//    QLabel *LabelShowToday;
//    QLabel *LabelShowWeek;
//    QLabel *LabelShowDay;
//    QLabel *LabelShowYear;

signals:
    void SignalDayChanged();
    void SignalDayClicked(int);
private slots:
    void ShowPrevMonth();
    void ShowNextMonth();
    void SltDayClicked(int type, int day);
};
#endif // WIDGET_H
