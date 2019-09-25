 #ifndef ERRORSINGLETON_H
#define ERRORSINGLETON_H

#define DEF_DEBUG 0
#include <QObject>
#include <QDebug>
#include <memory>
#include <QQueue>
#include <QMutexLocker>
#include "notifyenums.h"
#include "messagemap.h"

// QTimer::singleShot(5000,[](){});

class ErrorSingleton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool notifyBellState READ getNotifyBellState WRITE setNotifyBellState NOTIFY notifyBellStateChanged)   
    // notifyBellState < - set according to notify bell reaction (QML)
public:
    ErrorSingleton(const ErrorSingleton& errSing) = delete;
    ErrorSingleton& operator=(const ErrorSingleton& errSing) = delete;

    static ErrorSingleton* getInstance();
    static ErrorSingleton& AppWariningRegister(const MessageType& mType);


    void setNotifyBellState(bool bellState);
    bool getNotifyBellState() const;

    friend void operator<<(ErrorSingleton& debug,
                           const QByteArray& reply);
signals:
    void notifyBellStateChanged();
    void sendMessageToMainNotification(const QString& message,
                                       int type);
private:
    explicit ErrorSingleton(QObject *parent = nullptr): QObject(parent) {}

    bool                                   notifyBellState = true;
    static QMutex                          handlerLocker;
    static std::shared_ptr<ErrorSingleton> error_Handler;
    MessageMap<MessageType, QByteArray>    messageMap;
    MessageType                            mType;
};

constexpr auto RegisterError = &ErrorSingleton::AppWariningRegister;

#endif // ERRORSINGLETON_H
