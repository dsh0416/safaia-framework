/*
 * This is the route class of Safaia
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 30 Aug 2015
 * */

#include <string>
#include <functional>
#include "Request.h"

#ifndef SAFAIA_FRAMEWORK_ROUTE_H
#define SAFAIA_FRAMEWORK_ROUTE_H

namespace Safaia{
    class Route{

    public:
        Route(std::string path, std::string method, std::function<std::string(Safaia::Request)> function){

        }
    };
}


#endif //SAFAIA_FRAMEWORK_ROUTE_H
