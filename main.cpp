/*
 * This is an example showing how to use the Safaia-framework.
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 30 Aug 2015
 * */

#include "framework/Safaia.h"

// Server Configuration Start
const int port = 21411;
const int max_connections = 1024;
// Server Configuration End

int main() {
    Safaia server = Safaia::Safaia(port, max_connections);
    server.add_route(Route("/index", "GET", [](Request req){return "Hello World";}));
    server.run();
    return 0;
}