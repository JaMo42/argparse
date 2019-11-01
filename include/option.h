#ifndef OPTION_H
#define OPTION_H
#include "stdafx.h"
#include "string_type.h"

namespace argparse {

enum has_value {
    // Values
    none = 0b00,
    required = 0b10,
    optional = 0b11,
    // Bit masks
    _has_value = 0b10,
    _value_opt = 0b01
};

struct Option {
    // The name of the option in the @ref Arguments struct
    string_type name;
    // A short desciption of the option
    string_type description {""};
    // The POSIX flag of the option
    char flag {0};
    // The long option of the option
    string_type long_opt {""};
    // What type of argument the option takes
    has_value value {has_value::none};

    /**
     * @brief Check if two options are equal
     * Two option count as equal, if either their name, flag or long option is equal.
     */
    bool operator== (const Option &other) const;
};

/**
 * @brief Validates an option.
 * Checks that the option has either a short or long option.
 * Checks that the value is compatible with the option (if it has a short
 * option, it cannot have an option argument).
 * Checks that the option has a name.
 * Checks that the POSIX flag, if given, is alphanumeric.
 * @param opt - The option to validate
 */
bool validate_option(const Option& opt);

/**
 * @brief Checks if a vector of option contains a option.
 */
bool contains_option(const std::vector<Option> &options, const Option &check);

}

#endif /* !OPTION_H */
