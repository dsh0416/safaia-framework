#include <iostream>
#include <vector>
#include <queue>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <future>
#include <unistd.h>
#include <ctime>
#include <iomanip>
#include <sstream>
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
        static void serve(int sockfd, Log &log, bool &soft_stop, std::vector<Route> &vec_routes, Resp &not_found){
            int fd;
            int size = (int)vec_routes.size();

            while (!soft_stop){
                fd = accept(sockfd, NULL, NULL);
                char buf[BUF_LEN];
                read(fd, buf, BUF_LEN);
                bool has_found = false;

                Req req = Req(std::string(buf));

                for(int i = 0; i < size; i++){
                    if ((!vec_routes[i].is_regex && vec_routes[i].method == req.method && vec_routes[i].path == req.request_url) ||
                        (vec_routes[i].is_regex && vec_routes[i].method == req.method && std::regex_match(req.request_url, vec_routes[i].regex_path))){
                        Resp response = Resp(500, "500 Internal Error");

                        if(vec_routes[i].is_regex){
                            std::smatch regex_match;
                            std::regex_match(req.request_url, regex_match, vec_routes[i].regex_path);
                            for (size_t j = 0; j < regex_match.size(); j++) {
                                std::ssub_match sub_match = regex_match[j];
                                req.regex_result.push_back(sub_match.str());
                                // std::ssub_match could be convert to std::string with the .str() method in C++11 official documentation
                                // But clang++ may do nothing cause std::ssub_match could also implicit convert to std::string
                                // So that some IDE like CLion may incorrectly trust it as an error
                            }
                        }

                        try {
                            response = vec_routes[i].function(req);
                        }catch(std::exception& e) {
                            std::string err_message(e.what());
                            log.error("Handle", err_message);
                        }
                        std::string header = "HTTP/1.1 " + response.status_code +"\r\nContent-type: text/html\r\n\r\n";
                        std::string body = response.body;
                        write(fd, header.c_str(), header.length());
                        write(fd, body.c_str(), body.length());
                        close(fd);
                        has_found = true;

                        time_t t = time(0);
                        std::stringstream log_text;
                        std::string formatted_time = ctime(&t);
                        formatted_time = formatted_time.substr(0, formatted_time.length() - 1);
                        // std::put_time(std::localtime(&t) is recommended for formatting time,
                        // but <codecvt> is not involved in stdlibc++ with gcc 4.9,
                        // use ctime(&t) for compatibility temporarily.

                        log_text << "[" << formatted_time << "] \"" <<
                        req.method << " " << req.request_url << " " << req.protocol << "\" " << response.status_code;
                        log.info("Server", log_text.str());

                        break;
                    }
                }
                if (!has_found){
                    // No Matching, return 404
                    std::string header = "HTTP/1.1 " + not_found.status_code +"\r\nContent-type: text/html\r\n\r\n";
                    std::string body = not_found.body;
                    write(fd, header.c_str(), header.length());
                    write(fd, body.c_str(), body.length());
                    close(fd);

                    time_t t = time(0);
                    std::stringstream log_text;
                    std::string formatted_time = ctime(&t);
                    formatted_time = formatted_time.substr(0, formatted_time.length() - 1);
                    // std::put_time(std::localtime(&t) is recommended for formatting time,
                    // but <codecvt> is not involved in stdlibc++ with gcc 4.9,
                    // use ctime(&t) for compatibility temporarily.

                    log_text << "[" << formatted_time << "] \"" <<
                    req.method << " " << req.request_url << " " << req.protocol << "\" " << "404 Not Found";
                    log.info("Server", log_text.str());
                }
            }

        }

        // IO Loop
        void loop(){
            std::vector<std::thread> threads;
            for (int i = 0; i < thread; i++){
                threads.push_back(std::thread(serve, std::ref(sockfd), std::ref(logger), std::ref(soft_stop), std::ref(vec_routes), std::ref(not_found)));
            }
            for (int i = 0; i < thread; i++){
                threads[i].join();
            }

        }

    public:
        int port = 21411;
        int thread = 4;

        Resp not_found = Resp(404, "404 Not Found");

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
            logger.info("Server","safaia-framework v0.1.3 alpha");
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