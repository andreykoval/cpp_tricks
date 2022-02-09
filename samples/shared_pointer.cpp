#include <iostream>

using namespace std;

class counter_sp
{
public:
    counter_sp() = default;
    ~counter_sp() = default;
    
    void operator++()
    {
        m_count++;
    }

    void operator++(int)
    {
        m_count++;
    }
    
    void operator--()
    {
        m_count--;
    }

    void operator--(int)
    {
        m_count--;
    }
    
    size_t get()
    {
        return m_count;
    }
    
private:
    size_t m_count{0};
};

template <class T>
class shared_pointer_c
{
public:
    shared_pointer_c(T* ptr = nullptr)
    {
        m_pointer = ptr;
        
        if (m_pointer)
        {
            m_counter = new counter_sp();
            (*m_counter)++;
        }
    }
    
    shared_pointer_c(const shared_pointer_c<T>& sp)
    {
        assign( sp );
    }
    
    ~shared_pointer_c()
    {
        decrease();
    }
    
    shared_pointer_c<T>& operator=(const shared_pointer_c<T>& sp)
    {
        if (m_pointer)
        {
           decrease();     
        }
        
        assign( sp );
        return *this;
    }
    
    T& operator*()
    {
        return *m_pointer;
    }
    
    T* operator->()
    {
        return m_pointer;
    }
    
private:
    void assign(const shared_pointer_c<T>& sp)
    {
        m_pointer = sp.m_pointer;
        m_counter = sp.m_counter;
        (*m_counter)++;
    }
    
    void decrease()
    {
        (*m_counter)--;
        if(m_counter->get() == 0)
        {
            delete m_counter;
            delete m_pointer;
        }
    }

private:
    T* m_pointer;
    counter_sp* m_counter;
};

class test_data
{
public:
    test_data(int id = 0): m_id(id){cout << "create test data id = " << m_id << endl;}
    ~test_data(){ cout << "destroy test data id = " << m_id << endl;}
private:
    int m_id;
};

int main()
{
    shared_pointer_c<test_data> delay_d;
    
    {
        shared_pointer_c<test_data> td1(new test_data(1));
        shared_pointer_c<test_data> td2(new test_data(2));
        delay_d = td1;
    }
    
    shared_pointer_c<test_data> td3(new test_data(3));
    
    //delay_d = td3;

    return 0;
}