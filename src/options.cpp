// Copyright (C) 2019 Anders Lövgren (Nowise Systems)
//
// This library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "options.hpp"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE // basename()
#endif
#include <string.h>

namespace Citrus {

        //
        // Implemention for struct Option:
        //

        Option::Option(std::string args)
            : Option(Split(args)) {}

        Option::Option(std::string key, const std::string val)
            : key(key), val(val) {}

        Option::Option(const std::pair<std::string, std::string> &pair)
            : key(pair.first), val(pair.second) {}

        bool Option::HasValue() const
        {
                return val.length();
        }

        bool Option::IsOption() const
        {
                if (key.empty()) {
                        return false;
                } else if (IsOptionLong()) {
                        return true;
                } else if (IsOptionShort()) {
                        return true;
                } else {
                        return false;
                }
        }

        bool Option::IsOptionShort() const
        {
                if (key.length() != 2) {
                        return false;
                } else if (key[0] == '-' && key[1] == '-') {
                        return false;
                } else {
                        return true;
                }
        }
        bool Option::IsOptionLong() const
        {
                if (key.length() < 2) {
                        return false;
                } else if (key[0] == '-' && key[1] == '-') {
                        return true;
                } else {
                        return false;
                }
        }

        Option Option::Split(std::string args)
        {
                Option option;
                std::string::size_type pos = args.find_first_of('=');

                if (pos == std::string::npos) {
                        option.key = args;
                        option.val = "";
                } else {
                        option.key = args.substr(0, pos);
                        option.val = args.substr(pos + 1);
                }

                return option;
        }

        //
        // Implemention for class Options:
        //

        Options::Options(int argc, const char **argv)
        {
                SetProgram(argv[0]);
                SetOptions(argc, argv);
        }

        void Options::SetProgram(std::string name)
        {
                program = basename(name.c_str());
        }

        std::string Options::GetProgram() const
        {
                return program;
        }

        void Options::AddOption(const std::string &key, const std::string &val)
        {
                options[key] = val;
        }

        void Options::AddOption(const Option &option)
        {
                options[option.key] = option.val;
        }

        void Options::AddListing(const std::string &key)
        {
                listing.push_back(key);
        }

        void Options::AddListing(const Option &option)
        {
                listing.push_back(option.key);
        }

        void Options::SetOptions(std::map<std::string, std::string> options)
        {
#if defined(HAVE_CXX17)
                this->options.merge(options);
#else
                for (auto option : options) {
                        this->options[option.first] = option.second;
                }
#endif
        }

        void Options::SetOptions(int argc, const char **argv)
        {
                for (int i = 1; i < argc; ++i) {
                        Option option(argv[i]);

                        if (option.IsOption()) {
                                AddOption(option);
                        } else {
                                AddListing(option);
                        }
                }
        }

        bool Options::HasOption(const std::string &key) const
        {
                return options.find(key) != options.end();
        }

        bool Options::HasOptions() const
        {
                return options.size();
        }

        bool Options::HasListing() const
        {
                return listing.size();
        }

        Option Options::GetOption(const std::string &key) const
        {
                auto found = options.find(std::string(key));
                return Option(found->first, found->second);
        }

        std::string Options::GetValue(const std::string &key) const
        {
                auto found = options.find(std::string(key));
                return found->second;
        }

        const std::map<std::string, std::string> &Options::GetOptions() const
        {
                return options;
        }

        const std::vector<std::string> &Options::GetListing() const
        {
                return listing;
        }

} // namespace Citrus
