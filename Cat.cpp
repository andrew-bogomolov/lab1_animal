#include "Cat.h"
#include <stdexcept>

Cat::Cat(): Animal(), ownerFullName_(""), name_("")
{
    std::cout << "Cat: construcor."<< std::endl;
}

Cat::Cat(const std::string& breed,const std::string& color,const std::string& ownerFullName,const std::string& name)
    : Animal(breed, color), ownerFullName_(ownerFullName),name_(name)
{
    std::cout << "Cat: construcor with param."<< std::endl;
}

Cat::Cat(const Cat& other)
    : Animal(other),
    ownerFullName_(other.ownerFullName_),
    name_(other.name_)
{
    std::cout << "Cat: construcor copy."<< std::endl;
}

Cat& Cat::operator=(const Cat& other)
{
    if (this != &other)
    {
        setBreed(other.getBreed());
        setColor(other.getColor());

        ownerFullName_ = other.ownerFullName_;
        name_ = other.name_;
    }

    std::cout << "Cat: operator prisv." << std::endl;

    return *this;
}

Cat::~Cat()
{
    std::cout << "Cat: destrucor."<< std::endl;
}

std::string Cat::getOwnerFullName() const
{
    return ownerFullName_;
}

std::string Cat::getName() const
{
    return name_;
}

void Cat::setOwnerFullName(const std::string& ownerFullName)
{
    if (ownerFullName.empty())
    {
        throw std::invalid_argument("FullName cant empty.");
    }

    ownerFullName_ = ownerFullName;
}

void Cat::setName(const std::string& name)
{
    if (name.empty())
    {
        throw std::invalid_argument(
            "name cant empty."
        );
    }

    name_ = name;
}

void Cat::print() const
{
    std::cout << "\nInfo Cat\n";
    std::cout << "Type: Cat\n";
    std::cout << "Breed: " << getBreed() << '\n';
    std::cout << "Color: " << getColor() << '\n';
    std::cout << "FullNameOwner: " << ownerFullName_ << '\n';
    std::cout << "NameCat: " << name_ << '\n';
}

void Cat::input()
{
    std::string breed;
    std::string color;
    std::string ownerFullName;
    std::string name;

    std::cout << "Input breed cat: ";
    if (!std::getline(std::cin, breed))
    {
        throw std::runtime_error("error runtime breed cat.");
    }

    std::cout << "Input color cat: ";
    if (!std::getline(std::cin, color))
    {
        throw std::runtime_error("error runtime color cat.");
    }

    std::cout << "Input ownerFullName: ";
    if (!std::getline(std::cin, ownerFullName))
    {
        throw std::runtime_error("error runtime fullname.");
    }

    std::cout << "Input name cat: ";
    if (!std::getline(std::cin, name))
    {
        throw std::runtime_error("error runtime name cat.");
    }

    if (breed.empty() || color.empty() ||ownerFullName.empty() || name.empty())
    {
        throw std::invalid_argument("should not empty cat.");
    }

    setBreed(breed);
    setColor(color);
    setOwnerFullName(ownerFullName);
    setName(name);
}

void Cat::save(std::ostream& out) const
{
    out << getBreed() << '\n';
    out << getColor() << '\n';
    out << ownerFullName_ << '\n';
    out << name_ << '\n';

    if (!out)
    {
        throw std::runtime_error("error save cat.");
    }
}

void Cat::load(std::istream& in)
{
    std::string breed;
    std::string color;
    std::string ownerFullName;
    std::string name;

    if (!std::getline(in, breed) || !std::getline(in, color) || !std::getline(in, ownerFullName) ||!std::getline(in, name))
    {
        throw std::runtime_error("error load cat.");
    }

    if (breed.empty() || color.empty() ||ownerFullName.empty() || name.empty())
    {
        throw std::invalid_argument( "File is empty cat.");
    }

    setBreed(breed);
    setColor(color);
    setOwnerFullName(ownerFullName);
    setName(name);
}

Cat* Cat::clone() const
{
    return new Cat(*this);
}

std::string Cat::getType() const
{
    return "Cat";
}
