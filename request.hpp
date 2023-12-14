#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <cstring>
#include <map>

#define BODY_SEPARATOR "\r\n\r\n"
#define LINE_SEPARATOR "\r\n"
#define HEDER_SEPARATOR ":"

class   request
{
private:
    std::string                         method;
    std::string                         path;
    std::string                         version;
    std::map<std::string, std::string>  headers;
    std::string                         body;
public:
    void    set_body(std::string req);
    std::string get_metohd() const;
    std::string get_path() const;
    std::string get_version() const;
    std::string get_body() const;
};

#endif