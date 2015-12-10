# Tutorial

## Brief Introduction
Safaia framework is designed for high performance and concurrency light web framework with C++. It's easy to use, test and deploy. 

This tutorial is based on version v0.1.3 alpha. 

## Getting Started
First off, you should clone the whole project to your own disk. To make this happen, open your Terminal, and type the following command.

`git clone https://github.com/dsh0416/safaia-framework.git`

Safaia framework use `CMake` to build the project. It's easy to find the `CMakeList.txt` file under the project directory. `CMake` is a powerful tool to build your project. You'd better learn how to use it [here](http://www.cmake.org/). IDEs like `CLion` could automatically manage and build with `CMake`.

Importantly, the minimum version to make this project is cmake 3.2. GCC 4.9 is what we supported compiler on Linux. The latest clang compiler could also compile the project on Linux what if you are using libc++ but not libstdc++. Both gcc and clang is supported and officially tested on Mac OS X. `travis.sh` is the building process we use to pass the `travis-ci`, it may be advisable if you have troubles when compiling and building the project.

After you build the server, you could just run the executive file.

Type `http://127.0.0.1:21411/` in your browser and you would see a `Hello World` page in your browser. We will later describe how it works in Safaia-framework.

## Hello World in Ten Lines
`main.cpp` is the entrance of the whole program with `int main()`. The default `main.cpp` gives some examples, you could delete them and create your own. Let's start your project with the following code.

```
#include "framework/safaia/Safaia.h"
using namespace Safaia;
int main(){
    auto server = Server();
    server.add_route("GET", "/", [](Req req){
        return Resp("Hello World");
    }));
    server.run();
    return 0;
}
```

## Route
In Safaia framework, a route definition includes two parts: HTTP method and a Url-Matching pattern.

```
server.add_route(Route("GET", "/", [](Req req){
    .. show something ..
}));
server.add_route(Route("POST", "/", [](Req req){
    .. create something ..
}));
server.add_route(Route("PUT", "/", [](Req req){
    .. replace something ..
}));
server.add_route(Route("PATCH", "/", [](Req req){
    .. modify something ..
}));
server.add_route(Route("DELETE", "/", [](Req req){
    .. annihilate something ..
}));
server.add_route(Route("OPTIONS", "/", [](Req req){
    .. appease something ..
}));
server.add_route(Route("LINK", "/", [](Req req){
    .. affiliate something ..
}));
server.add_route(Route("UNLINK", "/", [](Req req){
    .. separate something ..
}));
server.add_route(Route("WTF", "/", ](Req req){
    .. do what the f**k you want on something ..
}));
```

The first route that matches the request is invoked.
