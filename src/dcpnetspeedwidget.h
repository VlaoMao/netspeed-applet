#ifndef NETSPEEDWIDGET_H
#define NETSPEEDWIDGET_H

#include <DcpStylableWidget>

class MLabel;
class MButton;
class MAction;
class MContainer;

class NetSpeedWidget : public DcpStylableWidget
{
    Q_OBJECT

public:
    NetSpeedWidget(int num, QGraphicsWidget *parent = 0);
    virtual ~NetSpeedWidget();

    virtual bool back ();
    //virtual QVector<MAction*> menuItems();
    QGraphicsLayoutItem* createSpacer(const QString &style) const;
    QGraphicsLayoutItem *createMyOwnSetting(const QString &title,const char *slotName, bool value);
    QGraphicsLayoutItem *createCombobox(const QString& title,QStringList list,const char *slotName,int initialValue = 0,bool set = false);
    MContainer* createEmptyContainer(const QString &containerStyle, bool headerVisible = false) const;
public slots:
    void buttonEnableClicked(bool);
    void buttonWhenOnlineClicked(bool);
    void ifaceIndexChanged(int);
    void updateIndexChanged(int);
private:
    MButton* createButton (const QString& title, const char* method);
    QStringList m_ifaces;
    QStringList m_times;
    MContainer *m_cnt;
};

#endif // NETSPEEDWIDGET_H

