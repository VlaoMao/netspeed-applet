TEMPLATE      = lib
CONFIG       += plugin gui meegotouch
VERSION = 1.0.0

INCLUDEPATH += /usr/include/duicontrolpanel
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       += dcpnetspeedapplet.h \
                 dcpnetspeedwidget.h \

SOURCES       = dcpnetspeedapplet.cpp \
                dcpnetspeedwidget.cpp

TARGET        = $$qtLibraryTarget(netspeedapplet)
desktop.files += *.desktop
desktop.path = /usr/share/duicontrolpanel/desktops
target.path = /usr/lib/duicontrolpanel/applets

INSTALLS += \
	    target \
	    desktop

