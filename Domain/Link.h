//
// Created by szili on 3/24/26.
//

#ifndef A4_5_SZILI_06_LINK_H
#define A4_5_SZILI_06_LINK_H
#include <string>
#include <utility>
#include <iostream>

/**
 * @brief A class representing a web link or URL.
 */
class Link {
    /**
     * @brief The string storing the actual URL data.
     */
    std::string url;

public:
    /**
     * @brief Default constructor. Initializes the link with an empty URL string.
     */
    Link() {}

    /**
     * @brief Parameterized constructor. Initializes the link with a specific URL.
     * Uses std::move to optimize the transfer of the string.
     * @param url The string representation of the URL to store.
     */
    Link(std::string url) : url(std::move(url)) {}

    /**
     * @brief Retrieves the currently stored URL.
     * @return A copy of the string containing the URL.
     */
    [[nodiscard]] std::string getUrl() const;

    /**
     * @brief Updates the stored URL with a new value.
     * @param url The new URL string to be set.
     */
    void setUrl(const std::string &url);

    /**
     * @brief Attempts to open the stored URL (typically invoking a system command to open a browser).
     * @return True if the link was successfully opened, false otherwise.
     */
    bool openLink() const;

    /**
     * @brief Equality operator. Compares this link to another based on their URL strings.
     * @param other The other Link object to compare against.
     * @return True if both links hold the exact same URL string, false otherwise.
     */
    bool operator==(const Link& other) const;

    /**
     * @brief Writes a Link object to an output stream.
     * @param os The output stream to write to.
     * @param link The Link object to be written.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Link& link);

    /**
     * @brief Reads a Link object from an input stream.
     * @param is The input stream to read from.
     * @param link The Link object where the read data will be stored.
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream& is, Link& link);
};

#endif //A4_5_SZILI_06_LINK_H