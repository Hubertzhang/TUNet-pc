#include "DataFormatter.h"

QString DataFormatter::trafficForm(double flow)
{
    if (flow < 1E3) {
        return QString::number(flow, 'f', 0) + "B";
    }
    else if (flow < 1E6) {
        return QString::number(flow/1E3, 'f', 2) + "KB";
    }
    else if (flow < 1E9) {
        return QString::number(flow/1E6, 'f', 2) + "MB";
    }
    else{
        return QString::number(flow/1E9, 'f', 2) + "GB";
    }
}

QString DataFormatter::timeForm(int k)
{
    if (k < 10)
        return "0" + QString::number(k);
    else
        return QString::number(k);
}
