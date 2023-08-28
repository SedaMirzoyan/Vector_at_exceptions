
#include <iostream>

class A
{
public:

    void init()
    {
        throw 23;
    }

    A()
    {
        std::cout << "Constructor\n";
        try
        {
            init();
        }
        catch (...)
        {
            std::cout << "error caught in constructor\n";
        }
    }

    ~A()
    {
        std::cout << "Destructor\n";
        try 
        {
            throw "5";
        }
        catch (...)
        {
            std::cout << "error caught in destructor\n";
        }
        
    }
};



int main()
{
    A ob;
    return 0;
}

