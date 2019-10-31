# argparse

A C++ argument parser inspired by pythons argparse module.

## Usage

### Argument syntax

Both POSIX and GNU long option are supported. Syntax follows [GNU Argument Syntax](https://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html)

1. Arguments are options if they begin with a hyphen delimiter (‘-’).

2. Multiple options may follow a hyphen delimiter in a single token if the options do not take arguments. Thus, ‘-abc’ is equivalent to ‘-a -b -c’.

3. Option names are single alphanumeric characters (as for`isalnum`).

4. Certain options require an argument. For example, the ‘-o’ command of the`ld`command requires an argument—an output file name.

5. An option and its argument may or may not appear as separate tokens. (In other words, the whitespace separating them is optional.) Thus, ‘-o foo’and ‘-ofoo’ are equivalent.

6. Options typically precede other non-option arguments.

   - This is not a requirement for this parser.

7. The argument ‘--’ terminates all options; any following arguments are treated as non-option arguments, even if they begin with a hyphen.

8. A token consisting of a single hyphen character is interpreted as an ordinary non-option argument. By convention, it is used to specify input from or output to the standard input and output streams.

   - This is currently ignored

9. Options may be supplied in any order, or appear multiple times. The interpretation is left up to the particular application program.

Long options:

10. Long options consist of ‘--’ followed by a name made of alphanumeric characters and dashes.

11. To specify an argument for a long option either `--name=value` or `--name value` can be used.

12. Long option can be abbreviated (if allowed by the parser), so that `-std=c++17` becomes the same as `--std=c++17`. In this case, long options can shadow POSIX options.

In addition to this, the syntax `-O3` will be interpreted as `-OOO`, this can interfere with (3.), as subsequent options with numeric flags will be interpreted as the count for the first option in the sequence. For this to work, there can only be one flag at the beginning of the sequence and only digits may follow.

## Requirements

- C++17 or higher

## @TODO

- Do something with `-` instead of ignoring it.

- Create a constructor for `ArgumentParser`, allowing to set parser settings

- Create help text generator




