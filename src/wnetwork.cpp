#include "wnetwork.h"

WNetwork::WNetwork(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&WNetwork::finishedFetchingIconData);
}

WApp WNetwork::setWapp(WApp wapp){
    return this->m_wapp = wapp;
}
WApp WNetwork::wapp(){
    return this->m_wapp;
}
void WNetwork::downloadIcons(){
    QNetworkRequest request(this->m_wapp.url());
    QSslConfiguration sslConfiguration(QSslConfiguration::defaultConfiguration());
    sslConfiguration.setProtocol(QSsl::TlsV1_0OrLater);
    request.setSslConfiguration(sslConfiguration);
    manager->get(request);
}

void WNetwork::finishedFetchingIconData(QNetworkReply* reply){

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QTextStream(stdout)<<"Status code: "<<statusCode<<"\n";
    if(statusCode == 302)
    {
        QUrl newUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
        qDebug() << "redirected from " + reply->url().toString() + " to " + newUrl.toString();
        QNetworkRequest newRequest(newUrl);
        QSslConfiguration sslConfiguration(QSslConfiguration::defaultConfiguration());
        sslConfiguration.setProtocol(QSsl::SslV2);
        newRequest.setSslConfiguration(sslConfiguration);

        manager->get(newRequest);
        return;
    }

    QByteArray bytes = reply->readAll();
    QString str = QString::fromUtf8(bytes.data(), bytes.size());

    QTextStream(stdout)<<str;
    QTextStream(stdout)<<"DONE";
}
