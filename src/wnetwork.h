#ifndef WNETWORK_H
#define WNETWORK_H

#include <QObject>
#include "wapp.h"
#include "QNetworkAccessManager"
#include "QNetworkReply"
#include "QTextStream"
#include "QNetworkRequest"
#include "QVariant"
class WNetwork : public QObject
{
    Q_OBJECT
public:
    explicit WNetwork(QObject *parent = nullptr);
    WApp wapp();
    WApp setWapp(WApp);
    void downloadIcons();
private:
    WApp m_wapp;
    QNetworkAccessManager *manager;
signals:

public slots:
    void finishedFetchingIconData(QNetworkReply*);
};

#endif // WNETWORK_H
