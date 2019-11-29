# argparse

[![CodeFactor](https://www.codefactor.io/repository/github/jamo42/argparse/badge)](https://www.codefactor.io/repository/github/jamo42/argparse)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6e11a48d2d3d46259121be09ace2ff70)](https://www.codacy.com/manual/JaMo42/argparse?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=JaMo42/argparse&amp;utm_campaign=Badge_Grade)

A C++ argument parser inspired by pythons argparse module.

## Usage

```cpp
#include "argparse.h"

int main(int argc, const char **argv) {
```

### ArgumentParser

#### Creation

```cpp
    ArgumentParser parser(argv[0]);
```

The constructor takes the name of the program as argument. This gets used for help and error messages.

#### Configuring

-   set `allow_abbreviations` to true, in order to allow long options to have a sginle `-` (See **[below](#Argument-Syntax)** for more information).

-   Set `option_errors` to false, in order to disable option error messages.

Defaults:

```cpp
    parser.allow_abbreviations = false;
    parser.option_errors = true;
```

#### Adding arguments

```cpp
    parser.add_argument(Option{
        "name",
        "short description",
        'f',
        "long-option",
        has_value::required
    });
```

See **[below](#Options)** for more information about the `Options` struct and what values are required.

#### Parsing

```cpp
    Arguments args = parser.parse(argc, argv);
```

### Arguments

#### Check for parsing errors

```cpp
    const bool args_ok = args.ok();
```

Returns `false` if either there was an unknown option or an option was missing its argument.

#### Checking wheter an option exists

```cpp
    const bool hello_exists = args.has_option("hello");
```

#### Check how many times an option was given

```cpp
    const int verbosity = args.count("verbosity");
    const bool has_hello = args.count("hello") >= 1;
```

#### Check whether an option still has a value

```cpp
    const bool hello_has_val = args.option_has_arg("hello");
```

#### Get the next argument of an option

```cpp
    std::string out;
    bool read = args.next_arg("hello", out);
```

Return `true` if there was an argument and it was written (same as `option_has_arg`).
Optionally you can run the following to neither check if the option exists, or if it has a value. This is a (little) bit faster, but may try popping from an empty list, causing an exception.

```cpp
    bool read = args.next_arg("hello", out, true);

} // closes the main function
```

### Options

The struct is declared as

```cpp
struct Option {
    std::string_view name;
    std::string_view description {""};
    char flag {0};
    std::string_view long_opt {""};
    has_value value {has_value::none};
};
```

In order to be valid, either `flag` of `long_opt` must have valid value. See **[below](#Argument-Syntax)**(3. & 10.) for information about what a valid value is.

### has_value

```cpp
enum has_value {
    none = 0b00,
    required = 0b10,
    optional = 0b11,
};
```

The values should be self explanatory.

### Argument Syntax

Both POSIX and GNU long option are supported. Argument syntax follows the [GNU Argument Syntax](https://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html).

1.  Arguments are options if they begin with a hyphen delimiter (‘-’).

2.  Multiple options may follow a hyphen delimiter in a single token if the options do not take arguments. Thus, ‘-abc’ is equivalent to ‘-a -b -c’.

3.  Option names are single alphanumeric characters (as for`isalnum`).

4.  Certain options require an argument. For example, the ‘-o’ command of the`ld`command requires an argument—an output file name.

5.  An option and its argument may or may not appear as separate tokens. (In other words, the whitespace separating them is optional.) Thus, ‘-o foo’and ‘-ofoo’ are equivalent.

6.  Options typically precede other non-option arguments.

    -   This is not a requirement for this parser.

7.  The argument ‘--’ terminates all options; any following arguments are treated as non-option arguments, even if they begin with a hyphen.

8.  A token consisting of a single hyphen character is interpreted as an ordinary non-option argument. By convention, it is used to specify input from or output to the standard input and output streams.

9.  Options may be supplied in any order, or appear multiple times. The interpretation is left up to the particular application program.

Long options:

10. Long options consist of ‘--’ followed by a name made of alphanumeric characters and dashes.

11. To specify an argument for a long option either `--name=value` or `--name value` can be used.

12. Long option can be abbreviated (if allowed by the parser), so that `-std=c++17` becomes the same as `--std=c++17`. In this case, long options can shadow POSIX options.

In addition to this, the syntax `-O3` will be interpreted as `-OOO`, this can interfere with (3.), as subsequent options with numeric flags will be interpreted as the count for the first option in the sequence. For this to work, there can only be one flag at the beginning of the sequence and only digits may follow.

## Requirements

-   CMake

## Building

### Building

```sh
.../argparse $ mkdir build
.../argparse & cd build
.../argparse/build $ cmake ..
```

Unix systems:

```sh
.../argparse/build $ make
```

Windows:

Running cmake will generate a Visual Studio Solution, open with Visual Studio and compile.

Optionally you can call cmake with `-G "MinGW Makefiles"` to generate a Makefile and the use make.

### Installing

```sh
$ sudo make install
```
