#ifndef ARGUMENTS_H
#define ARGUMENTS_H
#include "stdafx.h"

namespace argparse {

struct Arguments {
    // List of arguments the option has.
    // If the value is not present, the option was not given.
    using ArgVal = std::optional<std::forward_list<std::string_view>>;
    // Parameters given to the program
    std::vector<std::string_view> parameters;
    // Options given to the program.
    std::map<std::string_view, ArgVal> options;

    /**
     * @brief Checks whether an option is given.
     * @param name - The name of the option.
     * @return false, if the option was not given or does not exist
     */
    bool has_option(
        std::string_view name
    ) const;

    /**
     * @brief Checks in an option has atleast one argument.
     * @param name - The name of the option.
     * @return false, if the option does not have any arguments given ot does not exist.
     */
    bool option_has_arg(
        std::string_view name
    );

    /**
     * @brief Get the next argument of an option.
     * @param name - The name of the option.
     * @param out - String to write the value to.
     * @param _no_checks - If true, do not check whether the option exists or has arguments given.
     * If this is given and
     * A - the option does not exist, an entry for it gets created in the map.
     * In this case has_option will still work correctly (this case is harmless).
     * B - the option does exist but does not have any values, the function will
     * try to pop from an empty list, causing an exception.
     * @return false, if there were no more arguments for the option or the option does not exist.
     */
    bool next_arg(
        std::string_view name,
        std::string &out,
        bool _no_checks = false
    );
};

}

#endif /* !ARGUMENTS_H */
