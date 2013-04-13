#include <QDebug>
#include <MAction>
#include <MLibrary>

#include <DcpStylableWidget>
#include "dcpnetspeedapplet.h"
#include "dcpnetspeedwidget.h"

M_LIBRARY
Q_EXPORT_PLUGIN2(netspeedapplet, NetSpeedApplet)

DcpStylableWidget* NetSpeedApplet::constructStylableWidget(int widgetId)
{
    this->currentWidget = new NetSpeedWidget(widgetId);
    return this->currentWidget;
}

QString NetSpeedApplet::title() const
{
    return QString();
}

QVector<MAction*> NetSpeedApplet::viewMenuItems()
{
    return QVector<MAction*>();
}

