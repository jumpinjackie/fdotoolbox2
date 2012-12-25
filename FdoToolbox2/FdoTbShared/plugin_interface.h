#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#include <QString>
#include <QtWidgets/QMenuBar>
#include <QtPlugin>

/// \brief
/// This is the main plugin interface for FDO Toolbox used to register itself with various aspects
/// of the Host Application, such as:
/// \list
///    \li Menu Items
///    \li Toolbar Items
///    \li Object Explorer
class IPlugin
{
public:
    virtual ~IPlugin() { };

    /// \brief
    /// Returns the name of this plugin
    ///
    /// \return
    /// The name of this plugin
    virtual QString getPluginName() const = 0;

    /// \brief
    /// The entry point of the plugin, invoked by the Host Application. This is the first thing called
    ///
    virtual void initPlugin() = 0;

    /// \brief
    /// Registers any menu items into the Host Application's main menu
    ///
    virtual void registerMenuItems(QMenuBar* mainMenu) = 0;
};

#define IID_IPlugin "org.fdotoolbox.IPlugin"

Q_DECLARE_INTERFACE(IPlugin, IID_IPlugin)

#endif // PLUGIN_INTERFACE_H
