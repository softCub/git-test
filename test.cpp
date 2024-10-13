#include <iostream>

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include<asio/ts/internet.hpp>

int main(){
std::cout<<"hi";
 asio::error_code ec;

 asio::io_context context;

 asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.36",ec),80);

 asio::ip::tcp::socket scoket(context);

 if(!ec) std::cout<<"connected"<<std::endl;
 else{
    std::cout<<"failed to connect to address"<<ec.message()<<std::endl;

 }
}
