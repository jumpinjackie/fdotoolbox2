#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QDockWidget>
#include <QMenuBar>
#include "plugin_interface.h"
#include "objectexplorerwidget.h"

#include "Fdo.h"

int main(int argc, char *argv[])
{
    //Little FDO sanity test. If we can link to FDO and print out the provider names
    //from the registry, our 2 concerns will be addressed:
    //
    // 1. Can we consume FDO from Qt Creator?
    // 2. Is Qt built with wchar_t defined?
    //
    //For Qt5 (which we're assuming you're building this against), both of these should
    //be true
    FdoPtr<IProviderRegistry> providerReg = FdoFeatureAccessManager::GetProviderRegistry();
    const FdoProviderCollection* providers = providerReg->GetProviders();
    for (FdoInt32 i = 0; i < providers->GetCount(); i++)
    {
        const FdoProvider* provider = providers->GetItem(i);
        QString qsProviderName = QString::fromWCharArray(provider->GetName());
        qDebug("Found FDO Provider: %s", qPrintable(qsProviderName));
    }

    QApplication a(argc, argv);
    MainWindow w;

    ObjectExplorerWidget objExp(&w);
    objExp.setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    w.addDockWidget(Qt::LeftDockWidgetArea, &objExp);

    //Call our plugin initializers
    QDir pluginsDir = QDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    QMenuBar* mainMenu = w.menuBar();
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject* ldrInstance = loader.instance();
        if (ldrInstance)
        {
            IPlugin* plugin = qobject_cast<IPlugin*>(ldrInstance);
            if (plugin)
            {
                plugin->initPlugin();
                plugin->registerMenuItems(mainMenu);
            }
        }
    }

    w.show();
    
    return a.exec();
}
