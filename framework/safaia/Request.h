#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace Safaia{
    class Req{
    public:
        std::string method = "";
        std::string request_url = "";
        std::string protocol = "";
        std::unordered_map<std::string, std::string> header;
        std::string accept = "";
        std::string accept_encoding = "";
        std::string accept_language = "";
        std::string cache_control = "";
        std::string cookie = "";
        std::string host = "";
        std::string referer = "";
        std::string user_agent = "";

        std::string body = "";

        std::vector<std::string> regex_result;

        // TODO: Finish Request Deserialization
        Req(std::string str){
            std::stringstream ss;
            ss << str;
            ss >> method >> request_url >> protocol;
        }
    };
}