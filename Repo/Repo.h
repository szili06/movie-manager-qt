//
// Created by szili on 3/24/26.
//

#ifndef A4_5_SZILI_06_REPO_H
#define A4_5_SZILI_06_REPO_H

#include <vector>
#include <algorithm>
#include "../Domain/Exceptions.h"

/**
 * @brief An abstract base repository template.
 * @tparam T The type of the elements to be stored in the repository.
 */
template <typename T>
class Repo {
protected:
    std::vector<T> data;
public:
    virtual ~Repo() = default;
    
    virtual void addElement(const T& elem) {
        auto it = std::find(data.begin(), data.end(), elem);
        if (it != data.end()) {
            throw RepositoryException("Element already exists in repository!");
        }
        data.push_back(elem);
    }

    virtual void removeElement(const T& elem) {
        auto it = std::find(data.begin(), data.end(), elem);
        if (it != data.end()) {
            data.erase(it);
        } else {
            throw RepositoryException("Element not found in repository!");
        }
    }

    virtual void updateElement(const T& oldElem, const T& newElem) {
        auto it = std::find(data.begin(), data.end(), oldElem);
        if (it != data.end()) {
            *it = newElem;
        } else {
            throw RepositoryException("Element not found in repository!");
        }
    }

    [[nodiscard]] virtual int getSize() const {
        return static_cast<int>(data.size());
    }

    virtual T& getElement(const T& elem) {
        auto it = std::find(data.begin(), data.end(), elem);
        if (it != data.end()) {
            return *it;
        }
        throw RepositoryException("Element not found in repository!");
    }

    virtual std::vector<T> getData() {
        return data;
    }
};

#endif //A4_5_SZILI_06_REPO_H
