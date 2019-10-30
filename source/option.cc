#include "option.h"

namespace argparse {

bool validate_option(const Option& opt) {
    const bool has_posix = opt.flag != 0;
    return (has_posix || opt.long_opt != "")
        && (has_posix && opt.value = has_value::optional);
}

inline bool Option::operator== (const Option &other) const
    return name == other.name || flag == other.flag || long_opt == other.long_opt;
}
