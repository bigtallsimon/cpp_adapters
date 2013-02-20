#include <string>
#include <iostream>
#include <typeinfo>
#include <map>
#include <utility>
#include <sstream>
using namespace std;

#include "adapter_factory.h"
map<pair<type_info const *, type_info const *>, IAdapterFactory *> type2adapterfactory;

#include "adapt.h"


class Person
{
public:
    Person(string name, unsigned int age) { _name = name; _age = age; }
    unsigned int get_age() const { return _age; }
    string const & get_name() const { return _name; }
private:
    int _age;
    string _name;
};


class Dog
{
public:
    Dog(string breed, string colour) { _breed = breed, _colour = colour; }
    string const & get_breed() const { return _breed; }
    string const & get_colour() const { return _colour; }
private:
    string _breed;
    string _colour;
};


class IHasDescription
{
public:
    virtual ~IHasDescription() {}
public:
    virtual string get_description() =0;
};




class PersonToIHasDescriptionAdapter : public IHasDescription
{
public:
    PersonToIHasDescriptionAdapter(Person * adaptee) { _adaptee = adaptee; }

    virtual string get_description()
    {
        stringstream ss;
        ss << _adaptee->get_name() << " aged " << _adaptee->get_age();
        return ss.str();
    }
private:
    Person * _adaptee;
};
static int dummy1 = adapts<PersonToIHasDescriptionAdapter, Person, IHasDescription>();

class DogToIHasDescriptionAdapter : public IHasDescription
{
public:
    DogToIHasDescriptionAdapter(Dog * adaptee) { _adaptee = adaptee; }

    virtual string get_description()
    {
        return string("A ") + _adaptee->get_colour() + " " + _adaptee->get_breed();
    }
private:
    Dog * _adaptee;
};
static int dummy2 = adapts<DogToIHasDescriptionAdapter, Dog, IHasDescription>();



int main(int argc, char const ** argv)
{
    Person p("Fred", 42);
    Dog d("Labrador", "Black");
    IHasDescription *p_as_i = adapt<IHasDescription>(&p);
    IHasDescription *d_as_i = adapt<IHasDescription>(&d);
    cout << "Person: " << p_as_i->get_description() << endl;
    cout << "Dog: " << d_as_i->get_description() << endl;
    delete p_as_i;
    delete d_as_i;
    return 0;
}
