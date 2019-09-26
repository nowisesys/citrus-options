# Citrus C++

## Command line options for C++ (citrus-options)

This library provides an alternative to getopt(3) for parsing command line options with a pure object oriented implementation. 

Instead of using an fixed structure of accepted options that input options are validated against, this library is feed with options that gets classified. This gives a flexible solution that supports default arguments, standard options (long and short) and optional arguments (listing).

## Example

An standard program with support for --help and --version might use this boiler plate code:

```c++
#include <iostream>
#include <citrus/options.hpp>

int main(int argc, const char **argv)
{
        Citrus::Options options(argc, argv);

        if (options.HasOption("--help") || options.HasOption("-h")) {
                std::cout 
                    << "Usage: " << options.GetProgram() << " [...options]\n"
                    << "Options:\n"
                    << "  --address=host    : The target host (IP or FQHN)\n"
                    << "  --port=num        : Connect to TCP port\n"
                    << "  --help,-h         : This causal help\n"
                    << "  --version         : Show program version\n";
                return 0;
        }
        if (options.HasOption("--version")) {
                std::cout << options.GetProgram() << " v1.00\n";
                return 0;
        }

        if (!options.HasOption("--address") || 
            !options.HasOption("--port")) {
                std::cerr << options.GetProgram() << ": The address and port options are required!\n";
                return 1;
        }

        for (auto option : options.GetOptions()) {
                std::cout << option.first << "=" << option.second << "\n";
        }

        return 0;
}
```

Any --xxx or -x options ends up in the options map. Command line arguments not starting with an dash ('-') will end up in the listings array and can be processed by calling the GetListing() method:

```c++
#include <iostream>
#include <citrus/options.hpp>

int main(int argc, const char **argv)
{
        Citrus::Options options(argc, argv);

        if (options.HasListing()) {
                for (auto option : options.GetListing()) {
                        std::cout << option << "\n";
                }
        }

        return 0;
}
```
Invoking this program with some non-option arguments would yield output like this:

```bash
bash$> listing --key1=val1 --key2=val2 hello --key3=val3 world
hello
world
```

## Default options

It's often useful to provide default values that can be overridden by command line options or values scanned from reading a config file. In this case, simply call AddOption() before parsing i.e. the argv array.

## Requirements

A decent C++ compiler supporting version 11 should be sufficient. Some parts uses version 17 with code emulation for non-conforming compilers (i.e. lack of std::map<K,V>::merge()).

## Building

A standard installation into /usr/local:

```bash
bash$> ./autogen.sh
bash$> ./configure
bash$> make && make install
```

Pass --prefix=path to configure or use DESTDIR for make install to install in non-standard locations.

## Getting started

See the examples directory for complete code ready to be run.

## License

This library is released under LGPL-3.0 and can be linked and used with commercial applications.

## Bug report & suggestions

Please see the AUTHORS file for contact information. Feel free to submit bug reports and suggestions.