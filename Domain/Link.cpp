//
// Created by szili on 3/24/26.
//

#include "Link.h"

std::string Link::getUrl() const {
    return url;
}

void Link::setUrl(const std::string &url) {
    this->url = url;
}

bool Link::openLink() const {
    if (this->url.empty()) {
        return false;
    }

    #ifndef TESTING_MODE
        std::string command = "xdg-open " + this->url;
        system(command.c_str());
    #endif

    return true;
}

bool Link::operator==(const Link &other) const {
    return this->url == other.url;
}

std::ostream& operator<<(std::ostream& os, const Link& link) {
    os << link.url;
    return os;
}

std::istream& operator>>(std::istream& is, Link& link) {
    is >> link.url;
    return is;
}
