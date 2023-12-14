#include "request.hpp"

void    request::set_body(std::string req)
{
    this->body = req.substr(req.find(BODY_SEPARATOR) + strlen(BODY_SEPARATOR));
    req = req.substr(0, req.find(BODY_SEPARATOR));
    this->method = req.substr(0, req.find(' '));
    req = req.substr(req.find(' ') + 1);
    this->path = req.substr(0, req.find(' '));
    req = req.substr(req.find(' ') + 1);
    this->version = req.substr(0, req.find(' '));
    req = req.substr(req.find(LINE_SEPARATOR) + strlen(LINE_SEPARATOR));
    std::cout<<req<<std::endl;
    while (!req.empty())
    {
        this->headers[req.substr(0, req.find(HEDER_SEPARATOR))] = req.substr(req.find(HEDER_SEPARATOR) + 2, req.find(LINE_SEPARATOR) - req.find(HEDER_SEPARATOR) - 3);
        if (req.find(LINE_SEPARATOR) == std::string::npos)
            req = "";
        else
            req = req.substr(req.find(LINE_SEPARATOR) + strlen(LINE_SEPARATOR));
    }
}

std::string request::get_metohd() const
{
    return (this->method);
}

std::string request::get_path() const
{
    return (this->path);
}

std::string request::get_version() const
{
    return (this->version);
}

std::string request::get_body() const
{
    return (this->body);
}