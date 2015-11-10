/*
 * This is the route class of Safaia
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 2 Sep 2015
 * */

#include <string>
#include <regex>
#include <functional>
#include "Request.h"
#include "Response.h"

#ifndef SAFAIA_FRAMEWORK_ROUTE_H
#define SAFAIA_FRAMEWORK_ROUTE_H

namespace Safaia{
    class Route{
    public:

        std::string path;
        std::regex regex_path;
        bool is_regex;
        std::string method;
        std::function<Safaia::Resp(Safaia::Req)> function;

        Route(std::string path, std::string method, std::function<Safaia::Resp(Safaia::Req)> function){
            this->is_regex = false;
            this->path = path;
            this->method = method;
            this->function = function;
        }

        Route(std::regex path, std::string method, std::function<Safaia::Resp(Safaia::Req)> function){
            this->is_regex = true;
            this->regex_path = path;
            this->method = method;
            this->function = function;
        }
    };
}


#endif //SAFAIA_FRAMEWORK_ROUTE_H
