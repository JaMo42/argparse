#include "argparse.h"

namespace argparse {

bool ArgumentParser::add_argument(const Option &opt) {
    if (!validate_option(opt)) {
        printf("Invalid option\n"); // @TODO: better error message
        return false;
    }
    options.push_back(opt);
    option_letters += opt.flag == 0 ? '-' : opt.flag;
    option_long.push_back(opt.long_opt == "" ? "<nil>" : opt.long_opt);
    return true;
}

Arguments ArgumentParser::parse(int argc, const char **argv) const {
    Arguments result;
    bool terminate_options = false;
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-' && !terminate_options) {
            if (strlen(argv[i]) == 1) {
                // Single -, ignore
                continue;
            } else if (strcmp(argv[i], "--") == 0) {
                // --, terminate option parsing
                terminate_options = true;
            } else {
                // Get the name/flag[s] of the argument
                const std::string tok = argv[i];
                const std::size_t eq_pos = tok.find('=');
                const int offset = (int)(argv[i][1] == '-') + 1;
                const std::string_view name = tok.substr(offset, eq_pos - offset);
                if (offset >= 2 // Argument is a long flag
                    // Abbreviations are enabled, and a matching option was found;
                    || (allow_abbreviations && this->option_index(name) != std::string::npos)) {
                    // Long option
                    this->parse_long_option(argc, argv, i, name, result);
                } else {
                    // POSIX options[s]
                    this->parse_posix_option(argc, argv, i, name, result);
                }
            }
        } else {
            result.parameters.push_back(argv[i]);
        }
    }
    return result;
}

std::size_t ArgumentParser::option_index(const char& flag) const {
    return option_letters.find(flag);
}

std::size_t ArgumentParser::option_index(std::string_view flag) const {
    const auto it = std::find(option_long.begin(), option_long.end(), flag);
    if (it == option_long.end())
        return std::string::npos;
    return std::distance(option_long.begin(), it);
}

int ArgumentParser::parse_long_option(
    int argc, const char **argv,
    int &pos, std::string_view name,
    Arguments &result
) const {

}

int ArgumentParser::parse_posix_option(
    int argc, const char **argv,
    int &pos, std::string_view flag,
    Arguments &result
) const {

}

}
