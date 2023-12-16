#include <arg_parser.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <arg_parser.hpp>

arg_parser::arg_parser(const std::string &program_name)
{
    m_program_name = program_name;
}

bool arg_parser::parse(const size_t &arg_count, char **arg_values)
{
    bool help_found = false;

    for(size_t i = 1; i < arg_count; ++i)
    {
        std::string arg_str = std::string(arg_values[i]);

        if(arg_str.substr(0, 2) != "--")
        {
            std::cerr << "Error: Invalid argument \"" << arg_str << "\"" << std::endl;
            std::cout << help_str() << std::endl;

            return false;
        }

        size_t split_position = arg_str.find_first_of('=');

        if(split_position == std::string::npos)
        {
            const std::string arg_name = arg_str.substr(2);

            if(arg_name == "help")
            {
                help_found = true;

                continue;
            }

            std::map<std::string, bool>::iterator flag_it = m_flags.find(arg_name);

            if(flag_it == m_flags.end())
            {
                std::cerr << "Error: Invalid flag \"" << arg_name << "\"" << std::endl;
                std::cout << help_str() << std::endl;

                return false;
            }
            else
            {
                flag_it->second = true;
            }
        }
        else
        {
            const std::string arg_name = arg_str.substr(2, split_position - 2);
            const std::string arg_value = arg_str.substr(split_position + 1);
            std::map<std::string, std::string>::iterator value_it = m_values.find(arg_name);

            if(value_it == m_values.end())
            {
                std::cerr << "Error: Invalid value \"" << arg_name << "\"" << std::endl;
                std::cout << help_str() << std::endl;

                return false;
            }
            else
            {
                value_it->second = arg_value;
            }
        }
    }

    if(help_found)
    {
        std::cout << help_str() << std::endl;
    }

    return true;
}

const std::string &arg_parser::help_str() const
{
    std::cout << "Usage: " << m_program_name << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "--help\t\t\tShow this message" << std::endl;
}

void arg_parser::add_value(const std::string &name, const std::string &value)
{
    m_values[name] = value;
}

void arg_parser::add_flag(const std::string &name, const bool &value)
{
    m_flags[name] = value;
}

const std::string &arg_parser::get_value(const std::string &name) const
{
    return m_values.at(name);
}

const bool &arg_parser::get_flag(const std::string &name) const
{
    return m_flags.at(name);
}