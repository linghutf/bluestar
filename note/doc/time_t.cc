#include <iostream>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t t;
    time(&t);
    size_t n = (size_t)t;
    std::cout<<n<<std::endl;
    return 0;
}
