#ifndef STRING_TYPE_H
#define STRING_TYPE_H

#if (__cplusplus >= 201500)
// std::string_view is available

using string_type = std::string_view;
#define get_c_str(s) s.data()

#else
// std::string_view is not available

using string_type = std::string;
#define get_c_str(s) s.c_str()

#endif

#endif /* !STRING_TYPE_H */
