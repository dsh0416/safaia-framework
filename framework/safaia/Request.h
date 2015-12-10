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

        Req(std::string str){
            std::stringstream ss;
            ss << str;
            ss >> method >> request_url >> protocol;

            std::string ln;
            getline(ss, ln); // Clean up the \n in the first line

            bool stage = 0; // 0 = Header 1 = Body
            while (getline(ss, ln)){
                if (ln == "\r"){
                    stage = true;
                    continue;
                }
                if(!stage){
                    std::stringstream tmp_ss;
                    tmp_ss << ln;
                    std::string header_name;
                    std::string header_content;

                    tmp_ss >> header_name;
                    getline(tmp_ss, header_content);

                    header_name = header_name.substr(0, header_name.length() - 1);
                    header_content = header_content.substr(1, header_content.length() - 1);

                    header[header_name] = header_content;

                    if (header_name == "Accept") accept = header_content;
                    else if (header_name == "Accept-Encoding") accept_encoding = header_content;
                    else if (header_name == "Accept-Language") accept_language = header_content;
                    else if (header_name == "Cache-Control") cache_control = header_content;
                    else if (header_name == "Cookie") cookie = header_content;
                    else if (header_name == "Host") host = header_content;
                    else if (header_name == "Referer") referer = header_content;
                    else if (header_name == "User-Agent") user_agent = header_content;
                }
                if(stage){
                    body += ln;
                    body += "\n";
                }
            }
        }
    };
}