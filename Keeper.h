#ifndef KEEPER_H
#define KEEPER_H

#include "Animal.h"
#include <string>

class Keeper
{
private:
    Animal** animals_;
    int count_;
    int capacity_;

    void increaseCapacity();
    void addOwned(Animal* animal);

public:
    Keeper();
    Keeper(const Keeper& other);

    Keeper& operator=(const Keeper& other);
    ~Keeper();

    int getCount() const;
    void add(const Animal& animal);
    void removeAt(int index);
    Animal* getAt(int index) const;
    void printAll() const;
    void clear();

    void saveToFile(const std::string& fileName) const;
    void loadFromFile(const std::string& fileName);
};

#endif
