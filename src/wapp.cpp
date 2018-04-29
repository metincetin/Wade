#include "wapp.h"

WApp::WApp()
{

}

QString WApp::name(){
    return this->m_name;
}

QString WApp::setName(QString name){
    return this->m_name = name;
}

QUrl WApp::url(){
    return this->m_url;
}

QUrl WApp::setUrl(QUrl url){
    return this->m_url = url;
}


WApp *WApp::load(){
    QFile config(QDir::homePath()+"/.wade/"+this->name()+"/config");
    QString configData;
    config.open(QIODevice::ReadOnly);
    configData = config.readAll();
    config.close();
    for(int i=0;i<configData.split("\n").length();i++){
        QString line = configData.split("\n")[i];
        QString left = line.split("=")[0].trimmed();
        QString right = line.split("=")[1].trimmed();

        if(left == "name"){
            this->setName(right);
        }else if(left == "url"){
            this->setUrl(QUrl(right));
            QTextStream (stdout)<<right;
        }else if(left == "icon"){
            this->m_icon = QIcon(right);
        }
    }
    return this;
}

QIcon WApp::icon()
{
    return this->m_icon;
}
