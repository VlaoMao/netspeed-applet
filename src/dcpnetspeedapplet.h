#ifndef NETSPEEDAPPLET_H
#define NETSPEEDAPPLET_H

#include <DcpAppletIf>
#include <QObject>
class DcpStylableWidget;
class MAction;

class NetSpeedApplet : public QObject, public DcpAppletIf
{
	Q_OBJECT
	Q_INTERFACES(DcpAppletIf)

public:
    virtual DcpStylableWidget* constructStylableWidget(int widgetId);

    virtual QString title() const;
    virtual QVector<MAction *> viewMenuItems();

protected:
    class NetSpeedWidget* currentWidget;
};

#endif // NETSPEEDAPPLET_H

