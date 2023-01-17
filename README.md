# drogon-boilerplate
C++ Boilerplate starter for Drogon framework-based websevice

1. Install all Drogon framework pre-requisites for your system. See: https://github.com/drogonframework/drogon/wiki/ENG-02-Installation


2. Retrieve sourcecode, including [Drogon](https://github.com/drogonframework/drogon) (as /lib/drogon submodule) and it's own dependencies (including [Trantor](https://github.com/an-tao/trantor) library submodule)


    git submodule update --init --recursive
    

3. Build boilerplate webservice app


    mkdir build
    cd build
    cmake ..
    make


4. Run it


    ./build/drogon-boilerplate

    ./drogon-boilerplate 
    20230117 01:44:05.626137 UTC 3116317 INFO  Starting server on port 8090. Use: http://localhost:8090/api/v1/HelloWorld/ - main.cpp:5
    
5. Access API endpoint http://localhost:8090/api/v1/HelloWorld using any HTTP client or web-browser
You should see response JSON message:


    {"message":"Hello, World!"}

< The End >

# It's not the end, It's just the begninning
Now you're free to start your own journey and create high-performance webservices using Drogon framework assistance.