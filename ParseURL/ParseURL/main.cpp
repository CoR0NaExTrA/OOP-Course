#include <iostream>
#include "ParseURL.h"

int main()
{
    std::string url;
    getline(std::cin, url);

    Protocol protocol;
    int port;
    std::string host, document;

    if (!ParseURL(url, protocol, port, host, document))
    {
        std::cout << "ERROR" << std::endl;
        return 0;
    }

    std::cout << url << std::endl;
    std::cout << "HOST: " << host << std::endl;
    std::cout << "PORT: " << port << std::endl;
    std::cout << "DOC: " << document << std::endl;

    return 0;
}
