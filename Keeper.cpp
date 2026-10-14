#include "Keeper.h"
#include "Fish.h"
#include "Bird.h"
#include "Cat.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <utility>

Keeper::Keeper(): animals_(nullptr), count_(0), capacity_(0)
{
    std::cout << "Keeper: construcor."<< std::endl;
}

Keeper::Keeper(const Keeper& other): animals_(nullptr), count_(0), capacity_(0)
{
    std::cout << "Keeper: construcor copy." << std::endl;

    try
    {
        if (other.capacity_ > 0)
        {
            animals_ = new Animal * [other.capacity_];
            capacity_ = other.capacity_;
        }

        for (int i = 0; i < other.count_; ++i)
        {
            animals_[count_] = other.animals_[i]->clone();
            ++count_;
        }
    }
    catch (...)
    {
        clear();
        delete[] animals_;
        animals_ = nullptr;
        capacity_ = 0;
        throw;
    }
}

Keeper& Keeper::operator=(const Keeper& other)
{
    if (this != &other)
    {
        Keeper temp(other);

        std::swap(animals_, temp.animals_);
        std::swap(count_, temp.count_);
        std::swap(capacity_, temp.capacity_);
    }

    std::cout << "Keeper: operator prisv."<< std::endl;

    return *this;
}

Keeper::~Keeper()
{
    clear();
    delete[] animals_;

    std::cout << "Keeper: destrucor." << std::endl;
}

// Увеличение вместимости массива
void Keeper::increaseCapacity()
{
    int newCapacity = (capacity_ == 0) ? 2 : capacity_ * 2;
    Animal** newAnimals = new Animal * [newCapacity];

    for (int i = 0; i < count_; ++i)
    {
        newAnimals[i] = animals_[i];
    }

    delete[] animals_;
    animals_ = newAnimals;
    capacity_ = newCapacity;
}

// Добавление объекта, переданного во владение Keeper
void Keeper::addOwned(Animal* animal)
{
    if (animal == nullptr)
    {
        throw std::invalid_argument("nullptr" );
    }

    try
    {
        if (count_ == capacity_)
        {
            increaseCapacity();
        }
    }
    catch (...)
    {
        delete animal;
        throw;
    }

    animals_[count_] = animal;
    ++count_;
}

void Keeper::add(const Animal& animal)
{
    if (count_ == capacity_)
    {
        increaseCapacity();
    }

    Animal* copy = animal.clone();

    animals_[count_] = copy;
    ++count_;
}

int Keeper::getCount() const
{
    return count_;
}

// Получение животного по индексу
Animal* Keeper::getAt(int index) const
{
    if (index < 0 || index >= count_)
    {
        throw std::out_of_range( "error index" );
    }

    return animals_[index];
}

// Удаление животного по индексу
void Keeper::removeAt(int index)
{
    if (index < 0 || index >= count_)
    {
        throw std::out_of_range("error index remove" );
    }

    delete animals_[index];

    for (int i = index; i < count_ - 1; ++i)
    {
        animals_[i] = animals_[i + 1];
    }

    --count_;
    animals_[count_] = nullptr;
}

// Вывод всех животных
void Keeper::printAll() const
{
    if (count_ == 0)
    {
        std::cout << "print null" << std::endl;
        return;
    }

    for (int i = 0; i < count_; ++i)
    {
        std::cout << "\nAnimal #" << i + 1 << std::endl;
        animals_[i]->print();
    }
}

// Удаление всех животных
void Keeper::clear()
{
    for (int i = 0; i < count_; ++i)
    {
        delete animals_[i];
        animals_[i] = nullptr;
    }

    count_ = 0;
}

// Сохранение всех животных в файл
void Keeper::saveToFile(const std::string& fileName) const
{
    std::ofstream out(fileName);

    if (!out.is_open())
    {
        throw std::runtime_error("error open file");
    }

    out << count_ << '\n';

    for (int i = 0; i < count_; ++i)
    {
        out << animals_[i]->getType() << '\n';
        animals_[i]->save(out);
    }

    if (!out)
    {
        throw std::runtime_error("error file save");
    }

    std::cout << "Save file: "<< fileName << std::endl;
}

// Загрузка животных из файла
void Keeper::loadFromFile(const std::string& fileName)
{
    std::ifstream in(fileName);

    if (!in.is_open())
    {
        throw std::runtime_error("error open file for load");
    }

    int fileCount;

    if (!(in >> fileCount) || fileCount < 0)
    {
        throw std::runtime_error("error fileCount");
    }

    in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    clear();

    for (int i = 0; i < fileCount; ++i)
    {
        std::string type;

        if (!std::getline(in, type))
        {
            throw std::runtime_error("error read type animal");
        }

        Animal* animal = nullptr;

        try
        {
            if (type == "Fish")
            {
                animal = new Fish();
            }
            else if (type == "Bird")
            {
                animal = new Bird();
            }
            else if (type == "Cat")
            {
                animal = new Cat();
            }
            else
            {
                throw std::runtime_error("unknown type animal");
            }

            animal->load(in);
            addOwned(animal);
            animal = nullptr;
        }
        catch (...)
        {
            delete animal;
            throw;
        }
    }

    std::cout << "loaded from file: " << fileName << std::endl;
}
