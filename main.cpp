#include "ifask2.h"
#include<qfile.h>
#include <QApplication>
#include<global.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 加载QSS样式
    QFile qss(":/style/stylesheet.qss");
    if (qss.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(qss.readAll());
        qApp->setStyleSheet(styleSheet);
        qss.close();
    }
    // 获取当前应用程序的路径
    QString app_path = QCoreApplication::applicationDirPath();
    // 拼接文件名
    qDebug()<<"path is"<<app_path;
    QString fileName = "config.ini";
    QString config_path = QDir::toNativeSeparators(app_path +QDir::separator() + fileName);
    qDebug() << "Config file path:" << config_path;
    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    qDebug()<<gate_host<<"is";
    QString gate_port = settings.value("GateServer/port").toString();
    qDebug()<<gate_port<<"gate_port";
    gate_url_prefix = "http://"+gate_host+":"+gate_port;
    ifask2 w;
    w.show();
    return a.exec();
}
