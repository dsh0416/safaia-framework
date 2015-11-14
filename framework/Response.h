#include <string>
#include <sstream>

namespace Safaia{
    class Resp{

    public:
        int status_code = 0;
        std::string content = "";

        Resp(std::string str){
            this->content = str;
        }

        Resp(int status_code, std::string str){
            this->status_code = status_code;
            this->content = str;
        }

    };
}