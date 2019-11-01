#include "arguments.h"

namespace argparse {

bool Arguments::has_option(string_type name) const {
    // Check if the option exists
    const auto it = options.find(name);
    if (it == options.end())
        return false;
    // Return if it was given
    return it->second.count >= 1;
}

bool Arguments::option_has_arg(string_type name) {
    if (this->has_option(name))
        return !options[name].values.empty();
    return false;
}

int Arguments::count(string_type name) {
    if (this->has_option(name))
        return options[name].count;
    return 0;
}

bool Arguments::next_arg(string_type name, std::string &out, bool _no_checks) {
    if (_no_checks || this->has_option(name))
        if (_no_checks || this->option_has_arg(name)) {
            out = options[name].values.front();
            options[name].values.pop_front();
            return true;
        }
    return false;
}

}
