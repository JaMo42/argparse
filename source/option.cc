#include "option.h"

namespace argparse {

inline bool Option::operator== (const Option &other) const {
    const bool has_posix = flag != 0;
    const bool has_long = long_opt != "";
    return (name == other.name)
        || (has_posix ? (flag == other.flag) : false)
        || (has_long ? (long_opt == other.long_opt) : false);
}

bool validate_option(const Option& opt) {
    const bool has_posix = opt.flag != 0;
    return (opt.name != "")
        && (has_posix || opt.long_opt != "")
        && (has_posix ? (opt.value != has_value::optional) : true)
        && (has_posix ? isalnum(opt.flag) : true)
        && (std::all_of(opt.long_opt.begin(), opt.long_opt.end(), [&](const char c) {
                return ::isalnum(c) || (c == '-');
            }))
        && (opt.long_opt == "" ? true : opt.long_opt.length() >= 1);
}

bool contains_option(const std::vector<Option> &options, const Option &check) {
    return std::any_of(options.begin(), options.end(), [&](const Option &opt) {
        return opt == check;
    });
}

}
