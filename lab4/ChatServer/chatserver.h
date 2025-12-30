#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include "serverworker.h"

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QObject*parent = nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor)override;
    QVector<ServerWorker*>m_clients;
    void broadcast(const QJsonObject &message,ServerWorker *exclude);

public slots:
    void stopServer();
    void jsonReceived(ServerWorker *sender,const QJsonObject &docObj);
    void userDisconnected(ServerWorker * sender);

signals:
    void logMessage(const QString &msg);


};

#endif // CHATSERVER_H
