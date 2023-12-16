#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <exception>

class arg_exception : public std::exception
{
private:
    std::string m_message;

public:
    arg_exception(const std::string &message);
    const char *what() const noexcept;
};

class arg_parser
{
private:
    std::map<std::string, std::string> m_values;
    std::map<std::string, bool> m_flags;
    std::string m_program_name;

public:
    arg_parser(const std::string &program_name);
    void parse(const size_t &arg_count, char **arg_values);
    void add_value(const std::string &name, const std::string &value = "");
    void add_flag(const std::string &name, const bool &value = false);
    const std::string &get_value(const std::string &name) const;
    const bool &get_flag(const std::string &name) const;
};

#endif