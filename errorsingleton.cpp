#include "errorsingleton.h"


std::shared_ptr<ErrorSingleton> ErrorSingleton::error_Handler = nullptr;
QMutex ErrorSingleton::handlerLocker;

// 1. TODO: Enum register

void operator<<(ErrorSingleton& debug, const QByteArray& reply){
#if DEF_DEBUG == 1
    qDebug() << reply;
#endif

    if(debug.mType ==  MessageType::NoType)
        return;

    if(debug.notifyBellState){
        debug.sendMessageToMainNotification(reply, static_cast<int>(debug.mType));
    }else{
        debug.messageMap.insertMessage(debug.mType, reply);
    }
}

ErrorSingleton *ErrorSingleton::getInstance()
{
    QMutexLocker locker(&handlerLocker);

    if(!error_Handler.get())
        error_Handler = std::shared_ptr<ErrorSingleton>(new ErrorSingleton());

    error_Handler->mType = MessageType::NoType;

    return error_Handler.get();
}

ErrorSingleton &ErrorSingleton::AppWariningRegister(const MessageType& messType)
{
    QMutexLocker locker(&handlerLocker);

    if(!error_Handler.get())
        error_Handler = std::shared_ptr<ErrorSingleton>(new ErrorSingleton());

    error_Handler->mType = messType;

    return *error_Handler;
}

bool ErrorSingleton::getNotifyBellState() const
{
    return notifyBellState;
}

void ErrorSingleton::setNotifyBellState(bool bellState)
{
    if (notifyBellState == bellState)
        return;

    if(notifyBellState){

        if(messageMap.isEmpty()){
            RegisterError(MessageType::Information) << "CODE: MessageMap is Empty";
            return;
        }
        messageForEach(messageMap, [this](auto pair){
            this->sendMessageToMainNotification(pair.second, static_cast<int>(pair.first));
        });
    }

    notifyBellState = bellState;
    emit notifyBellStateChanged();
}
