#ifndef ONLINESTATEINTERFACE_H
#define ONLINESTATEINTERFACE_H

#include "../backend/NetworkInfoType.h"
#include "../backend/UseregPageService.h"
#include "../DataFormatter.h"
#include "InterfaceEngine.h"
#include <QObject>
#include <QSettings>

class OnlineStateInterface : public QObject
{
    Q_OBJECT

public:
    OnlineStateInterface();

private:
    QSettings settings;
    void initializeInterface();
    void loadName(Info*);

private slots:
    void useregPageQueryState(Info);
    void useregPageDropIp(Info);

public slots:
    void saveName(int,QString,QString);
};

#endif // ONLINESTATEINTERFACE_H
