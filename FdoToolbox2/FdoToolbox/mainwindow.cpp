#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "aboutpluginsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_bMenuInit(false),
    m_bToolbarInit(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMenuItems()
{
    if (!m_bMenuInit)
    {
        qDebug("Registering Main Menu Items");

        QString helpLabel = tr("Help");

        QMenu* helpMenu = NULL;

        QList<QMenu*> menus = menuBar()->findChildren<QMenu*>();

        foreach (QMenu* menu, menus)
        {
            if (menu->title() == helpLabel)
                helpMenu = menu;
        }

        if (helpMenu == NULL)
        {
            helpMenu = menuBar()->addMenu(helpLabel);
        }

        QAction* aboutAction = new QAction(tr("About FDO Toolbox"), this);
        QAction* aboutPluginsAction = new QAction(tr("About Plugins"), this);

        if (helpMenu->children().count() > 0)
            helpMenu->addSeparator();

        helpMenu->addAction(aboutAction);
        helpMenu->addAction(aboutPluginsAction);

        connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutActionHandler()));
        connect(aboutPluginsAction, SIGNAL(triggered()), this, SLOT(aboutPluginsActionHandler()));

        m_bMenuInit = true;
    }
}

void MainWindow::addToolbarItems()
{
    if (!m_bToolbarInit)
    {
        m_bToolbarInit = true;
    }
}

void MainWindow::setPluginInfo(const QString &path, const QStringList &files)
{
    m_pluginPath = path;
    m_pluginFiles = files;
}

void MainWindow::aboutActionHandler()
{
    AboutDialog* diag = new AboutDialog(this);
    diag->show();
}

void MainWindow::aboutPluginsActionHandler()
{
    AboutPluginsDialog* diag = new AboutPluginsDialog(m_pluginPath, m_pluginFiles, this);
    diag->show();
}
