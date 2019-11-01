#ifndef STRING_TYPE_H
#define STRING_TYPE_H

//#if __has_include(<string_view>)
//#if __cplusplus >= 201500
#if __cpp_lib_string_view >= 201606

using string_type = std::string_view;
#define get_c_str(s) s.data()

#else

using string_type = std::string;
#define get_c_str(s) s.c_str()

#endif

#endif /* !STRING_TYPE_H */
