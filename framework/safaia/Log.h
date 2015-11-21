#define RESET "\033[0m"
#define GREEN "\033[32m" // Green
#define YELLOW "\033[33m" // Yellow
#define RED "\033[1m\033[31m" // Bold Red

#include <iostream>
#include <string>
#include <regex>
#include <unistd.h>
#include <cstdio>

namespace Safaia{
    class Log{
        int is_stdout = isatty(fileno(stdout));

    public:
        bool ansi_color = true;
        int level = 3;

        Log(){
            // CLion still does not support ASCII color control, disable the feature by default
            if (std::regex_match(std::string(getenv("XPC_SERVICE_NAME")), std::regex("(.*)(CLion)(.*)")))
                ansi_color = false;
        }

        void info(std::string tag, std::string str){
            if (level > 2) {
                if (ansi_color && is_stdout) {
                    printf(GREEN);
                }
                printf("[Info] %s: %s", tag.c_str(), str.c_str());
                if (ansi_color && is_stdout) {
                    printf(RESET);
                }
                printf("\n");
            }
        }
        void warning(std::string tag, std::string str){
            if (level > 1) {
                if (ansi_color && is_stdout) {
                    printf(YELLOW);
                }
                printf("[Warning] %s: %s", tag.c_str(), str.c_str());
                if (ansi_color && is_stdout) {
                    printf(RESET);
                }
                printf("\n");
            }
        }
        void error(std::string tag, std::string str){
            if (level > 1) {
                if (ansi_color && is_stdout) {
                    printf(RED);
                }
                printf("[Error] %s: %s", tag.c_str(), str.c_str());
                if (ansi_color && is_stdout) {
                    printf(RESET);
                }
                printf("\n");
            }
        }
    };
}