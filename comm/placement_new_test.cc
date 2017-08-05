#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    char str[]="123";
    std::string* raw = new std::string(BUFSIZ,'\0');
    std::string* pstr = new(raw)std::string(str);
    std::cout<<*pstr<<std::endl;
    delete raw;
    return 0;
}
