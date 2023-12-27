#ifndef POST_HPP
#define POST_HPP

#include <iostream>

class request
{
private:
    std::string body;
public:
    void    set_body(std::string b)
    {
        this->body = b;
    }
    std::string get_body() const
    {
        return (this->body);
    }
};

class post
{
private:
    std::string file_name;
    // void    create_file_name();
    size_t      chunked_size;
    std::string rest;
public:
    post(){this->chunked_size = 0;}
    void    _post(request req);
    void    chunked(request req)
    {
        size_t      hex_end;

        this->rest += req.get_body();
        req.set_body("");
        if (this->chunked_size == 0)
        {
            hex_end = this->rest.find("\r\n");
            if (hex_end == std::string::npos) //"\r\n" not found
            {
                if (this->rest.length() >= 16) // hexdecemal number too long
                    throw (400);
                return ;
            }
            std::string n = this->rest.substr(0, hex_end);
            for (int i = 0; n[i];i++)
                if (!std::isdigit(n[i]))
                    throw (300);
            this->chunked_size = std::stoi(n);
            if (this->chunked_size == 0)
                return ;
            this->rest = this->rest.substr(hex_end + 2);
        }
        if (this->chunked_size > this->rest.length()/*important ==>'\0' inside buffer*/)
        {
            std::cout<<"|"<<this->rest<<"|";
            this->chunked_size -= this->rest.length();
            this->rest = "";
        }
        else
        {
            std::cout<<this->rest.substr(0, this->chunked_size);
            this->rest = this->rest.substr(this->chunked_size + 2);
            this->chunked_size = 0;
            this->chunked(req);
        }
    }
};

int main(void)
{
    request req;
    post    p;

    try
    {
        req.set_body("101010");
        p.chunked(req);
        req.set_body("1212");
        p.chunked(req);
        // std::cout<<"---------------"<<std::endl;
        req.set_body("4545");
        p.chunked(req);
        std::cout<<"rest =="<<p.rest<<"$"<<std::endl;
        // req.set_body("1");
        // p.chunked(req);
        // // std::cout<<"rest =="<<p.rest<<std::endl;
        // req.set_body("0\r\nelkama");
        // p.chunked(req);
        // req.set_body("lmoh");
        // p.chunked(req);
    }
    catch(int e)
    {
        std::cerr<<"error:" << e << '\n';
    }
    
}

#endif