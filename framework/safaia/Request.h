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
                    header[header_name.substr(0, header_name.length() - 1)] = header_content.substr(1, header_content.length() - 1);
                }
                if(stage){
                    body += ln;
                    body += "\n";
                }
            }

            // Fast headers
            if(header.find("Accept")!=header.end()) accept = header["Accept"];
            if(header.find("Accept-Encoding")!=header.end()) accept_encoding = header["Accept-Encoding"];
            if(header.find("Accept-Language")!=header.end()) accept_language = header["Accept-Language"];
            if(header.find("Cache-Control")!=header.end()) cache_control = header["Cache-Control"];
            if(header.find("Cookie")!=header.end()) cookie = header["Cookie"];
            if(header.find("Host")!=header.end()) host = header["Host"];
            if(header.find("Referer")!=header.end()) referer = header["Referer"];
            if(header.find("User-Agent")!=header.end()) user_agent = header["User-Agent"];

        }
    };
}