#ifndef ARGPARSE_H
#define ARGPARSE_H
#include "stdafx.h"
#include "option.h"
#include "arguments.h"

namespace argparse {

class ArgumentParser {
public: // Settings

    // Whether to allow long option to have a single -.
    // In this case, long options are checked for before
    // posix options.
    bool allow_abbreviations = false;

    // If true, inhibit option error messages
    bool option_errors = true;

public:
    /**
     * @brief Adds an option to the parser.
     * @param opt - The option to add.
     * @return Whether the option was accepted, false if the option itself was
     * not valid, or has the same name/flags as an  existing option.
     */
    bool add_argument(const Option &opt);

    /**
     * @brief Parses arguments.
     * @param argc - The number of elements in ARGV.
     * @param argv - The arguments.
     * @return @ref Arguments structure with the given arguments.
     */
    Arguments parse(int argc, const char **argv) const;

private:

    /**
     * @brief Find the index of an option using its flag.
     */
    std::size_t option_index(const char& flag) const;

    /**
     * @brief Find the index of an option suing its long option.
     */
    std::size_t option_index(std::string_view flag) const;

    /**
     * @brief Initializes @ref Arguments structure.
     * Creates entries for all registered options.
     * @param result - The struct to initialize.
     */
    void init_args(Arguments &result) const;

    /**
     * @brief Parses a long option.
     */
    void parse_long_option(
        int argc, const char **argv,
        int &pos, std::string_view name,
        const std::size_t eq_pos,
        Arguments &result
    ) const;

    /**
     * @brief Pares a posix option.
     */
    void parse_posix_option(
        int argc, const char **argv,
        int &pos, std::string_view name,
        Arguments &result
    ) const;

private:
    // Contains all options of the parser
    std::vector<Option> options;
    // The following are used to find the index of an option using its flag
    // Holds all the long options in the same order as in the options vector
    std::vector<std::string_view> option_long;
    // Holds all the posix options in the same order as in the options vector
    std::string option_letters;
};

}

#endif /* !ARGPARSE_H */
