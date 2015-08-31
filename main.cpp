/*
 * This is an example showing how to use the Safaia-framework.
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 31 Aug 2015
 * */

#include "framework/Safaia.h"
using namespace Safaia;

int main(){
    auto server = Server();

    server.add_route(Route("/index", "GET", [](Request req){
        return "Hello World";
    }));

    server.add_route(Route("/request_url","GET", [](Request req){
        std::map<std::string,std::string>dic;
        dic.insert(std::pair<std::string,std::string>("url",req.request_url));
        return ecp("./views/index.ecp",dic);
    }));

    server.run();
    return 0;
}