#include "http_tcp_server.h"

int main()
{
    http::TcpServer server("0.0.0.0", 8080);
    server.startListening();

    return 0;
}
