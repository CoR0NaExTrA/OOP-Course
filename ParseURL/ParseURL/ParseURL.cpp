#include "ParseURL.h"
#include <regex>
#include <unordered_map>

const std::unordered_map<std::string, Protocol> PROTOCOL_MAP = {
    {"http", Protocol::HTTP},
    {"https", Protocol::HTTPS},
    {"ftp", Protocol::FTP}
};

const std::unordered_map<Protocol, int> DEFAULT_PORT = {
    {Protocol::HTTP, 80},
    {Protocol::HTTPS, 443},
    {Protocol::FTP, 21}
};

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
    std::regex urlRegex(R"(^([a-zA-Z]+)://([^/:]+)(?::(\d+))?(?:/(.*))?$)");
    std::smatch matches;

    if (!regex_match(url, matches, urlRegex))
    {
        return false;
    }

    std::string protocolStr = matches[1].str();
    std::string hostStr = matches[2].str();
    std::string portStr = matches[3].str();
    std::string documentStr = matches[4].str();

    for (auto& c : protocolStr)
    {
        c = tolower(c);
    }

    if (PROTOCOL_MAP.find(protocolStr) == PROTOCOL_MAP.end())
    {
        return false;
    }

    protocol = PROTOCOL_MAP.at(protocolStr);
    host = hostStr;
    document = documentStr;

    if (!portStr.empty())
    {
        try
        {
            int portNum = stoi(portStr);
            if (portNum < 1 || portNum > 65535)
            {
                return false;
            }
            port = portNum;
        }
        catch (...)
        {
            return false;
        }
    }
    else
    {
        port = DEFAULT_PORT.at(protocol);
    }

    return true;
}