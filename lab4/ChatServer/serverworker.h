#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include<QTcpSocket>
#include<QTcpServer>

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr sockedDescriptor);

    QString userName();
    void setUserName(QString user);

signals:
    void logMessage(const QString & msg);
    void disconnectedFromClient();
    void jsonReceived(ServerWorker *sender,const QJsonObject &docObj);
private:
    QTcpSocket *m_serverSocket;
    QString m_userName;

public slots:
    void onReadyRead();
    void sendMessage(const QString &text ,const QString &type = "message");
    void sendJson(const QJsonObject &json);
};

#endif // SERVERWORKER_H
