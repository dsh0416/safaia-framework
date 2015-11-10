/*
 * This is an example showing how to use the Safaia-framework.
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 9 Sep 2015
 * */

#include "framework/Safaia.h"
using namespace Safaia;

int main(){
    auto server = Server();

    server.add_route(Route("/", "GET", [](Req req){
        return Resp("Hello World");
    }));

    server.add_route(Route(std::regex("/index"),"GET",[](Req req){
        return Resp(200, "Hello World");
    }));

    server.add_route(Route("/request_url","GET", [](Req req){
        EcpAtom atom;
        atom.store("url",req.request_url);
        return Resp(ecp("./views/request_url.html",atom));
    }));

    server.log.ansi_color = false;

    server.run();
    return 0;
}