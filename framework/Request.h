/*
 * This is the request class of Safaia
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 30 Aug 2015
 * */

#include <string>

#ifndef SAFAIA_FRAMEWORK_REQUEST_H
#define SAFAIA_FRAMEWORK_REQUEST_H

class Request{

public:

    std::string request_url = "";
    std::string method = "";
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

    }
};

#endif //SAFAIA_FRAMEWORK_REQUEST_H
