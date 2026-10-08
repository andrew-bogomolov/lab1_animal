#include "Animal.h"

Animal::Animal()
    : breed_(""), color_("")
{
    std::cout << "Animal: constructor." << std::endl;
}

Animal::Animal(const std::string& breed, const std::string& color)
    : breed_(breed), color_(color)
{
    std::cout << "Animal: constructor with param." << std::endl;
}

Animal::Animal(const Animal& other)
    : breed_(other.breed_), color_(other.color_)
{
    std::cout << "Animal: constructor copy." << std::endl;
}

Animal::~Animal()
{
    std::cout << "Animal: destructor." << std::endl;
}

std::string Animal::getBreed()
{
    return breed_;
}

std::string Animal::getColor()
{
    return color_;
}

void Animal::setBreed(const std::string& breed)
{
    breed_ = breed;
}

void Animal::setColor(const std::string& color)
{
    color_ = color;
}
