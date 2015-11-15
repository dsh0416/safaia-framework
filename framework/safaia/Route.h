#include <string>
#include <regex>
#include <functional>
#include "Request.h"
#include "Response.h"

namespace Safaia{
    class Route{
    public:

        std::string path;
        std::regex regex_path;
        bool is_regex;
        std::string method;
        std::function<Safaia::Resp(Safaia::Req)> function;

        Route(std::string method, std::string path, std::function<Safaia::Resp(Safaia::Req)> function){
            this->is_regex = false;
            this->path = path;
            this->method = method;
            this->function = function;
        }

        Route(std::string method, std::regex path, std::function<Safaia::Resp(Safaia::Req)> function){
            this->is_regex = true;
            this->regex_path = path;
            this->method = method;
            this->function = function;
        }
    };
}