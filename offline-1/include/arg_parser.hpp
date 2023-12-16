#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <cstdint>
#include <map>
#include <set>
#include <string>

class arg_parser
{
private:
    std::map<std::string, std::string> m_values;
    std::map<std::string, bool> m_flags;
    std::string m_program_name;
    std::string help_command;

public:
    arg_parser(const std::string &program_name);
    const std::string &help_str() const;
    bool parse(const size_t &arg_count, char **arg_values);
    void add_value(const std::string &name, const std::string &value = "");
    void add_flag(const std::string &name, const bool &value = false);
    const std::string &get_value(const std::string &name) const;
    const bool &get_flag(const std::string &name) const;
};

#endif