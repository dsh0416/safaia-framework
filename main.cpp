#include "framework/safaia/Safaia.h"
using namespace Safaia;

int main(){
    auto server = Server();

    server.add_route("GET", "/", [](Req req){
        return Resp("Hello World");
    });

    server.add_route("GET", std::regex("/hello-request/(.*)"), [](Req req){
        EcpAtom atom;
        atom.store("url",req.request_url);
        return Resp(Ecp::render("./views/request_url.html", atom));
    });

    server.run();
    return 0;
}