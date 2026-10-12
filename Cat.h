#ifndef CAT_H
#define CAT_H

#include "Animal.h"
#include <string>
#include <iostream>

class Cat : public Animal
{
private:
    std::string ownerFullName_;
    std::string name_;

public:
    Cat();
    Cat(const std::string& breed,const std::string& color,const std::string& ownerFullName,const std::string& name);
    Cat(const Cat& other);

    Cat& operator=(const Cat& other);
    ~Cat() override;

    std::string getOwnerFullName() const;
    std::string getName() const;

    void setOwnerFullName(const std::string& ownerFullName);
    void setName(const std::string& name);

    void print() const override;
    void input() override;

    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

    Cat* clone() const override;
    std::string getType() const override;
};

#endif
