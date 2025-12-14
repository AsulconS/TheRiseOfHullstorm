#ifndef ECS_CONNECTION_SYSTEM_H
#define ECS_CONNECTION_SYSTEM_H

#include <curlcpp/curl_easy.h>
#include <curlcpp/curl_receiver.h>
#include <curlcpp/curl_exception.h>
#include <curlcpp/curl_sender.h>

class ConnectionSystem
{
public:
    static void init();
    static void update(float deltaTime);
    static void destroy();

    inline static void setURL(const String& _url) { url = _url; }
    inline static void setTimeout(const uint32 _timeout) { timeout = _timeout; }

    static void registerPlayer(const std::string& username = "Default", const uint32 score = 0);

private:
    explicit ConnectionSystem() {}

    static String playerToJSON(const Player* player);

    static String url;
    static uint32 timeout;
    static EntityManager<Player> players;
};

#endif // ECS_CONNECTION_SYSTEM_H
