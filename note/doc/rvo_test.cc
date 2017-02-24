#include <iostream>


class RVO{
    public:
        RVO(int n)
            :n_(n)
        {
            std::cout<<"construct called...\n";
        }

        RVO(const RVO & rhs)
        {
            n_ = rhs.n_;
            std::cout<<"construct called...\n";

        }

        ~RVO()
        {
            std::cout<<"deconstruct called...\n";
        }


    private:
        int n_;
};


class RVOTest{
    public:
        RVOTest():rvo_(10){}

        const RVO rvo()const{return rvo_;} // 返回局部变量,复制一次
    private:
        RVO rvo_;

};


int main(int argc, char *argv[])
{
    RVOTest t;
    t.rvo();
    return 0;
}
