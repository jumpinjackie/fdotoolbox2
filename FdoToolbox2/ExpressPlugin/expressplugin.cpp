#include "expressplugin.h"
#include <QList>
#include <QtWidgets/QMenu>

ExpressPlugin::ExpressPlugin()
{
}

void ExpressPlugin::initPlugin(QFdoConnectionManager* connMgr)
{
    qDebug("Loading: %s", qPrintable(this->getPluginName()));
}

void ExpressPlugin::registerMenuItems(QMenuBar* mainMenu)
{
    qDebug("Registering Menu Items: %s", qPrintable(this->getPluginName()));

    QString expressLabel = tr("Express");
    QString helpLabel = tr("Help");

    QMenu* expressMenu = NULL;
    QMenu* helpMenu = NULL;

    QList<QMenu*> menus = mainMenu->findChildren<QMenu*>();

    foreach (QMenu* menu, menus)
    {
        if (menu->title() == expressLabel)
            expressMenu = menu;
        if (menu->title() == helpLabel)
            helpMenu = menu;
    }

    if (expressMenu == NULL)
    {
        if (helpMenu == NULL)
        {
            expressMenu = mainMenu->addMenu(expressLabel);
        }
        else
        {
            expressMenu = new QMenu(expressLabel, mainMenu);
            mainMenu->insertMenu(helpMenu->menuAction(), expressMenu);
        }
    }
}

QString ExpressPlugin::getPluginName() const
{
    return "Express Plugin";
}
