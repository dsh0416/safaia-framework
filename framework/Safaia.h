#include <iostream>
#include <vector>
#include <queue>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <future>
#include "Log.h"
#include "Route.h"
#include "Ecp.h"

#define BUF_LEN 1028

namespace Safaia{

    Log logger = Log();

    class Server {

        bool soft_stop = false;
        std::vector<Route> vec_routes;

        int sockfd, err;
        struct sockaddr_in addr;

        // TODO: Message Handle
        static void serve(int sockfd, Log &log, bool &soft_stop, std::vector<Route> &vec_routes){
            int fd;
            int size = (int)vec_routes.size();
            while (!soft_stop){
                fd = accept(sockfd, NULL, NULL);
                char buf[BUF_LEN];
                read(fd, buf, BUF_LEN);

                Req req = Req(std::string(buf));
                log.info("Server", "Received a Request\n" + std::string(buf));

                for(int i = 0; i < size; i++){
                    if (!vec_routes[i].is_regex && vec_routes[i].method == req.method && vec_routes[i].path == req.request_url){
                        std::string header = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
                        std::string content = vec_routes[i].function(req).content;
                        write(fd, header.c_str(), header.length());
                        write(fd, content.c_str(), content.length());
                        close(fd);
                    } else if (vec_routes[i].is_regex && vec_routes[i].method == req.method && std::regex_match(req.request_url, vec_routes[i].regex_path)) {
                        std::string header = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
                        std::string content = vec_routes[i].function(req).content;
                        write(fd, header.c_str(), header.length());
                        write(fd, content.c_str(), content.length());
                        close(fd);
                    }
                }
                // No Matching
                close(fd);
            }

        }

        // IO Loop
        void loop(){
            for (int i = 0; i < thread; i++){
                std::async(std::launch::async, serve, std::ref(sockfd), std::ref(logger), std::ref(soft_stop), std::ref(vec_routes));
            }
        }

    public:
        int port = 21411;
        int thread = 4;

        Server(){

        }

        // Route Definition
        void add_route(Route route){
            vec_routes.push_back(route);
        }

        void add_route(std::string method, std::string path, std::function<Safaia::Resp(Safaia::Req)> function){
            vec_routes.push_back(Route(method, path, function));
        }

        void add_route(std::string method, std::regex path, std::function<Safaia::Resp(Safaia::Req)> function){
            vec_routes.push_back(Route(method, path, function));
        }

        // Start running the server
        void run(){
            // Initializing
            logger.info("Server","safaia-framework v0.1 alpha");
            logger.info("Server","Safaia Server is initializing");

            // Establish TCP Socket
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0) {
                logger.error("Server", "Socket Creation Failed!");
                exit(0);
            } else {
                logger.info("Server", "Socket Creation Succeeded!");
            }

            if (thread < 1){
                logger.error("Server", "Thread Number Error!");
            }

            memset(&addr, 0, sizeof(addr));
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = INADDR_ANY;

            // Binding Address and Port
            if(bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in))){
                logger.error("Server", "Port Binding Failed at Port " + std::to_string(port));
                exit(0);
            } else {
                logger.info("Server", "Port Binding Succeeded!");
            }

            // Start Listening
            listen(sockfd, 128);

            // Server Started
            logger.info("Server","Safaia Server has Started at Port " + std::to_string(port));

            loop();

            logger.info("Server","Safaia Server has Stopped");
        }

        // Soft Stop running the server
        void stop(){
            soft_stop = true;
            logger.info("Server","Safaia Server is Stopping");
        }

        // Hard Stop running the server
        void stop_force(){
            logger.warning("Server","Safaia Server is Force Stopping");
            delete(this);
        }

    };
}