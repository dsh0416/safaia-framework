#include <iostream>
#include <string>
#include <regex>
#include <unistd.h>
#include <cstdio>
#include <cstring>

namespace Safaia{
    class Log{
        int is_stdout = isatty(fileno(stdout));
        const std::string str_reset = "\033[0m";
        const std::string str_green = "\033[32m";
        const std::string str_yellow = "\033[33m";
        const std::string str_red = "\033[1m\033[31m";

    public:
        bool ansi_color = true;
        int level = 3;

        Log(){
            // CLion still does not support ASCII color control, disable the feature by default
            char * env = getenv("XPC_SERVICE_NAME");
            if (env != NULL){
                if (std::regex_match(std::string(env), std::regex("(.*)(clion)(.*)")))
                    ansi_color = false;
            }
        }

        void info(std::string tag, std::string str){
            if (level > 2){
                std::string str_log = (((ansi_color && is_stdout) ? str_green : "") + "[Info] " + tag + ": " + str + ((ansi_color && is_stdout) ? str_reset : ""));
                printf("%s\n", str_log.c_str());
            }

        }
        void warning(std::string tag, std::string str){
            if (level > 1){
                std::string str_log = (((ansi_color && is_stdout) ? str_yellow : "") + "[Warning] " + tag + ": " + str + ((ansi_color && is_stdout) ? str_reset : ""));
                printf("%s\n", str_log.c_str());
            }
        }
        void error(std::string tag, std::string str){
            if (level > 0){
                std::string str_log = (((ansi_color && is_stdout) ? str_red : "") + "[Error] " + tag + ": " + str + ((ansi_color && is_stdout) ? str_reset : ""));
                printf("%s\n", str_log.c_str());
            }
        }
    };
}