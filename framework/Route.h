/*
 * This is the route class of Safaia
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 2 Sep 2015
 * */

#include <string>
#include <functional>
#include "Request.h"

#ifndef SAFAIA_FRAMEWORK_ROUTE_H
#define SAFAIA_FRAMEWORK_ROUTE_H

namespace Safaia{
    class Route{
    public:
        std::string path;
        std::string method;
        std::function<std::string(Safaia::Request)> function;
        Route(std::string path, std::string method, std::function<std::string(Safaia::Request)> function){
            this->path = path;
            this->method = method;
            this->function = function;
        }
    };
}


#endif //SAFAIA_FRAMEWORK_ROUTE_H
