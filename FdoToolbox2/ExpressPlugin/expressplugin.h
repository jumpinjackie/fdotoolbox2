#ifndef EXPRESSPLUGIN_H
#define EXPRESSPLUGIN_H

#include "ExpressPlugin_global.h"
#include <QObject>
#include <plugin_interface.h>

class ExpressPlugin : public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IID_IPlugin)
    Q_INTERFACES(IPlugin)

public:
    ExpressPlugin();
    void initPlugin();
    void registerMenuItems(QMenuBar* mainMenu);
    QString getPluginName() const;
};

#endif // EXPRESSPLUGIN_H
