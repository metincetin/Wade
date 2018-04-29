#include "wappwindow.h"

WAppWindow::WAppWindow(QWidget *parent) : QWidget(parent)
{
    QApplication a();
    this->m_webview = new QWebEngineView();
}

WApp WAppWindow::setWApp(WApp wapp){
    this->m_wapp = wapp;
    load();
    return this->m_wapp;
}
WApp WAppWindow::wapp(){
    return this->m_wapp;
}

void WAppWindow::load(){
    m_webview->setUrl(wapp().url());
}

void WAppWindow::show(){
    m_webview->setWindowTitle(this->wapp().name());
    m_webview->show();
}
