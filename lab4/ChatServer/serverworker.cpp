#include "serverworker.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>
#include <QJsonValue>
#include<QJsonObject>


ServerWorker::ServerWorker(QObject *parent)
    : QObject{parent}
{
    m_serverSocket = new QTcpSocket(this);
    connect(m_serverSocket,&QTcpSocket::readyRead,this,&ServerWorker::onReadyRead);
    connect(m_serverSocket,&QTcpSocket::disconnected,this,&ServerWorker::disconnectedFromClient);

}

bool ServerWorker::setSocketDescriptor(qintptr sockedDescriptor)
{
    return m_serverSocket->setSocketDescriptor(sockedDescriptor);
}

QString ServerWorker::userName()
{
    return m_userName;
}

void ServerWorker::setUserName(QString user)
{
    m_userName = user;
}

void ServerWorker::onReadyRead()
{
    QByteArray jsonData;
    QDataStream sockStream(m_serverSocket);
    sockStream.setVersion(QDataStream::Qt_6_9);
    for(;;)
    {
        sockStream.startTransaction();
        sockStream>>jsonData;
        if(sockStream.commitTransaction())
        {
            // emit logMessage(QString::fromUtf8(jsonData));
            // sendMessage("i recieved message");

            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&parseError);
            if(parseError.error==QJsonParseError::NoError)
            {
                if(jsonDoc.isObject())
                {
                    emit logMessage(QJsonDocument(jsonDoc).toJson(QJsonDocument::Compact));
                    emit jsonReceived(this,jsonDoc.object());
                }
            }

        }
        else{
            break;
        }
    }
}

void ServerWorker::sendMessage(const QString &text, const QString &type)
{
    if(m_serverSocket->state()!=QAbstractSocket::ConnectedState)
        return;
    if(!text.isEmpty())
    {
        QDataStream serverStream(m_serverSocket);
        serverStream.setVersion(QDataStream::Qt_6_9);

        QJsonObject message;
        message["type"] = type;
        message["text"] = text;

        serverStream<<QJsonDocument(message).toJson();
    }
}

void ServerWorker::sendJson(const QJsonObject &json)
{
    const QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
    emit logMessage(QLatin1String("Sending to")+userName()+QLatin1String(" - ")+
                    QString::fromUtf8(jsonData)) ;
    QDataStream socketStream(m_serverSocket);
    socketStream.setVersion(QDataStream::Qt_6_9);
    socketStream<<jsonData;
}



