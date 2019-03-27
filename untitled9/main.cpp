#include <QCoreApplication>

#include <iostream>
#include "tratadivporzero.h"

#include <cstdlib>
#include <exception>

#include <new>

void doSomeStuff()
{
    for(int i=0;i<10000;i++)
    {
        for(int j=0;j<100000;j++){}
    }
}

void handlerToNew()
{
    std::cout << "Memory allocation failed, terminating\n";
    std::set_new_handler(nullptr);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int b;
    float c;
    double d;
    std::string e;
    TrataDivPorZero div;

    try
    {
        throw b;
    }
    catch (int inteiro)
    {
        std::cout << "int was thrown and captured" << std::endl;
        std::cout.flush();
    }

    try
    {
        throw c;
    }
    catch (float unica)
    {
        std::cout << "float was thrown and captured" << std::endl;
        std::cout.flush();
    }

    try
    {
        throw d;
    }
    catch (double duplaprec)
    {
        std::cout << "double was thrown and captured" << std::endl;
        std::cout.flush();
    }

    try
    {
        throw e;
    }
    catch (std::string s)
    {
        std::cout << "std::string was thrown and captured" << std::endl;
        std::cout.flush();
    }

    try
    {
        throw div;
    }
    catch (TrataDivPorZero div)
    {
        std::cout << "TrataDivPorZero was thrown and captured" << std::endl;
        std::cout.flush();
    }

    try
    {
        throw div;
    }
    catch (...)
    {
        std::cout << "Some exception was thrown and captured" << std::endl;
        std::cout.flush();
    }

    //Configurando um handler para quando uma excessão ão for tratada
    //std::set_terminate([](){ std::cout << "Unhandled exception\n"; std::abort();});
    std::set_terminate([](){ std::cout << "Unhandled exception\n"; });
    //std::set_unexpected([](){ std::cout << "Unhandled exception\n"; });
    //std::set_new_handler(handlerToNew);

    //It does the same of std::set_terminate, but it was removed in c++17
    //set_unexpected( std::unexpected_handler f )

    //Do some stuff
    doSomeStuff();

    //this will trigger the handler of std::set_terminate
    //because there is not a handler to it
    //throw 1;

    //No caso abaixo, não será chamado set::terminate, pois tem try-catch
    //In the case below, it will not call set::terminate, becasuse there is a try-catch
    try {
        throw 1;
    } catch (...)
    {
        std::cout << "Captured exception of no handler" << std::endl;
    }{}

    /*try {
        while (true)
        {
            new int[100000000ul];
        }
    } catch (...)
    {
        std::cout << "Captured exception bad alloc" << std::endl;
    }{}*/

    //Se for aqui, executa o handler e termina
    //If th code belowget executed, it will call the handler and finish the code
    /*while (true)
    {
        new int[100000000ul];
    }*/

    std::cout << "End of code" << std::endl;

    return a.exec();
}
