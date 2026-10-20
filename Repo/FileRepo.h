#ifndef A4_5_SZILI_06_FILEREPO_H
#define A4_5_SZILI_06_FILEREPO_H

#include "Repo.h"
#include <fstream>
#include <string>
#include <utility>
#include <sstream>

/**
 * @brief A repository that persists data in a text file.
 * Inherits from Repo<T> and adds file loading and saving capabilities.
 * @tparam T The type of elements stored in the repository.
 */
template <typename T>
class FileRepo : public Repo<T> {
private:
    /**
     * @brief The name of the file used for storage.
     */
    std::string filename;

    /**
     * @brief Loads the data from the file into the repository's vector.
     */
    void loadFromFile() {
        std::ifstream file(this->filename);
        if (!file.is_open()) {
            return;
        }

        this->data.clear();
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            T elem;
            try {
                ss >> elem;
                this->data.push_back(elem);
            } catch (...) {

            }
        }
        file.close();
    }

    /**
     * @brief Saves the current state of the repository's vector to the file.
     */
    void saveToFile() {
        std::ofstream file(this->filename);
        if (!file.is_open()) {
            return;
        }

        for (const auto& elem : this->data) {
            file << elem << "\n";
        }
        file.close();
    }

public:
    /**
     * @brief Constructor for FileRepo. Loads data from the specified file.
     * @param filename The path to the storage file.
     */
    FileRepo(std::string filename) : filename(std::move(filename)) {
        this->loadFromFile();
    }

    /**
     * @brief Adds an element to the repository and saves the change to the file.
     * @param elem The element to be added.
     */
    void addElement(const T& elem) override {
        Repo<T>::addElement(elem);
        this->saveToFile();
    }

    /**
     * @brief Removes an element from the repository and saves the change to the file.
     * @param elem The element to be removed.
     */
    void removeElement(const T& elem) override {
        Repo<T>::removeElement(elem);
        this->saveToFile();
    }

    /**
     * @brief Updates an element in the repository and saves the change to the file.
     * @param oldElem The element to be replaced.
     * @param newElem override The new element to replace with.
     */
    void updateElement(const T& oldElem, const T& newElem) override {
        Repo<T>::updateElement(oldElem, newElem);
        this->saveToFile();
    }
};

#endif // A4_5_SZILI_06_FILEREPO_H
