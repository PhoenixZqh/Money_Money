//
// Created by nhy on 2023/3/13.
//

#ifndef VIDEO_DISPLAYS_MYSOCKETSERVER_H
#define VIDEO_DISPLAYS_MYSOCKETSERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <string>
#include <thread>
#include <set>
#include "nlohmann/json.hpp"
#include <unistd.h>


class MySocketServer {

public:

    MySocketServer() {}

    MySocketServer(int port);

    ~MySocketServer() {
    }

    void run();

    void sendMessage(const std::string &message);

private:
    typedef websocketpp::server<websocketpp::config::asio> server;
    typedef server::message_ptr message_ptr;

    int port_;
    server ws_server;
    std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> conns_;


    void onOpen(websocketpp::connection_hdl hdl);

    void onClose(websocketpp::connection_hdl hdl);

    void onMessage(websocketpp::connection_hdl hdl, message_ptr msg);


};


#endif //VIDEO_DISPLAYS_MYSOCKETSERVER_H
