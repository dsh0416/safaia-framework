/*
 * This is the log class of Safaia
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 30 Aug 2015
 * */

#ifndef SAFAIA_FRAMEWORK_LOG_H
#define SAFAIA_FRAMEWORK_LOG_H

#include <iostream>
#include <string>


class Log{
public:void info(std::string tag, std::string str){
        std::cout << "[Info] " << tag << ": "<< str << std::endl;
    }
public:void warning(std::string tag, std::string str){
        std::cout << "[Warning] " << tag << ": "<< str << std::endl;
    }
public:void error(std::string tag, std::string str){
        std::cout << "[Error] " << tag << ": "<< str << std::endl;
    }
};

#endif //SAFAIA_FRAMEWORK_LOG_H
