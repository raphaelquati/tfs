QT += xml

DEFINES += TFS_LIBRARY

# Tfs files

SOURCES += tfsplugin.cpp \
    tfssettings.cpp \
    tfscontrol.cpp \
    optionspage.cpp \
    tfsclient.cpp \
    clonewizard.cpp \
    clonewizardpage.cpp \
    cloneoptionspanel.cpp \
    tfsworkspacedialog.cpp \
    tfsdatatypes.cpp \
    tfsworkspacedialogedit.cpp \
    tfsworkspacemodel.cpp \
    tfsserverwidget.cpp \
    tfsserverwizardpage.cpp

HEADERS += tfsplugin.h\
        tfs_global.h\
        tfsconstants.h \
    tfssettings.h \
    tfscontrol.h \
    optionspage.h \
    tfsclient.h \
    clonewizard.h \
    clonewizardpage.h \
    cloneoptionspanel.h \
    tfsworkspacedialog.h \
    tfsdatatypes.h \
    tfsworkspacedialogedit.h \
    tfsworkspacemodel.h \
    tfsserverwidget.h \
    tfsserverwizardpage.h

RESOURCES += \
    tfs.qrc

FORMS += \
    optionpage.ui \
    cloneoptionspanel.ui \
    tfsworkspacedialog.ui \
    tfsworkspacedialogedit.ui \
    tfsserverwidget.ui \
    tfsserverlistdialog.ui \
    tfsserveradddialog.ui

# Qt Creator linking

## set the QTC_SOURCE environment variable to override the setting here
QTCREATOR_SOURCES = $$(QTC_SOURCE)
isEmpty(QTCREATOR_SOURCES):QTCREATOR_SOURCES=../qt-creator

## set the QTC_BUILD environment variable to override the setting here
IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE):IDE_BUILD_TREE=../build-qt-creator

## uncomment to build plugin into user config directory
## <localappdata>/plugins/<ideversion>
##    where <localappdata> is e.g.
##    "%LOCALAPPDATA%\QtProject\qtcreator" on Windows Vista and later
##    "$XDG_DATA_HOME/data/QtProject/qtcreator" or "~/.local/share/data/QtProject/qtcreator" on Linux
##    "~/Library/Application Support/QtProject/Qt Creator" on Mac
# USE_USER_DESTDIR = yes

PROVIDER = RavaSoftware

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = Tfs
QTC_LIB_DEPENDS += \
    utils

QTC_PLUGIN_DEPENDS += \
    texteditor \
    coreplugin \
    vcsbase

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$QTCREATOR_SOURCES/src/qtcreatorplugin.pri)

OTHER_FILES += \
    tfs.mimetypes.xml

