#ifndef FISH_H
#define FISH_H

#include "Animal.h"
#include <string>
#include <iostream>

class Fish : public Animal
{
private:
    std::string feedingType_;

public:
    Fish();
    Fish(const std::string& breed, const std::string& color,const std::string& feedingType);
    Fish(const Fish& other);

    Fish& operator=(const Fish& other);
    ~Fish() override;

    std::string getFeedingType() const;
    void setFeedingType(const std::string& feedingType);

    void print() override;
    void input() override;

    void save(std::ostream& out) override;
    void load(std::istream& in) override;

    Fish* clone() override;
    std::string getType() override;
};

#endif
