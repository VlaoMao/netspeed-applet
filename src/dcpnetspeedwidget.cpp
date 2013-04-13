#include "dcpnetspeedwidget.h"
#include <mlayout.h>
#include <mlinearlayoutpolicy.h>
#include <mlabel.h>
#include <mbutton.h>
#include <mcombobox.h>
#include <mwidgetcreator.h>
#include <maction.h>
#include <MGridLayoutPolicy>
#include <MLayout>
#include <MLocale>
#include <MContainer>
#include <QGraphicsLinearLayout>
#include <QtNetwork/QNetworkInterface>
#include <MGConfItem>

M_REGISTER_WIDGET_NO_CREATE (NetSpeedWidget)

NetSpeedWidget::NetSpeedWidget (int,QGraphicsWidget *parent)
	    :DcpStylableWidget(parent)
{
    // get gconf keys
    bool enable = MGConfItem("/desktop/meego/status_area/display_netspeed").value().toBool();
    bool whenOnline = MGConfItem("/desktop/meego/status_area/display_netspeed_whenOnline").value().toBool();
    QString iface = MGConfItem("/desktop/meego/status_area/netspeed_interface").value().toString();
    QString updateTime = MGConfItem("/desktop/meego/status_area/netspeed_update_time").value().toString();
    // build the ui:
    MLayout *mainLayout = new MLayout();

    MLinearLayoutPolicy *mainLayoutPolicy =
            new MLinearLayoutPolicy (mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayout->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    MLabel * label = new MLabel(qtTrId("qtn_netspeed_title"), this);
    label->setStyleName ("CommonSingleTitleInverted");
    mainLayoutPolicy->addItem(label);


    MContainer *glbl = createEmptyContainer("CommonContainerInverted",true);
    m_cnt = createEmptyContainer("CommonContainerInverted",false);

    QGraphicsLinearLayout *vlaycnt = new QGraphicsLinearLayout(Qt::Vertical);
    QGraphicsLinearLayout *vlayglbl = new QGraphicsLinearLayout(Qt::Vertical);

    vlaycnt->setContentsMargins(0,0,0,0);
    vlaycnt->setSpacing(10);
    vlayglbl->setContentsMargins(0,0,0,0);
    vlayglbl->setSpacing(10);

    vlayglbl->addItem(createSpacer("CommonLargeSpacer"));
    vlayglbl->addItem(createMyOwnSetting(qtTrId("qtn_netspeed_enable_str"),SLOT(buttonEnableClicked(bool)),enable));
    vlayglbl->addItem(createSpacer("CommonLargeSpacer"));

    vlaycnt->addItem(createSpacer("CommonLargeSpacer"));
    vlaycnt->addItem(createMyOwnSetting(qtTrId("qtn_netspeed_only_online_str"),SLOT(buttonWhenOnlineClicked(bool)),whenOnline));
    vlaycnt->addItem(createSpacer("CommonLargeSpacer"));


    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();

    for(int i = 0; i < ifaces.count(); ++i)
    {
        m_ifaces << ifaces[i].name();
    }

    if(m_ifaces.indexOf("gprs0") == -1)
        m_ifaces << "gprs0";

    m_times << "100" << "500" << "1000" << "2000" << "3000" << "4000" << "5000" << "6000" << "7000" << "8000" << "9000" << "10000";

    int ifacePos = m_ifaces.indexOf(iface);
    bool needIfaceSet = (ifacePos != -1);
    int timePos = m_times.indexOf(updateTime);
    bool needTimeSet = (timePos != -1);

    vlaycnt->addItem(createCombobox(qtTrId("qtn_netspeed_interface_title"),m_ifaces,SLOT(ifaceIndexChanged(int)),ifacePos,needIfaceSet));
    vlaycnt->addItem(createSpacer("CommonLargeSpacer"));
    vlaycnt->addItem(createCombobox(qtTrId("qtn_netspeed_update_title"),m_times,SLOT(updateIndexChanged(int)),timePos,needTimeSet));
    vlaycnt->addItem(createSpacer("CommonLargeSpacer"));

    m_cnt->centralWidget()->setLayout(vlaycnt);
    glbl->centralWidget()->setLayout(vlayglbl);

    mainLayoutPolicy->addItem(glbl);
    mainLayoutPolicy->addItem(m_cnt);
    mainLayoutPolicy->addStretch();

    m_cnt->setVisible(enable);

    setLayout(mainLayout);

}
QGraphicsLayoutItem *NetSpeedWidget::createCombobox(const QString &title,QStringList list, const char *slotName, int initialValue, bool set)
{
    MComboBox *combobox = new MComboBox(this);
    combobox->setTitle(title);
    combobox->setStyleName("CommonComboBoxInverted");

    combobox->addItems(list);
    if(set)
        combobox->setCurrentIndex(initialValue);
    connect(combobox,SIGNAL(currentIndexChanged(int)),slotName);

    return combobox;
}

QGraphicsLayoutItem *NetSpeedWidget::createMyOwnSetting(const QString &title, const char *slotName, bool value)
{
    QGraphicsLinearLayout *lay = new QGraphicsLinearLayout(Qt::Horizontal);
    lay->setContentsMargins(0,0,0,0);
    lay->setSpacing(0);

    MLabel *label = new MLabel(title);
    label->setStyleName ("CommonSingleTitleInverted");
    label->setTextElide(true);

    MButton *button = new MButton("");
    button->setViewType(MButton::switchType);
    button->setStyleName("CommonRightSwitchInverted");
    button->setCheckable(true);
    button->setChecked(value);
    connect(button,SIGNAL(clicked(bool)),slotName,Qt::UniqueConnection);

    lay->addItem(label);
    lay->addItem(button);
    return lay;
}

NetSpeedWidget::~NetSpeedWidget()
{
}

/*
 * This gets called before closing the page.
 * If we return false here, the page will not be closed.
 */
bool NetSpeedWidget::back()
{
    //qDebug ("BACK was asked from me: %d", !m_PreventQuitToggle->isChecked());
    //return ! m_PreventQuitToggle->isChecked();
    return true;
}

/*
 * Example for having a menu item:
 */
/*
QVector<MAction*> NetSpeedWidget::menuItems()
{
    QVector<MAction*> vector (1);
    vector[0] = new MAction("singlepage example", this);
    vector[0]->setLocation(MAction::ApplicationMenuLocation);
    connect (vector[0], SIGNAL(triggered()),
             this, SLOT(startLanguageApplet()));
    return vector;
}*/

QGraphicsLayoutItem *NetSpeedWidget::createSpacer(const QString &style) const
{
    MWidgetController *spacer = new MWidgetController;
    spacer->setViewType(QLatin1String("background"));
    if (!style.isEmpty())
        spacer->setStyleName(style);
    else
        spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return spacer;
}


MContainer *NetSpeedWidget::createEmptyContainer(const QString &containerStyle, bool headerVisible) const
{
    MContainer *container = new MContainer;
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    container->setContentsMargins(0, 0, 0, 0);
    container->setStyleName(containerStyle);
    container->setHeaderVisible(headerVisible);

    return container;
}

void NetSpeedWidget::ifaceIndexChanged(int idx)
{
    MGConfItem("/desktop/meego/status_area/netspeed_interface").set(m_ifaces.at(idx));
}
void NetSpeedWidget::updateIndexChanged(int idx)
{
    MGConfItem("/desktop/meego/status_area/netspeed_update_time").set(m_times.at(idx));
}
void NetSpeedWidget::buttonEnableClicked(bool e)
{
    MGConfItem("/desktop/meego/status_area/display_netspeed").set(e);
    m_cnt->setVisible(e);
}
void NetSpeedWidget::buttonWhenOnlineClicked(bool e)
{
    MGConfItem("/desktop/meego/status_area/display_netspeed_whenOnline").set(e);
}
