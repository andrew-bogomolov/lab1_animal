#ifndef BIRD_H
#define BIRD_H

#include "Animal.h"
#include <string>
#include <iostream>

class Bird : public Animal
{
private:
    std::string feedingType_;
    std::string habitat_;

public:
    Bird();
    Bird(const std::string& breed, const std::string& color, const std::string& feedingType,  const std::string& habitat);
    Bird(const Bird& other);

    Bird& operator=(const Bird& other);
    ~Bird() override;

    std::string getFeedingType() const;
    std::string getHabitat() const;

    void setFeedingType(const std::string& feedingType);
    void setHabitat(const std::string& habitat);

    void print() const override;
    void input() override;

    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

    Bird* clone() const override;
    std::string getType() const override;
};

#endif
