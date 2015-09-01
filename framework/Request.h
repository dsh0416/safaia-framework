/*
 * This is the request class of Safaia
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 2 Sep 2015
 * */

#include <string>
#include <sstream>

#ifndef SAFAIA_FRAMEWORK_REQUEST_H
#define SAFAIA_FRAMEWORK_REQUEST_H

namespace Safaia{
    class Request{

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

        Request(std::string str){
            std::stringstream ss;
            ss << str;
            ss >> method >> request_url >> protocol;
        }
    };
}

#endif //SAFAIA_FRAMEWORK_REQUEST_H
