#define RESET "\033[0m"
#define GREEN "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define RED "\033[1m\033[31m" /* Bold Red */

#include <iostream>
#include <string>


class Log{
public:

    bool ansi_color = true;

    void info(std::string tag, std::string str){
        std::cout << (ansi_color ? GREEN : "") << "[Info] " << tag << ": "<< str << (ansi_color ? RESET : "") << std::endl;
    }
    void warning(std::string tag, std::string str){
        std::cout << (ansi_color ? YELLOW : "") <<"[Warning] " << tag << ": "<< str << (ansi_color ? RESET : "") << std::endl;
    }
    void error(std::string tag, std::string str){
        std::cerr << (ansi_color ? RED : "") << "[Error] " << tag << ": "<< str << (ansi_color ? RESET : "") << std::endl;
    }
};