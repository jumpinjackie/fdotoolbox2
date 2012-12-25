#include "qfdoconnectionhandle.h"

QFdoConnectionHandle::QFdoConnectionHandle(QObject *parent, FdoIConnection *conn, const QString &id) :
    QObject(parent), m_id(id)
{
    m_conn = FDO_SAFE_ADDREF(conn);
}

QFdoConnectionHandle::~QFdoConnectionHandle()
{
    FDO_SAFE_RELEASE(m_conn);
}

FdoIConnection *QFdoConnectionHandle::getConnection()
{
    return FDO_SAFE_ADDREF(m_conn);
}

const QString QFdoConnectionHandle::getId() const
{
    return m_id;
}
