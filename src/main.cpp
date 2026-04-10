#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <limits>

int main()
{
    std::filesystem::path const dataPath = "../../data";
    if (std::filesystem::exists(dataPath))
    {
        std::unordered_map<char, std::filesystem::path> asciiFile;
        asciiFile[' '] = "../../data/espace.txt";
        for (auto const &folder : std::filesystem::directory_iterator(dataPath))
        {
            if (std::filesystem::is_directory(folder))
            {
                for (const auto &file : std::filesystem::directory_iterator(folder))
                {
                    if (!std::filesystem::is_directory(file) == true && std::filesystem::path(file).extension() == ".txt")
                    {
                        asciiFile[file.path().stem().string()[0]] = file.path();
                    }
                }
            }
        }

        std::string firstTest;
        std::cout << "Ecrivez quelque chose (uniquement lettres et chiffres)\nEvitez les caracteres speciaux et les symboles (+, -, @, &, etc.) : ";
        std::getline(std::cin, firstTest);
        std::cout << std::endl;

        for (auto &content : firstTest)
        {
            content = static_cast<char>(std::toupper(static_cast<unsigned char>(content)));
            if (asciiFile.contains(content))
            {
                if (std::ifstream testFile = asciiFile.at(content); testFile.is_open())
                {
                    std::string line;
                    while (std::getline(testFile, line))
                    {
                        std::cout << line << std::endl;
                    }
                    std::cout << std::endl;
                }
            }
        }

        std::cout << "Programme termiee." << std::endl;
        std::cout << "Appuyez sur Entrée pour fermer le programme." << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    else
    {
        std::cout << "The path: " << dataPath << " does not exist." << std::endl;
    }

    return 0;
}