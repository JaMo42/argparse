#ifndef OPTION_H
#define OPTION_H

namespace argparse {

enum has_value {
    // Values
    none = 0b00,
    required = 0b10,
    optional = 0b11,
    // Bit masks
    _has_value = 0b10,
    _value_opt = 0b01;
};

struct Option {
    // The name of the option in the @ref Arguments struct
    std::string_view name;
    // A short desciption of the option
    std::string_view description {""};
    // The POSIX flag of the option
    char flag {0};
    // The long option of the option
    std::string_view long_opt {""};
    // What type of argument the option takes
    has_value value {has_value::none};
};

/**
 * @brief Validates an option.
 * Checks that the option has either a short or long option.
 * Checks that the value is compatible with the option (if it has a short
 * option, it cannot have an option argument).
 * @param opt - The option to validate
 */
bool validate_option(const Option& opt);
    const bool has_posix = opt.flag != 0;
    return (has_posix || opt.long_opt != "")
        && (has_posix && opt.value = has_value::optional);
}

#endif /* !OPTION_H */
