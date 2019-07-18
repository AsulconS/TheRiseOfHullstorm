String ConnectionSystem::url;
uint32 ConnectionSystem::timeout = 1000;
EntityManager<Player> ConnectionSystem::players;

void ConnectionSystem::init()
{
    //
}

void ConnectionSystem::update(float deltaTime)
{
    //
}

void ConnectionSystem::destroy()
{
    players.clear();
}

void ConnectionSystem::registerPlayer(const std::string& username, const uint32 score)
{
    Player* player = players.createEntity();
    player->playerData->username = std::move(username);
    player->playerData->score = score;

    std::string content = playerToJSON(player);

    std::string request = "POST " + url +
                          " HTTP/1.1\r\n" +
                          "Host: localhost:8080\r\n" +
                          "Connection: close\r\n" +
                          "Accept: */*\r\n" +
                          "Content-Type: application/json\r\n" +
                          "Content-Length: " + std::to_string(content.size()) + "\r\n" +
                          "\r\n";

    curl::curl_easy easy{};

    std::cout << std::endl;
    std::string fullRequest = request + content + "\r\n";
    std::cout << fullRequest << std::endl;

    try
    {
        easy.add<CURLOPT_URL>(url.c_str());
        easy.add<CURLOPT_CONNECT_ONLY>(true);

        easy.perform();
    }
    catch(const curl::curl_easy_exception& e)
    {
        curl::curlcpp_traceback error = e.get_traceback();
        e.print_traceback();
    }

    curl::curl_sender<std::string> sender(easy);
    sender.send(fullRequest);

    std::cout << "Sent bytes: " << sender.get_sent_bytes() << std::endl;

    while(timeout--)
    {
        try
        {
            curl::curl_receiver<char, 1024> receiver;
            receiver.receive(easy);
        }
        catch(const curl::curl_easy_exception& e)
        {
            e.print_traceback();
            break;
        }
    }
}

String ConnectionSystem::playerToJSON(const Player* player)
{
    std::string content = 
        std::string{"{"} +
            "\"username\":\"" + player->playerData->username + "\", " +
            "\"score\":" + std::to_string(player->playerData->score) +
        "}";
        
    return content;
}
