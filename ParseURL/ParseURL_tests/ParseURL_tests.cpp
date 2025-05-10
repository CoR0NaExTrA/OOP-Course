#define CATCH_CONFIG_MAIN
#include "../../../Catch/catch.hpp"
#include "../ParseURL/ParseURL.h"

TEST_CASE("Valid URLs", "[ParseURL]") {
    Protocol protocol;
    int port;
    std::string host, document;

    SECTION("HTTP without port and document") {
        REQUIRE(ParseURL("http://example.com", protocol, port, host, document));
        REQUIRE(protocol == Protocol::HTTP);
        REQUIRE(port == 80);
        REQUIRE(host == "example.com");
        REQUIRE(document.empty());
    }

    SECTION("HTTPS with port and document") {
        REQUIRE(ParseURL("https://secure.com:443/index.html", protocol, port, host, document));
        REQUIRE(protocol == Protocol::HTTPS);
        REQUIRE(port == 443);
        REQUIRE(host == "secure.com");
        REQUIRE(document == "index.html");
    }

    SECTION("FTP with default port and document") {
        REQUIRE(ParseURL("ftp://ftpserver.com/docs/manual.pdf", protocol, port, host, document));
        REQUIRE(protocol == Protocol::FTP);
        REQUIRE(port == 21);
        REQUIRE(host == "ftpserver.com");
        REQUIRE(document == "docs/manual.pdf");
    }

    SECTION("HTTP with custom port and document") {
        REQUIRE(ParseURL("http://my.site:8080/page.html", protocol, port, host, document));
        REQUIRE(protocol == Protocol::HTTP);
        REQUIRE(port == 8080);
        REQUIRE(host == "my.site");
        REQUIRE(document == "page.html");
    }

    SECTION("HTTP with max valid port") {
        REQUIRE(ParseURL("http://maxport.com:65535", protocol, port, host, document));
        REQUIRE(protocol == Protocol::HTTP);
        REQUIRE(port == 65535);
        REQUIRE(host == "maxport.com");
        REQUIRE(document.empty());
    }

    SECTION("HTTP with min valid port") {
        REQUIRE(ParseURL("http://minport.com:1", protocol, port, host, document));
        REQUIRE(protocol == Protocol::HTTP);
        REQUIRE(port == 1);
        REQUIRE(host == "minport.com");
        REQUIRE(document.empty());
    }
}

TEST_CASE("Invalid URLs", "[ParseURL]") {
    Protocol protocol;
    int port;
    std::string host, document;

    SECTION("Invalid protocol") {
        REQUIRE_FALSE(ParseURL("htp://invalid.com", protocol, port, host, document));
    }

    SECTION("Missing protocol") {
        REQUIRE_FALSE(ParseURL("//example.com", protocol, port, host, document));
    }

    SECTION("Empty host") {
        REQUIRE_FALSE(ParseURL("http://", protocol, port, host, document));
    }

    SECTION("Invalid port (non-numeric)") {
        REQUIRE_FALSE(ParseURL("http://example.com:abcd", protocol, port, host, document));
    }

    SECTION("Invalid port (out of range: 0)") {
        REQUIRE_FALSE(ParseURL("http://example.com:0", protocol, port, host, document));
    }

    SECTION("Invalid port (out of range: 65536)") {
        REQUIRE_FALSE(ParseURL("http://example.com:65536", protocol, port, host, document));
    }

    SECTION("Invalid port (negative)") {
        REQUIRE_FALSE(ParseURL("http://example.com:-1", protocol, port, host, document));
    }
}


