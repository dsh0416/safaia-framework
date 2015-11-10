#include <string>
#include <sstream>

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