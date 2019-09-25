#ifndef NOTIFYENUMS_H
#define NOTIFYENUMS_H
#include <QByteArray>
#include <QObject>
#include <QList>

// REGISTRATION IN QML

class MessageLevel : public QObject {
    Q_OBJECT
public:
    enum class MessageType{
        Warning = 1,
        Information,
        Success,
        NoType
    };

    Q_ENUM(MessageType)
private:
    MessageLevel(QObject* parent = nullptr): QObject(parent) {}
};

using MessageType = MessageLevel::MessageType;

#endif // NOTIFYENUMS_H
