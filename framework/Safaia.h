/*
 * This is the main class of Safaia
 * Created By Delton Ding (dsh0416@gmail.com)
 * Create Time: 30 Aug 2015
 * Last Edited Time: 31 Aug 2015
 * */

#include <iostream>
#include <vector>
#include <queue>
#include "Log.h"
#include "Route.h"
#include "Ecp.h"
#include <sys/socket.h>

#ifndef SAFAIA_FRAMEWORK_SAFAIA_H
#define SAFAIA_FRAMEWORK_SAFAIA_H

namespace Safaia{

    class Server {

        bool soft_stop = false;
        std::vector<Route> vec_routes;
        std::queue<Req> que_reqs;

        // IO Loop
        void loop(){

        }

    public:
        Log log = Log();
        int port = 21411;
        int thread = 4;

        Server(){

        }

        // Route Definition
        void add_route(Route route){
            vec_routes.push_back(route);
        }

        // Start running the server
        void run(){
            // Initializing
            log.info("Server","Safaia server is initializing");

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
