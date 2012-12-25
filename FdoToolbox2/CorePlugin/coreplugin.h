#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include "CorePlugin_global.h"
#include <QObject>
#include <plugin_interface.h>

class CorePlugin : public QObject, public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID IID_IPlugin)
    Q_INTERFACES(IPlugin)

public:
    CorePlugin();
    void initPlugin(QFdoConnectionManager* connMgr);
    void registerMenuItems(QMenuBar* mainMenu);
    QString getPluginName() const;

private:
    void populateFileMenu(QMenu* fileMenu);
    void populateToolsMenu(QMenu* toolsMenu);
    void populateHelpMenu(QMenu* helpMenu);

private slots:
    void registerProvider();
};

#endif // COREPLUGIN_H
