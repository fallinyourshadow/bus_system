#ifndef UPDATENOTICEANDWEATHER
#define UPDATENOTICEANDWEATHER

#endif // UPDATENOTICEANDWEATHER
#include "widget.h"
#include <QString>
class Notice
{
public:
    Notice();
    QString  content;
    uint ptime;
    QString weather;
    void set_members(uint,QString,QString);
    int delta_time;
    int calculate_deltatime();





};
