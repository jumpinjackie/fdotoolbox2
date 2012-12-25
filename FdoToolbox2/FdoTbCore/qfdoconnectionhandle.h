#ifndef QFDOCONNECTIONHANDLE_H
#define QFDOCONNECTIONHANDLE_H

#include <QObject>
#include "FdoTbCore_global.h"
#include "Fdo.h"

class QFdoConnectionManager;

/// \brief
/// Represents a handle to an FDO connection
///
class FDOTBCORESHARED_EXPORT QFdoConnectionHandle : public QObject
{
    Q_OBJECT

    friend class QFdoConnectionManager;

private:
    explicit QFdoConnectionHandle(QObject *parent, FdoIConnection* conn, const QString& id);
    ~QFdoConnectionHandle();
    
public:

    /// \brief
    /// Gets the underlying FDO connection
    ///
    /// \remarks
    /// Do not open or close this underlying connection! Use the QFdoConnectionManager to do this
    FdoIConnection* getConnection();

    /// \brief
    /// Gets the ID of this connection handle
    ///
    /// \return
    /// The ID of this connection handle
    const QString getId() const;

private:
    FdoIConnection* m_conn;
    QString m_id;

signals:
    
public slots:
    
};

#endif // QFDOCONNECTIONHANDLE_H
