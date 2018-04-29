#ifndef WAPPWINDOW_H
#define WAPPWINDOW_H

#include <QWidget>
#include "wapp.h"
#include "QWebEngineView"
#include "QIcon"
#include "QWebChannel"
class WAppWindow : public QWidget
{
    Q_OBJECT
public:
    explicit WAppWindow(QWidget *parent = nullptr);
    QWebEngineView *webview();
    WApp wapp();
    WApp setWApp(WApp);

    void load();
    void show();
signals:

public slots:
private:
    WApp m_wapp;
    QWebEngineView *m_webview;
};

#endif // WAPPWINDOW_H
