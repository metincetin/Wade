#include <QCoreApplication>
#include "qcommandlineparser.h"
#include "QApplication"
#include "QFile"
#include "qdebug.h"
#include "QDir"
#include "QTextStream"
#include "QWebEngineView"
#include "wappwindow.h"
#include "QNetworkAccessManager"
#include "qnetworkreply.h"
#include "wnetwork.h"
void connectOptions(QCoreApplication,QCommandLineParser);
void checkDotWade();
void readIcons(QNetworkReply *reply);
QString appName;

QNetworkAccessManager *manager;
QNetworkRequest request;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Wade");
    QCoreApplication::setApplicationVersion("v0.1");

    QCommandLineParser parser;
    //parser.setApplicationDescription("");
    parser.addVersionOption();
    parser.addHelpOption();


    parser.addPositionalArgument("create","Creates a wade app.","create [url] [appName]");

    parser.process(a);
    const QStringList args = parser.positionalArguments();


    QString command = args.isEmpty()? QString() : args.first();

    checkDotWade();

    if(command == "create"){
        QFile appDesktop (QDir::homePath()+"/.local/share/applications/"+QString(args.last()).toLower()+".desktop");
        appDesktop.open(QIODevice::WriteOnly);
        appName = args.last();
        QTextStream(&appDesktop)
                        <<"[Desktop Entry]\n"
                        <<"Generic Name = " << "x\n"
                        <<"Name="<<args.last()<<"\n"
                        <<"Exec= wade "<<args.last()<<"\n"
                        <<"Icon="<<"~/.wade/"<<args.last()+"/favico.ico";
        appDesktop.close();

        QDir appDir;
        appDir.mkpath(QDir::homePath()+"/.wade/"+QString(args.last()));
        QFile appConfig (QDir::homePath()+"/.wade/"+QString(args.last())+"/config");
        appConfig.open(QIODevice::WriteOnly);
        QTextStream(&appConfig)<<"name= "<<args.last()<<"\n"<<"url= "<<args.at(1);

        appConfig.close();

        QTextStream(stdout)<<args.last()<<" created\n";
        return 0;
    }else{
        //running app
        WAppWindow app;
        WApp wapp;
        wapp.setName(args.last());
        wapp.load();
        app.setWApp(wapp);
        app.show();
    }
    return a.exec();
}

void readIcons(QNetworkReply* reply){
    QTextStream(stdout)<<reply->readAll();
}

void checkDotWade(){
    QDir dir (QDir::homePath()+"/.wade/");

    if(dir.exists()){
    }else{
        QTextStream (stdout)<<"Initializing wade..\n";
        dir.mkdir(QDir::homePath()+"/.wade/");
    }
}
