#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>

class Animal
{
private:
    std::string bread_;
    std::string color_;

public:
    Animal();
    Animal(const std::string& breed, const std::string& color);
    Animal(const Animal& other);
    ~Animal();

    std::string getBreed();
    std::string getColor();

    void setBreed(const std::string& breed);
    void setColor(const std::string& color);

    virtual void print() const;
    virtual void input() = 0;

    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;

    virtual Animal* clone() const;

    virtual std::string getType() const = 0;
};

#endif
