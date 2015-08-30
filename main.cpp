/*
 * This is an example showing how to use the Safaia-framework.
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 30 Aug 2015
 * */

#include "framework/Safaia.h"
using namespace Safaia;

// Server Configuration
const auto bind_port = 21411;
const auto max_connection = 1024;

int main() {
    auto server = Server(bind_port, max_connection);
    server.add_route(Route("/index", "GET", [](Request req){
        return "Hello World";
    }));
    server.run();
    return 0;
}