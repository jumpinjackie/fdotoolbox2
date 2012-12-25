#ifndef ABOUTPLUGINSDIALOG_H
#define ABOUTPLUGINSDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>

class IPlugin;

namespace Ui {
class AboutPluginsDialog;
}

class AboutPluginsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AboutPluginsDialog(const QString &path, const QStringList &fileNames, QWidget *parent = 0);
    ~AboutPluginsDialog();
    
    void findPlugins(const QString &path, const QStringList &fileNames);
    void populateTreeWidget(QObject *plugin, const QString &text);
    void addItems(QTreeWidgetItem *pluginItem, const char *interfaceName, const IPlugin *pPlugin);
private:
    Ui::AboutPluginsDialog *ui;
};

#endif // ABOUTPLUGINSDIALOG_H
