#include "Bird.h"
#include <stdexcept>

Bird::Bird()
    : Animal(), feedingType_(""), habitat_("")
{
    std::cout << "Bird: construcor."<< std::endl;
}

Bird::Bird(const std::string& breed,const std::string& color,const std::string& feedingType,const std::string& habitat)
    : Animal(breed, color), feedingType_(feedingType), habitat_(habitat)
{
    std::cout << "Bird: construcor with param."<< std::endl;
}

Bird::Bird(const Bird& other)
    : Animal(other),
    feedingType_(other.feedingType_),
    habitat_(other.habitat_)
{
    std::cout << "Bird: construcor copy." << std::endl;
}

Bird& Bird::operator=(const Bird& other)
{
    if (this != &other)
    {
        setBreed(other.getBreed());
        setColor(other.getColor());

        feedingType_ = other.feedingType_;
        habitat_ = other.habitat_;
    }

    std::cout << "Bird: operator prisv."<< std::endl;

    return *this;
}

Bird::~Bird()
{
    std::cout << "Bird: distructor."<< std::endl;
}

std::string Bird::getFeedingType() const
{
    return feedingType_;
}

std::string Bird::getHabitat() const
{
    return habitat_;
}

void Bird::setFeedingType(const std::string& feedingType)
{
    if (feedingType.empty())
    {
        throw std::invalid_argument("FeedingType cant empty.");
    }

    feedingType_ = feedingType;
}

void Bird::setHabitat(const std::string& habitat)
{
    if (habitat.empty())
    {
        throw std::invalid_argument("habitat cant empty.");
    }

    habitat_ = habitat;
}

void Bird::print() const
{
    std::cout << "\nInfo Bird\n";
    std::cout << "Type: Bird\n";
    std::cout << "Breed: " << getBreed() << '\n';
    std::cout << "Color: " << getColor() << '\n';
    std::cout << "FeedingType: " << feedingType_ << '\n';
    std::cout << "Habitat: " << habitat_ << '\n';
}

void Bird::input()
{
    std::string breed;
    std::string color;
    std::string feedingType;
    std::string habitat;

    std::cout << "Input breed Bird: ";
    if (!std::getline(std::cin, breed))
    {
        throw std::runtime_error("error runtime breed bird.");
    }

    std::cout << "Input color Bird: ";
    if (!std::getline(std::cin, color))
    {
        throw std::runtime_error("error runtime color bird.");
    }

    std::cout << "Input feedingType Bird: ";
    if (!std::getline(std::cin, feedingType))
    {
        throw std::runtime_error("error runtime feed bird.");
    }

    std::cout << "Input habitat Bird: ";
    if (!std::getline(std::cin, habitat))
    {
        throw std::runtime_error("error runtime habitat bird.");
    }

    if (breed.empty() || color.empty() ||feedingType.empty() || habitat.empty())
    {
        throw std::invalid_argument("should not empty");
    }

    setBreed(breed);
    setColor(color);
    setFeedingType(feedingType);
    setHabitat(habitat);
}

void Bird::save(std::ostream& out) const
{
    out << getBreed() << '\n';
    out << getColor() << '\n';
    out << feedingType_ << '\n';
    out << habitat_ << '\n';

    if (!out)
    {
        throw std::runtime_error( "error save bird." );
    }
}

void Bird::load(std::istream& in)
{
    std::string breed;
    std::string color;
    std::string feedingType;
    std::string habitat;

    if (!std::getline(in, breed) || !std::getline(in, color) || !std::getline(in, feedingType) || !std::getline(in, habitat))
    {
        throw std::runtime_error( "error load bird.");
    }

    if (breed.empty() || color.empty() ||feedingType.empty() || habitat.empty())
    {
        throw std::invalid_argument("File is emty bird");
    }

    setBreed(breed);
    setColor(color);
    setFeedingType(feedingType);
    setHabitat(habitat);
}

Bird* Bird::clone() const
{
    return new Bird(*this);
}

std::string Bird::getType() const
{
    return "Bird";
}
