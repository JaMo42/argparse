#include "arguments.h"

namespace argparse {

bool Arguments::has_option(std::string_view name) const {
    // Check if the option exists
    const auto it = options.find(name);
    if (it == options.end())
        return false;
    // Return if it was given
    return it->second.has_value();
}

bool Arguments::option_has_arg(std::string_view name) {
    if (this->has_option(name))
        return !options[name]->empty();
    return false;
}

bool Arguments::next_arg(std::string_view name, std::string &out, bool _no_checks) {
    if (_no_checks || this->has_option(name))
        if (_no_checks || this->option_has_arg(name)) {
            auto &val = options[name];
            out = val->front();
            val->pop_front();
            return true;
        }
    return false;
}

}
