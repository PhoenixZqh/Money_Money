#include "MySocketServer.h"

MySocketServer::MySocketServer(int port)
{
    port_ = port;
}

void MySocketServer::onOpen(websocketpp::connection_hdl hdl)
{
    std::cout << "WebSocket connection opened." << std::endl;
    conns_.insert(hdl);
}

void MySocketServer::onClose(websocketpp::connection_hdl hdl)
{
    std::cout << "WebSocket connection closed." << std::endl;
    conns_.erase(hdl);
}

void MySocketServer::onMessage(websocketpp::connection_hdl hdl, message_ptr msg)
{
    std::string message = msg->get_payload();
    if (message == "ping") {
        std::cout << "Received ping message, responding with pong." << std::endl;
        // Respond with a "pong" message
        websocketpp::lib::error_code ec;
        std::string resMsg = "pong";
        ws_server.send(hdl, resMsg, websocketpp::frame::opcode::text, ec);
        if (ec) {
            std::cout << "Failed to send pong message: " << ec.message() << std::endl;
        }
    } else {
        std::cout << "Received message: " << message << std::endl;
        // Handle the received message here.
    }
}

void MySocketServer::sendMessage(const std::string& message)
{
    // Send the message to all connected clients
    for (auto& conn : conns_) {
        websocketpp::lib::error_code ec;
        ws_server.send(conn, message, websocketpp::frame::opcode::text, ec);
        if (ec) {
            std::cout << "Failed to send message: " << ec.message() << std::endl;
        }
    }
}

void MySocketServer::run()
{
    ws_server.set_reuse_addr(true);
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("0.0.0.0"), port_);
    ws_server.set_access_channels(websocketpp::log::alevel::none);
    ws_server.init_asio();

    // Set the callback functions
    ws_server.set_open_handler(bind(&MySocketServer::onOpen, this, websocketpp::lib::placeholders::_1));
    ws_server.set_close_handler(bind(&MySocketServer::onClose, this, websocketpp::lib::placeholders::_1));
    ws_server.set_message_handler(bind(&MySocketServer::onMessage, this, websocketpp::lib::placeholders::_1,
        websocketpp::lib::placeholders::_2));

    // Start the WebSocket server
    ws_server.listen(endpoint);
    ws_server.start_accept();

    std::cout << "WebSocket server started. Listening on port " << port_ << std::endl;

    ws_server.run();
}

// //
// // Created by nhy on 2023/3/13.
// //

// #include "MySocketServer.h"

// //    sub_depth = nh.subscribe(topicName_depth, 10, &MySocketServer::callback_depth, this);
// //    sub_rgb = nh.subscribe(topicName_rgb, 10, &MySocketServer::callback_rgb, this);

// MySocketServer::MySocketServer(int port) {
//     port_ = port;
// }

// void MySocketServer::onOpen(websocketpp::connection_hdl hdl) {
//     std::cout<<"websocket open success"<<std::endl;
//     conns_.insert(hdl);
// }

// void MySocketServer::onClose(websocketpp::connection_hdl hdl) {
//     std::cout<<"websocket close success"<<std::endl;
//     conns_.erase(hdl);

// }

// void MySocketServer::onMessage(websocketpp::connection_hdl hdl, message_ptr msg) {
//     std::string message = msg->get_payload();
//     if (message == "ping") {
//         // 收到来自客户端的心跳包，返回响应的心跳包
//         websocketpp::lib::error_code ec;
//         nlohmann::json json = {};
//         json["data"] = "pong";
//         std::string resMsg = json.dump();
//         try {
//             ws_server.send(hdl, resMsg, websocketpp::frame::opcode::text, ec);
//         } catch (const std::exception &e) {
//             std::cerr << "Exception: " << e.what() << std::endl;
//         }

//         if (ec) {
//             std::cout << "发送心跳包失败: " << ec.message() << std::endl;
//         }
//     }
// }

// void MySocketServer::sendMessage(const std::string &message) {

// //    nlohmann::json json = {};
// //    json["data"] = message;
// //    std::string resMsg = json.dump();
//     // 遍历所有连接，发送消息
//     for (auto &conn: conns_) {
//         try {
//             ws_server.send(conn, message, websocketpp::frame::opcode::text);
//             sleep(0.03);
//         } catch (const std::exception &e) {
//             std::cerr << "Exception: " << e.what() << std::endl;
//         }
//     }
// }

// void MySocketServer::run() {
//     // 设置WebSocket服务器配置
//     ws_server.set_reuse_addr(true);
//     boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("0.0.0.0"), port_);
//     ws_server.set_access_channels(websocketpp::log::alevel::none);
//     ws_server.init_asio();

//     // 设置回调函数
//     ws_server.set_open_handler(bind(&MySocketServer::onOpen, this, websocketpp::lib::placeholders::_1));
//     ws_server.set_close_handler(bind(&MySocketServer::onClose, this, websocketpp::lib::placeholders::_1));
//     ws_server.set_message_handler(bind(&MySocketServer::onMessage, this, websocketpp::lib::placeholders::_1,
//                                        websocketpp::lib::placeholders::_2));

//     // 启动WebSocket服务器
//     ws_server.listen(endpoint);
//     ws_server.start_accept();

//     ws_server.run();

// }
