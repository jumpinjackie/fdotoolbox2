#include "coreplugin.h"
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include "Fdo.h"

CorePlugin::CorePlugin()
{
}

void CorePlugin::initPlugin(QFdoConnectionManager *connMgr)
{
    qDebug("Loading: %s", qPrintable(this->getPluginName()));
}

void CorePlugin::registerMenuItems(QMenuBar* mainMenu)
{
    qDebug("Registering Menu Items: %s", qPrintable(this->getPluginName()));

    QString fileLabel = tr("File");
    QString toolsLabel = tr("Tools");
    QString helpLabel = tr("Help");

    QMenu* fileMenu = NULL;
    QMenu* toolsMenu = NULL;
    QMenu* helpMenu = NULL;

    QList<QMenu*> menus = mainMenu->findChildren<QMenu*>();

    foreach (QMenu* menu, menus)
    {
        if (menu->title() == fileLabel)
            fileMenu = menu;
        else if (menu->title() == toolsLabel)
            toolsMenu = menu;
        else if (menu->title() == helpLabel)
            helpMenu = menu;
    }

    if (fileMenu == NULL)
    {
        fileMenu = mainMenu->addMenu(fileLabel);
    }

    if (toolsMenu == NULL)
    {
        toolsMenu = mainMenu->addMenu(toolsLabel);
    }

    if (helpMenu == NULL)
    {
        helpMenu = mainMenu->addMenu(helpLabel);
    }

    populateFileMenu(fileMenu);
    populateToolsMenu(toolsMenu);
    populateHelpMenu(helpMenu);
}

void CorePlugin::populateFileMenu(QMenu *fileMenu)
{
    QAction* connectToData = new QAction("Connect to Data", this);
    QAction* createDataStore = new QAction("Create Data Store", this);
    QAction* quit = new QAction("Quit", this);

    fileMenu->addAction(connectToData);
    fileMenu->addAction(createDataStore);
    fileMenu->addSeparator();
    fileMenu->addAction(quit);

    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void CorePlugin::populateToolsMenu(QMenu *toolsMenu)
{
    QMenu* fdoMenu = toolsMenu->addMenu(tr("FDO"));

    QAction* registerProvider = new QAction("Register Provider", this);
    fdoMenu->addAction(registerProvider);

    connect(registerProvider, SIGNAL(triggered()), this, SLOT(registerProvider()));
}

void CorePlugin::populateHelpMenu(QMenu* /*helpMenu*/)
{

}

QString CorePlugin::getPluginName() const
{
    return "Core Plugin";
}

void CorePlugin::registerProvider()
{
    QWidget* activeWin = qApp->activeWindow();
    QString fileName = QFileDialog::getOpenFileName(activeWin, tr("Register Provider"), qApp->applicationDirPath(), tr("FDO Providers (*.dll *.so)"));

    if (fileName.isEmpty() || fileName.isNull())
        return;

    try
    {
        FdoPtr<IConnectionManager> connMgr = FdoFeatureAccessManager::GetConnectionManager();
        FdoPtr<IProviderRegistry> provReg = FdoFeatureAccessManager::GetProviderRegistry();
        wchar_t libPath[1024];
        fileName.toWCharArray(libPath);
        FdoPtr<FdoIConnection> conn = connMgr->CreateConnection(libPath);
        FdoPtr<FdoIConnectionInfo> connInfo = conn->GetConnectionInfo();

        provReg->RegisterProvider(connInfo->GetProviderName(),
                                  connInfo->GetProviderDisplayName(),
                                  connInfo->GetProviderDescription(),
                                  connInfo->GetProviderVersion(),
                                  connInfo->GetFeatureDataObjectsVersion(),
                                  libPath,
                                  false);

        QMessageBox::information(activeWin, tr("Register Provider"), tr("Provider successfully registered"));
    }
    catch (FdoException* ex)
    {
        QString exMsg = tr("Error registering FDO provider: ");
        exMsg += QString::fromWCharArray(ex->GetExceptionMessage());
        QMessageBox::critical(activeWin, tr("Register Provider"), exMsg);
        FDO_SAFE_RELEASE(ex);
    }
}
