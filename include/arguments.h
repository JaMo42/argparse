#ifndef ARGUMENTS_H
#define ARGUMENTS_H
#include "stdafx.h"
#include "string_type.h"

namespace argparse {

struct Arguments {
    friend class ArgumentParser;

    // Stores option data
    struct _OptData {
        // Number of times the option was given
        int count;
        // Arguments passed to the option
        std::forward_list<std::string> values;
    };

    // Parameters given to the program
    std::vector<string_type> parameters;
    // Options given to the program.
    std::map<string_type, _OptData> options;

    /**
     * @brief Checks whether an option is given.
     * @param name - The name of the option.
     * @return false, if the option was not given or does not exist
     */
    bool has_option(
        string_type name
    ) const;

    /**
     * @brief Checks in an option has atleast one argument.
     * @param name - The name of the option.
     * @return false, if the option does not have any arguments given ot does not exist.
     */
    bool option_has_arg(
        string_type name
    );

    /**
     * @brief Returns the number of times, an option was given
     * @param name - The name of the option
     */
    int count(
        string_type name
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
        string_type name,
        std::string &out,
        bool _no_checks = false
    );

};

}

#endif /* !ARGUMENTS_H */
