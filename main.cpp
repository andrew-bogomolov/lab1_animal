#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <cstdlib>
#include <windows.h>

#include "Keeper.h"
#include "Fish.h"
#include "Bird.h"
#include "Cat.h"


const std::string DATA_FILE = "animals.txt";

// Очистка консоли Windows
void clearScreen()
{
    system("cls");
}

// Ожидание нажатия Enter
void pauseScreen()
{
    std::cout << "\nPress Enter to continue...";
    std::string line;
    std::getline(std::cin, line);
}

// Создание файла при первом запуске
void ensureDataFileExists()
{
    std::ifstream existingFile(DATA_FILE);

    if (existingFile.good())
    {
        return;
    }

    existingFile.close();

    std::ofstream newFile(DATA_FILE);

    if (!newFile.is_open())
    {
        throw std::runtime_error( "Cannot create animals.txt");
    }

    // Ноль означает, что в файле пока нет животных
    newFile << "0\n";

    if (!newFile)
    {
        throw std::runtime_error("Cannot initialize animals.txt");
    }
}


// Ввод целого числа с проверкой
bool readInt(const std::string& prompt, int& value)
{
    while (true)
    {
        std::cout << prompt;
        std::string line;

        if (!std::getline(std::cin, line))
        {
            return false;
        }

        std::stringstream input(line);
        char extra;

        if ((input >> value) && !(input >> extra))
        {
            return true;
        }

        std::cout << "ERROR INT\n";
    }
}

// Выбор животного по номеру
int chooseAnimal(const Keeper& keeper)
{
    if (keeper.getCount() == 0)
    {
        std::cout << "Animal null\n";
        return -1;
    }

    keeper.printAll();
    int number;

    if (!readInt("Print animal number: ", number))
    {
        return -2;
    }

    if (number < 1 || number > keeper.getCount())
    {
        std::cout << "is no animal with that number\n";
        return -1;
    }
    return number - 1;
}

// Добавление животного
void addAnimal(Keeper& keeper)
{
    std::cout << "\nWhich animal should we add?\n";
    std::cout << "1. Fish\n";
    std::cout << "2. Bird\n";
    std::cout << "3. Cat\n";

    int choice;

    if (!readInt("Your choice: ", choice))
    {
        throw std::runtime_error("Input completed");
    }

    switch (choice)
    {
    case 1:
    {
        Fish fish;
        fish.input();
        keeper.add(fish);
        break;
    }
    case 2:
    {
        Bird bird;
        bird.input();
        keeper.add(bird);
        break;
    }
    case 3:
    {
        Cat cat;
        cat.input();
        keeper.add(cat);
        break;
    }
    default:
        std::cout << "Invalid menu\n";
        return;
    }

    std::cout << "The animal has been successfully added\n";
}

// Вывод меню
void showMenu()
{
    std::cout << "MENU\n";
    std::cout << "1. Add animal\n";
    std::cout << "2. Show all the animals\n";
    std::cout << "3. Show one animal\n";
    std::cout << "4. Edit the animal\n";
    std::cout << "5. Remove the animal\n";
    std::cout << "6. Save to a file\n";
    std::cout << "7. Load from the file\n";
    std::cout << "8. Remove all animals\n";
    std::cout << "0. Exit\n";
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try
    {
        ensureDataFileExists();
    }
    catch (const std::exception& error)
    {
        std::cout << "Startup error: "<< error.what() << '\n';
        return 1;
    }

    Keeper keeper;
    bool running = true;

    while (running)
    {
        clearScreen();
        showMenu();

        int choice;

        if (!readInt("Your choice: ", choice))
        {
            break;
        }

        try
        {
            switch (choice)
            {
            case 1:
                addAnimal(keeper);
                break;

            case 2:
                keeper.printAll();
                break;

            case 3:
            {
                int index = chooseAnimal(keeper);

                if (index == -2)
                {
                    running = false;
                }
                else if (index >= 0)
                {
                    keeper.getAt(index)->print();
                }

                break;
            }

            case 4:
            {
                int index = chooseAnimal(keeper);

                if (index == -2)
                {
                    running = false;
                }
                else if (index >= 0)
                {
                    std::cout << "Print the new animal data\n";

                    keeper.getAt(index)->input();

                    std::cout << "The animal data has been updated\n";
                }
                break;
            }

            case 5:
            {
                int index = chooseAnimal(keeper);

                if (index == -2)
                {
                    running = false;
                }
                else if (index >= 0)
                {
                    keeper.removeAt(index);
                    std::cout << "The animal has been removed.\n";
                }
                break;
            }


            case 6:
                keeper.saveToFile(DATA_FILE);
                std::cout << "Animals saved successfully.\n";
                break;



            case 7:
                keeper.loadFromFile(DATA_FILE);
                std::cout << "Animals loaded successfully.\n";
                break;


            case 8:
            {
                int confirm;

                if (!readInt("Remove all animals? (1 yes, 0 no): ",confirm))
                {
                    running = false;
                    break;
                }

                if (confirm == 1)
                {
                    keeper.clear();
                    std::cout << "All animals have been removed\n";
                }
                else
                {
                    std::cout << "Delete has been cancelled.\n";
                }

                break;
            }

            case 0:
                running = false;
                break;

            default:
                std::cout << "error  no  menu \n";
                break;
            }
        }
        catch (const std::exception& error)
        {
            std::cout << "Error: " << error.what() << '\n';
        }

        if (running)
        {
            pauseScreen();
        }
    }

    std::cout << "The program has been completed\n";
    return 0;
}
