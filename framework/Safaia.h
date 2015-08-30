/*
 * This is the main class of Safaia
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 30 Aug 2015
 * */

#include <iostream>
#include <vector>
#include <queue>
#include "Log.h"
#include "Route.h"
#include <sys/socket.h>

#ifndef SAFAIA_FRAMEWORK_SAFAIA_H
#define SAFAIA_FRAMEWORK_SAFAIA_H

namespace Safaia{

    class Server {

        Log log = Log();

        bool configured = false;
        bool soft_stop = false;
        int port;
        int max_connection;
        std::vector<Route> vec_routes;
        std::queue<Request> que_reqs;

        // Server configuration
        void config(int port, int max_connection){
            this->port = port;
            if (port < 0 || port > 65535) {
                log.error("Config", "Port out of range");
                return;
            }
            this->max_connection = max_connection;
            this->configured = true;
        }

        // IO Loop
        void loop(){

        }

    public:

        Server(int port, int max_connection){
            config(port,max_connection);
        }

        // Route Definition
        void add_route(Route route){
            vec_routes.push_back(route);
        }

        // Start running the server
        void run(){
            // Initializing
            log.info("Server","Safaia server is initializing");
            if (!configured){
                log.error("Config","No Config Detected");
                log.error("Server","Initialization Failed");
                return;
            }

            // Server started
            log.info("Server","Safaia server has started");
            while (!soft_stop){
                //IO Loop
                loop();
            }
            log.info("Server","Safaia server has stopped");
        }

        // Soft Stop running the server
        void stop(){
            soft_stop = true;
            log.info("Server","Safaia server is stopping");
        }

        // Hard Stop running the server
        void stop_force(){
            log.warning("Server","Safaia server force stopping");
            delete(this);
        }

    };
}

#endif //SAFAIA_FRAMEWORK_SAFAIA_H
