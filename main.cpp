#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <errorsingleton.h>
#include "messagemap.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("errorManager", ErrorSingleton::getInstance());

    QTimer::singleShot(4000, [](){
    RegisterError(MessageType::Information) << "And share!";
    RegisterError(MessageType::Information) << "Enjoy this widget!";
    RegisterError(MessageType::Information) << "Welcome dear user!";
    });

//    MessageMap<MessageType, QByteArray> messages;

//    messages.insertMessage({MessageType::Information, "Information message!"});
//    messages.insertMessage({MessageType::Success, "Success!"});
//    messages.insertMessage({MessageType::Warning, "Warning!"});
//    messages.insertMessage({MessageType::Information, "Information message!"});
//    qDebug()<< messages;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
