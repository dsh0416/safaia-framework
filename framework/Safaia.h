/*
 * This is the main class of Safaia
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 30 Aug 2015
 * */
#include <iostream>
#include "Log.h"

#ifndef SAFAIA_FRAMEWORK_SAFAIA_H
#define SAFAIA_FRAMEWORK_SAFAIA_H


class Safaia {

    Log log;

    bool configured = false;
    int port;
    int max_connection;

public:

    Safaia(int port, int max_connection){
        config(port,max_connection);
    }

    // Server configuration
    void config(int port, int max_connection){
        this->port = port;
        this->max_connection = max_connection;
        this->configured = true;
    }

    // Start running the server
    void run(){
        // Initializing
        log.info("Initial","Safaia server is initializing");
        if (!configured){
            log.error("Config","No Config Detected");
            return;
        }
    }

    // Stop running the server
    void stop(){

    }

};


#endif //SAFAIA_FRAMEWORK_SAFAIA_H
