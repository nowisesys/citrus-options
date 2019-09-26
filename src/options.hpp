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

#ifndef LIBCITRUS_OPTIONS_HPP
#define LIBCITRUS_OPTIONS_HPP

#include <map>
#include <string>
#include <vector>

namespace Citrus {

        struct Option
        {
                Option() = default;
                Option(const Option &) = default;

                Option(std::string args);
                Option(std::string key, const std::string val);
                Option(const std::pair<std::string, std::string> &pair);

                bool HasValue() const;
                bool IsOption() const;
                bool IsOptionShort() const;
                bool IsOptionLong() const;

                static Option Split(std::string args);

                std::string key;
                std::string val;
        };

        class Options
        {
            public:
                Options() = default;
                Options(const Options &) = default;

                Options(const char *prog)
                    : program(prog) {}
                Options(const std::map<std::string, std::string> &defaults)
                    : options(defaults) {}
                Options(int argc, const char **argv); // equivalent to main(...)

                void SetProgram(std::string name);
                std::string GetProgram() const;

                void AddOption(const std::string &key, const std::string &val);
                void AddOption(const Option &option);
                void AddListing(const std::string &key);
                void AddListing(const Option &option);

                void SetOptions(std::map<std::string, std::string> options);
                void SetOptions(int argc, const char **argv);

                bool HasOption(const std::string &key) const;
                bool HasOptions() const;
                bool HasListing() const;

                Option GetOption(const std::string &key) const;
                std::string GetValue(const std::string &key) const;
                const std::map<std::string, std::string> &GetOptions() const;
                const std::vector<std::string> &GetListing() const;

            private:
                std::string program;
                std::map<std::string, std::string> options;
                std::vector<std::string> listing;
        };

} // namespace Citrus

#endif // LIBCITRUS_OPTIONS_HPP
