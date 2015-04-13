/*
	Пример простой фабрики.
	Иерархия классов может конструироваться только через метод createTemplate(),
	метод возвращает shared_ptr на созданный объект, поэтому, утечек не будет.
	!!! Это только самая базовая реализация которая только показывает идею !!!
*/

// string::find
#include <iostream>       			// std::cout
#include <boost/shared_ptr.hpp>

template <class RetType>
class VirtualConstructor
{
protected:
    VirtualConstructor(){};

public:
    virtual ~VirtualConstructor(){};
        
    template <class TypeTemplate>
    static boost::shared_ptr<RetType> createTemplate()             //Virtual constructor
    {
        return boost::shared_ptr<RetType>(new TypeTemplate());
    }
};

class ITemplate : public VirtualConstructor<ITemplate>
{
public:
    ITemplate() {}
    
public:
    virtual ~ITemplate() {}
       
    virtual void print() = 0;
};

typedef boost::shared_ptr<ITemplate> TemplatePtr;

class Receipt : public ITemplate
{
public:
	Receipt(){}

	virtual ~Receipt()
	{
		std::cout << "~Receipt()" << std::endl;    
	}
        
    virtual void print()
    {
        std::cout << "Receipt" <<std::endl;
    }
};

class StateSettelm : public ITemplate
{
public:
	StateSettelm(){}

	virtual ~StateSettelm()
	{
		std::cout << "~StateSettelm()" << std::endl;    
	}
        
    virtual void print()
    {
        std::cout << "StateSettelm" <<std::endl;
    }
};

int main ()
{
    
	TemplatePtr templatePtr = ITemplate::createTemplate<StateSettelm>();
	templatePtr->print();

	templatePtr = ITemplate::createTemplate<Receipt>();
	templatePtr->print();

	return 0;
}
