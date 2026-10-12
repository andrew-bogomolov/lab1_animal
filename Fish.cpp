#include "Fish.h"

#include <limits>
#include <stdexcept>

Fish::Fish()
    : Animal(), feedingType_("")
{
    std::cout << "Fish: constructor."   << std::endl;
}

Fish::Fish(const std::string& breed, const std::string& color,const std::string& feedingType)
    : Animal(breed, color), feedingType_(feedingType)
{
    std::cout << "Fish: constructor with param."  << std::endl;
}

Fish::Fish(const Fish& other)
    : Animal(other), feedingType_(other.feedingType_)
{
    std::cout << "Fish: constructor copy." << std::endl;
}

Fish& Fish::operator=(const Fish& other)
{
    if (this != &other)
    {
        setBreed(other.getBreed());
        setColor(other.getColor());
        feedingType_ = other.feedingType_;
    }

    std::cout << "Fish: operator prisv." << std::endl;

    return *this;
}

Fish::~Fish()
{
    std::cout << "Fish: destructor." << std::endl;
}

std::string Fish::getFeedingType() const
{
    return feedingType_;
}

void Fish::setFeedingType(const std::string& feedingType)
{
    if (feedingType.empty())
    {
        throw std::invalid_argument("FeedingType cant empty." );
    }

    feedingType_ = feedingType;
}

void Fish::print() const
{
    std::cout << "\nInfo Fish\n";
    std::cout << "Type: Fish\n";
    std::cout << "Breed: " << getBreed() << '\n';
    std::cout << "Color: " << getColor() << '\n';
    std::cout << "FeedingType: " << feedingType_ << '\n';
}

void Fish::input()
{
    std::string breed;
    std::string color;
    std::string feedingType;

    std::cout << "Input breed: ";
    if (!std::getline(std::cin, breed))
    {
        throw std::runtime_error("error runtime breed." );
    }

    if (breed.empty())
    {
        throw std::invalid_argument("breed cant empty." );
    }

    std::cout << "Input color: ";
    if (!std::getline(std::cin, color))
    {
        throw std::runtime_error("error runtime color.");
    }

    if (color.empty())
    {
        throw std::invalid_argument("color cant empty.");
    }

    std::cout << "Input feedingType: ";
    if (!std::getline(std::cin, feedingType))
    {
        throw std::runtime_error("error runtime feed.");
    }

    if (feedingType.empty())
    {
        throw std::invalid_argument("feed cant empty.");
    }

    setBreed(breed);
    setColor(color);
    setFeedingType(feedingType);
}

void Fish::save(std::ostream& out) const
{
    out << getBreed() << '\n';
    out << getColor() << '\n';
    out << feedingType_ << '\n';

    if (!out)
    {
        throw std::runtime_error("error save." );
    }
}

void Fish::load(std::istream& in)
{
    std::string breed;
    std::string color;
    std::string feedingType;

    if (!std::getline(in, breed) || !std::getline(in, color) || !std::getline(in, feedingType))
    {
        throw std::runtime_error("error load.");
    }

    if (breed.empty() || color.empty() || feedingType.empty())
    {
        throw std::invalid_argument("File is empty.");
    }

    setBreed(breed);
    setColor(color);
    setFeedingType(feedingType);
}

Fish* Fish::clone() const
{
    return new Fish(*this);
}

std::string Fish::getType() const
{
    return "Fish";
}
