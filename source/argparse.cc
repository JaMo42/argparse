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
    this->init_args(result);
    bool terminate_options = false;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && !terminate_options) {
            if (strlen(argv[i]) == 1) {
                // Single -
                result.options["-"].count++;
            } else if (strcmp(argv[i], "--") == 0) {
                // --, terminate option parsing
                terminate_options = true;
            } else {
                // Get the name/flag[s] of the argument
                const std::string tok = argv[i];
                const std::size_t eq_pos = tok.find('=');
                const int offset = (int)(argv[i][1] == '-') + 1;
                const string_type name = tok.substr(offset, eq_pos - offset);
                if (offset >= 2 // Argument is a long flag
                    // Abbreviations are enabled, and a matching option was found;
                    || (allow_abbreviations && this->option_index(name) != std::string::npos)) {
                    // Long option
                    this->parse_long_option(argc, argv, i, name, eq_pos, result);
                } else {
                    // POSIX option
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

std::size_t ArgumentParser::option_index(string_type flag) const {
    const auto it = std::find(option_long.begin(), option_long.end(), flag);
    if (it == option_long.end())
        return std::string::npos;
    return std::distance(option_long.begin(), it);
}

void ArgumentParser::init_args(Arguments &result) const {
    result.parameters = {};
    for (const Option &opt : options) {
        result.options[opt.name] = {0, {}};
    }
    result.options["-"] = {0, {}};
}

void ArgumentParser::parse_long_option(
    int argc, const char **argv,
    int &pos, string_type name,
    const std::size_t eq_pos,
    Arguments &result
) const {
    const std::size_t opt_ind = this->option_index(name);
    if (opt_ind == std::string::npos) {
        // The option does not exist
        if (option_errors)
            std::cerr << argv[0] << ": unrecognized option `--" << name << '\'' <<std::endl;
        return;
    }
    const Option &option = options[opt_ind];
    if (option.value & has_value::_has_value) {
        // The option takes an argument
        if (eq_pos == std::string::npos) {
            // The argument is the next ARGV-element
            const string_type next = ((pos + 1) < argc) ? argv[pos + 1] : "???";
            if (next[0] == '-' || ((pos + 1) == argc)) {
                // The next ARGV-element is an option, or there is no next element
                if (option.value && has_value::_value_opt) {
                    // If the option does not require an argument, just increase its count
                    result.options[option.name].count++;
                } else {
                    // otherwise, print error
                    if (option_errors)
                        std::cerr << argv[0] << ": option `--" << name << "' requires an argument" << std::endl;
                    return;
                }
            } else {
                // There is an ARGV-element after the option
                result.options[option.name].values.push_front(argv[pos + 1]);
                result.options[option.name].count++;
                ++pos;
            }
        } else {
            // The argument is attached
            const char *arg = argv[pos] + eq_pos + 1;
            result.options[option.name].values.push_front(arg);
            result.options[option.name].count++;
        }
    } else {
        result.options[option.name].count++;
    }
}

void ArgumentParser::parse_posix_option(
    int argc, const char **argv,
    int &pos, string_type name,
    Arguments &result
) const {
    const Option &first = options[this->option_index(name[0])];
    if (first.value == has_value::required) {
        // The option takes an argument
        if (name.length() > 1) {
            // Argument is attached to the option
            result.options[first.name].values.push_front(get_c_str(name) + 1);
            result.options[first.name].count++;
        } else {
            // Argument is the next ARGV-element
            const char *next = ((pos + 1) < argc) ? argv[pos + 1] : "???";
            if (next[0] == '-') {
                // Next ARGV-element is an option
                if (option_errors)
                    std::cerr << argv[0] << ": option requires an argument -- " << name[0] << std::endl;
                return;
            } else {
                result.options[first.name].values.push_front(next);
                result.options[first.name].count++;
                ++pos;
            }
        }
    } else {
        // Flag, without the fist option
        string_type rest = {get_c_str(name) + 1};
        if (!std::all_of(rest.begin(), rest.end(), ::isalpha)) {
            // The first option followed by a number, interpret as count flag
            result.options[first.name].count += std::stoi(get_c_str(rest));
        } else {
            // Increase count for all given flags by one
            for (std::size_t c = 0; c < name.length(); c++) {
                const std::size_t opt_ind = this->option_index(name[c]);
                if (opt_ind == std::string::npos) {
                    // Option does not exist
                    if (option_errors)
                        std::cerr << argv[0] << ": invalid option -- " << name[c] << std::endl;
                    return;
                } else {
                    result.options[options[opt_ind].name].count++;
                }
            }
        }
    }
}

}
