#ifndef WAPP_H
#define WAPP_H

#include "QString"
#include "QUrl"
#include "QFile"
#include "QDir"
#include "QTextStream"
#include "QIcon"
#include "QRegularExpression"
class WApp
{
public:
    WApp();
    QString name();
    QString setName(QString);
    QUrl url();
    QUrl setUrl(QUrl);
    WApp *load();
    QIcon icon();
private:
    QString m_name;
    QUrl m_url;
    QIcon m_icon;
};

#endif // WAPP_H
