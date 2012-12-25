#include "aboutpluginsdialog.h"
#include "ui_aboutpluginsdialog.h"
#include "plugin_interface.h"

#include <QPluginLoader>
#include <QStringList>
#include <QDir>
#include <QTreeWidgetItem>

AboutPluginsDialog::AboutPluginsDialog(const QString& path, const QStringList& fileNames, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutPluginsDialog)
{
    ui->setupUi(this);

    ui->treeWidget->setAlternatingRowColors(false);
    ui->treeWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->header()->hide();

    findPlugins(path, fileNames);
}

AboutPluginsDialog::~AboutPluginsDialog()
{
    delete ui;
}

void AboutPluginsDialog::findPlugins(const QString &path,
                                     const QStringList &fileNames)
{
    //label->setText(tr("Plug & Paint found the following plugins\n"
    //                  "(looked in %1):")
    //                 .arg(QDir::toNativeSeparators(path)));

    const QDir dir(path);

    foreach (QObject *plugin, QPluginLoader::staticInstances())
        populateTreeWidget(plugin, tr("%1 (Static Plugin)")
                                     .arg(plugin->metaObject()->className()));

    foreach (QString fileName, fileNames) {
        QPluginLoader loader(dir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin)
            populateTreeWidget(plugin, fileName);
    }
}

void AboutPluginsDialog::populateTreeWidget(QObject *plugin, const QString &text)
{
    QTreeWidgetItem *pluginItem = new QTreeWidgetItem(ui->treeWidget);
    pluginItem->setText(0, text);
    ui->treeWidget->setItemExpanded(pluginItem, true);

    QFont boldFont = pluginItem->font(0);
    boldFont.setBold(true);
    pluginItem->setFont(0, boldFont);

    if (plugin) {
        IPlugin *pPlugin = qobject_cast<IPlugin *>(plugin);
        if (pPlugin)
            addItems(pluginItem, "IPlugin", pPlugin);
    }
}

void AboutPluginsDialog::addItems(QTreeWidgetItem *pluginItem,
                                  const char *interfaceName,
                                  const IPlugin* pPlugin)
{
    QTreeWidgetItem *interfaceItem = new QTreeWidgetItem(pluginItem);
    interfaceItem->setText(0, interfaceName);
    //interfaceItem->setIcon(0, interfaceIcon);

    QTreeWidgetItem *nameItem = new QTreeWidgetItem(interfaceItem);
    nameItem->setText(0, pPlugin->getPluginName());
    //nameItem->setIcon(0, featureIcon);
}
