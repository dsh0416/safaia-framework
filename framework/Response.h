/*
 * This is the request class of Safaia
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 10 Nov 2015
 * Last Edited Time: 10 Nov 2015
 * */

#include <string>
#include <sstream>

#ifndef SAFAIA_FRAMEWORK_RESPONSE_H
#define SAFAIA_FRAMEWORK_RESPONSE_H

namespace Safaia{
    class Resp{

    public:
        int status_code = 0;

        Resp(std::string str){
            std::stringstream ss;
            ss << str;
        }

        Resp(int status_code, std::string str){
            this->status_code = status_code;
        }

    };
}


#endif //SAFAIA_FRAMEWORK_RESPONSE_H
