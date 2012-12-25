#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/// \brief
/// This is the Main Window class of FDO Toolbox
///
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addMenuItems();
    void addToolbarItems();
    void setPluginInfo(const QString& path, const QStringList& files);

private slots:
    void aboutActionHandler();
    void aboutPluginsActionHandler();

private:
    bool m_bMenuInit;
    bool m_bToolbarInit;

    QString m_pluginPath;
    QStringList m_pluginFiles;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
