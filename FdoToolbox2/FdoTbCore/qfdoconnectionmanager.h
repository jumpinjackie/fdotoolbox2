#ifndef QFDOCONNECTIONMANAGER_H
#define QFDOCONNECTIONMANAGER_H

#include <QObject>
#include <QMap>
#include "FdoTbCore_global.h"
#include "qfdoconnectionhandle.h"
#include "Fdo.h"

/// \brief
/// Manages the creation and access of FDO connections. Access is obtained through
/// QFdoConnectionHandle objects
///
class FDOTBCORESHARED_EXPORT QFdoConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit QFdoConnectionManager(QObject *parent = 0);
    ~QFdoConnectionManager();

    /// \brief
    /// Creates a new FDO Connection
    ///
    /// \param fdoProviderName (QString)
    /// The FDO provider name
    /// \param connectionString (QString)
    /// The FDO connection string
    ///
    /// \return
    /// A new QFdoConnectionHandle for this connection
    const QFdoConnectionHandle* createConnection(const QString& fdoProviderName, const QString& connectionString);

    /// \brief
    /// Creates a new FDO Connection
    ///
    /// \param fdoProviderName (QString)
    /// The FDO provider name
    /// \param connectionProperties (QMap<QString, QString>)
    /// The FDO connection properties
    ///
    /// \return
    /// A new QFdoConnectionHandle for this connection
    const QFdoConnectionHandle* createConnection(const QString& fdoProviderName, const QMap<QString, QString>& connectionProperties);

    /// \brief
    /// Opens the FDO connection indicated by the specified handle
    ///
    /// \param handle (QFdoConnectionHandle*)
    /// The FDO connection handle
    void openConnection(QFdoConnectionHandle* handle);

    /// \brief
    /// Closes a FDO connection by the specified handle
    ///
    /// \param handle (QFdoConnectionHandle*)
    /// The FDO connection handle
    /// \param bRemove (bool)
    /// true to remove this FDO connection, false to retain it (allowing it to be re-opened)
    void closeConnection(QFdoConnectionHandle* handle, bool bRemove = false);

private:
    QString makeName(FdoIConnection* conn);

    FdoPtr<IConnectionManager> m_connMgr;
    QMap<QString, QFdoConnectionHandle*> m_handles;

signals:
    void connectionOpened(const QFdoConnectionHandle* handle);
    void connectionClosed(const QFdoConnectionHandle* handle);
    void connectionRemoved(const QFdoConnectionHandle* handle);
    
public slots:
    
};

#endif // QFDOCONNECTIONMANAGER_H
