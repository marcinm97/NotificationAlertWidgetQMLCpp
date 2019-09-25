#ifndef MESSAGEMAP_H
#define MESSAGEMAP_H

#include <QDebug>
#include <map>
#include <QString>
#include <random>
#include <QMutexLocker>
#include <QMutex>
#include <QTimer>
#include <algorithm>

// # TODO LIST #
// 1. QSingleShot to erase deprecated alerts
// 2. Method to store actual number how many given type messages are there
// 3. Own for_each friend function to send data

// MType - message type
// MAlert - description

template<typename MType, typename MAlert>
class MessageMap
{
public:
    using tInterval    = unsigned int;
    using messPair     = std::pair<MType, MAlert>;
    using mContainer   = std::multimap<MType, MAlert>;
    using mapIter      = typename std::multimap<MType, MAlert>::iterator;
    using initList     = std::initializer_list<std::pair<const MType, MAlert>>;

    MessageMap(): tDuration(1*60*1000) {}
    MessageMap(const mContainer& cpyMessage, tInterval storageTime = 1*60*1000): messages(cpyMessage), tDuration(storageTime) {}
    MessageMap(const initList& initMessages, tInterval storageTime = 1*60*1000): messages(initMessages), tDuration(storageTime) {}
    MessageMap(const mapIter& first, const mapIter& last, tInterval storageTime = 1*60*1000): messages(first, last),
        tDuration(storageTime) {}

    MessageMap(const MessageMap<MType, MAlert>& mMap): messages(mMap.messages), tDuration(mMap.tDuration) {}

    template<typename T, typename Pred>
    friend void messageForEach(T map, Pred pred);

    MessageMap<MType, MAlert>& operator=(const MessageMap<MType, MAlert>& mMap){
        if(this == &mMap)
            return *this;

        // send deprecated datas to frontend
        messages.clear();
        messages = mMap.messages;
        tDuration = mMap.tDuration;

        return *this;
    }

    void insertMessage(const messPair& mPair){
        if(contains(mPair))
            return;

        messages.insert(mPair);

       QTimer::singleShot(tDuration, [this, mPair]() -> void {
           QMutexLocker locker(&messagesLocker);

           auto check = getMapPosition(mPair);
           if(check != messages.end())
               messages.erase(check);
       });
    }
    void setMessageDuration(unsigned int interval){
        if(tDuration == interval)
            return;

        tDuration = interval;
    }

    void insertMessage(const MType& fType, const MAlert& mAlert){
        insertMessage(std::make_pair(fType, mAlert));
    }

    bool contains(const messPair& conMessage){
        auto finder([conMessage](auto pair){
            if(pair.first == conMessage.first && pair.second == conMessage.second)
                return true;

            return false;
        });

        return std::find_if(messages.begin(), messages.end(), finder) != messages.end();
    }

    mContainer getCurrentMessages() const{
        return messages;
    }

    mapIter findByKey(const MType& key);
    mapIter findByValue(const MAlert& value);
    mapIter findByMessage(const messPair& message);

    size_t  uniqueKeyCount(const MType& key);   // how many massages of given 'key' are contained

    size_t  size() const{
        return messages.size();
    }

    bool isEmpty() const{
        return messages.empty();
    }

    //MAlert& operator[](const MType& key);

    friend QDebug operator<<(QDebug debug, const MessageMap& mMap){
        for(auto mess: mMap.messages){
            debug << mess;
        }

        return debug;
    }

private:

    mapIter getMapPosition(const messPair& cPair){
        auto finder([cPair](auto pair){
            if(pair.first == cPair.first && pair.second == cPair.second)
                return true;

            return false;
        });

        return std::find_if(messages.begin(), messages.end(), finder);
    }

    tInterval tDuration;
    QMutex messagesLocker;
    std::multimap<MType, MAlert> messages;
};

template<typename T, typename Pred>
void messageForEach(T map, Pred pred){
    for(const auto& m: map.messages){
        pred(m);
    }
}


#endif // MESSAGEMAP_H
