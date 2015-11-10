#include <string>
#include <sstream>

namespace Safaia{
    class Req{

    public:

        std::string method = "";
        std::string request_url = "";
        std::string protocol = "";
        std::string accept = "";
        std::string accept_encoding = "";
        std::string accept_language = "";
        std::string body = "";
        std::string cache_control = "";
        std::string cookie = "";
        std::string host = "";
        std::string referer = "";
        std::string user_agent = "";

        Req(std::string str){
            std::stringstream ss;
            ss << str;
            ss >> method >> request_url >> protocol;
        }
    };
}