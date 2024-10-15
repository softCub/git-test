#include <cstddef>
#include <iostream>
#include <chrono>
#include <system_error>
#include <thread>

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include<asio/ts/internet.hpp>

std::vector<char> vBuffer(20*1024);
void getdata(asio::ip::tcp::socket& socket){
    socket.async_read_some(asio::buffer(vBuffer.data(),vBuffer.size()),
    [&](std::error_code ec ,std::size_t length){
        if(!ec){
            std::cout<<length<<" Bites\n\n";

            for(int i=0;i<vBuffer.size();i++)std::cout<<vBuffer[i];
            getdata(socket);
           

        }
    });

}


int main(){
 asio::error_code ec;

 asio::io_context context;

 asio::io_context::work idleWork(context);

 std::thread thrContext = std::thread([&](){context.run();});

 asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34",ec),80);

 asio::ip::tcp::socket socket(context);

socket.connect(endpoint, ec);


 if(!ec){ std::cout<<"connected"<<std::endl;}
 else{
    std::cout<<"failed to connect to address"<<ec.message()<<std::endl;
 }

      if(socket.is_open())   {
        getdata(socket);
        std::string sRequest=
        "GET /index.html HTTP/1.1\r\n"
        "Host:example.com\r\n"
        "Connection:close\r\n\r\n";

        socket.write_some(asio::buffer(sRequest.data(),sRequest.size()),ec);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2000ms);

       context.stop();
       if(thrContext.joinable())thrContext.join();

 }

}
