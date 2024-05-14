#include <iostream>
#include <memory>
#include <chrono>

using namespace std;

class Person
{
    int age;
    string pName;

public:
    Person() : pName(0), age(0)
    {
    }
    Person(string pName, int age) : pName(pName), age(age)
    {
    }
    ~Person()
    {
    }

    void Display()
    {
        cout << "name: " << pName << endl << "age: " << age << endl;
    }
    void Shout()
    {
        cout << "lmao" << endl;
    }
};

class RC
{
private:
    int count; // Reference count

public:
    void AddRef()
    {
        // Increment the reference count
        count++;
        cout << "plus: " << count << endl;
    }

    int Release()
    {
        // Decrement the reference count and
        // return the reference count.
        cout << "minus: " << count << endl;
        return --count;
    }
};

template < typename T > class Log_Ptr
{
private:
    T* pData;       // pointer
    RC* reference; // Reference count

public:
    Log_Ptr() : pData(0), reference(0)
    {
        // Create a new reference 
        reference = new RC();
        // Increment the reference count
        reference->AddRef();
    }

    Log_Ptr(T* pValue) : pData(pValue), reference(0)
    {
        // Create a new reference 
        reference = new RC();
        // Increment the reference count
        reference->AddRef();
    }

    Log_Ptr(const Log_Ptr<T>& sp) : pData(sp.pData), reference(sp.reference)
    {
        // Copy constructor
        // Copy the data and reference pointer
        // and increment the reference count
        reference->AddRef();
    }

    ~Log_Ptr()
    {
        auto timestamp = chrono::system_clock::now();
        cout << timestamp << endl;
        cout << this->operator->() << endl;

        // Destructor
        // Decrement the reference count
        // if reference become zero delete the data
        if (reference->Release() == 0)
        {
            delete pData;
            delete reference;
        }
    }

    T& operator* ()
    {
        return *pData;
    }

    T* operator-> ()
    {
        return pData;
    }

    Log_Ptr<T>& operator = (const Log_Ptr<T>& sp)
    {
        // Assignment operator
        if (this != &sp) // Avoid self assignment
        {
            // Decrement the old reference count
            // if reference become zero delete the old data
            if (reference->Release() == 0)
            {
                delete pData;
                delete reference;
            }

            // Copy the data and reference pointer
            // and increment the reference count
            pData = sp.pData;
            reference = sp.reference;
            reference->AddRef();
        }
        return *this;
    }
};

int main()
{
    Log_Ptr<Person> p(new Person("Scott", 25));
    p->Display();
    {
        Log_Ptr<Person> q = p;
        q->Display();
        // Destructor of q will be called here..

        Log_Ptr<Person> r;
        r = p;
        r->Display();
        // Destructor of r will be called here..
    }
    p->Display();
    return 0;
    // Destructor of p will be called here 
    // and person pointer will be deleted
}