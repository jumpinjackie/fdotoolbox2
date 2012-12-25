#include "qfdoconnectionmanager.h"

QFdoConnectionManager::QFdoConnectionManager(QObject *parent) :
    QObject(parent)
{
    m_connMgr = FdoFeatureAccessManager::GetConnectionManager();
}

QFdoConnectionManager::~QFdoConnectionManager()
{
    m_connMgr = NULL;
    qDebug("Tearing down all FDO connection handles");
    for (QMap<QString, QFdoConnectionHandle*>::const_iterator i = m_handles.begin(); i != m_handles.end(); i++)
    {
        QFdoConnectionHandle* handle = i.value();
        QString qsConnID = i.key();
        FdoPtr<FdoIConnection> conn = handle->getConnection();
        try
        {
            conn->Close();
            delete handle;
            qDebug("Torn down connection: %s", qPrintable(qsConnID));
        }
        catch (FdoException* ex)
        {
            FDO_SAFE_RELEASE(ex);
        }
    }
    m_handles.clear();
}

const QFdoConnectionHandle *QFdoConnectionManager::createConnection(const QString &fdoProviderName, const QString &connectionString)
{
    std::wstring providerName = fdoProviderName.toStdWString();
    std::wstring connStr = connectionString.toStdWString();

    FdoPtr<FdoIConnection> conn = m_connMgr->CreateConnection(providerName.c_str());
    conn->SetConnectionString(connStr.c_str());

    QString name = makeName(conn);
    QFdoConnectionHandle* handle = new QFdoConnectionHandle(this, conn, name);

    m_handles.insert(name, handle);
    return handle;
}

const QFdoConnectionHandle *QFdoConnectionManager::createConnection(const QString &fdoProviderName, const QMap<QString, QString> &connectionProperties)
{
    std::wstring providerName = fdoProviderName.toStdWString();

    FdoPtr<FdoIConnection> conn = m_connMgr->CreateConnection(providerName.c_str());
    FdoPtr<FdoIConnectionInfo> connInfo = conn->GetConnectionInfo();
    FdoPtr<FdoIConnectionPropertyDictionary> connProps = connInfo->GetConnectionProperties();

    for (QMap<QString, QString>::const_iterator i = connectionProperties.begin(); i != connectionProperties.end(); i++)
    {
        std::wstring key = i.key().toStdWString();
        std::wstring value = i.value().toStdWString();

        connProps->SetProperty(key.c_str(), value.c_str());
    }

    QString name = makeName(conn);
    QFdoConnectionHandle* handle = new QFdoConnectionHandle(this, conn, name);

    m_handles.insert(name, handle);
    return handle;
}

void QFdoConnectionManager::openConnection(QFdoConnectionHandle *handle)
{
    FdoPtr<FdoIConnection> conn = handle->getConnection();
    if (conn->Open())
        emit connectionOpened(handle);
}

void QFdoConnectionManager::closeConnection(QFdoConnectionHandle *handle, bool bRemove)
{
    FdoPtr<FdoIConnection> conn = handle->getConnection();
    conn->Close();
    emit connectionClosed(handle);
    if (bRemove)
    {
        m_handles.remove(handle->getId());
        emit connectionRemoved(handle);
    }
}

QString QFdoConnectionManager::makeName(FdoIConnection *conn)
{
    FdoPtr<FdoIConnectionInfo> connInfo = conn->GetConnectionInfo();
    FdoString* name = connInfo->GetProviderName();
    FdoProviderNameTokensP tokens = FdoProviderNameTokens::Create(name);
    FdoStringsP tokenParts = tokens->GetNameTokens();
    FdoPtr<FdoStringElement> techPart = tokenParts->GetItem(1);
    FdoString* techPartStr = (FdoString*)techPart->GetString();

    QString qsTechPart = QString::fromWCharArray(techPartStr);
    QString prefix;
    prefix.append(qsTechPart);
    prefix.append("_Connection_");

    int counter = 1;
    QString connID = prefix;
    QString numStr = QString::number(counter);
    connID.append(numStr);
    while (m_handles.contains(connID))
    {
        counter++;
        connID = prefix;
        numStr = QString::number(counter);
        connID.append(numStr);
    }
    return connID;
}
