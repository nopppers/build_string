#pragma once

#include <string>
#include <cstring>
#include "build_string_extensions.hpp"
#include "build_string_settings.hpp"

namespace string
{
    namespace build
    {
        // Element length functions
        int element_length(const std::string &str) { return str.size(); }
        int element_length(const char *str) { return strlen(str); }
        int element_length(const int &num) 
        {
            int absNum = abs(num);
            bool isNegative = absNum < 0;
            int result = 0;
            if (absNum < 10)
            {
                result = 1;
            }
            else if (absNum < 100)
            {
                result = 2;
            }
            else if (absNum < 1000)
            {
                result = 3;
            }
            else if (absNum < 10000)
            {
                result = 4;
            }
            else if (absNum < 100000)
            {
                result = 5;
            }
            else if (absNum < 1000000)
            {
                result = 6;
            }
            else if (absNum < 10000000)
            {
                result = 7;
            }
            else if (absNum < 100000000)
            {
                result = 8;
            }
            else if (absNum < 1000000000)
            {
                result = 9;
            }
            else if (absNum < 10000000000)
            {
                result = 10;
            }

            if (result == 0)
            {
                throw std::runtime_error("Weird-ass integer");
            }

            return result;
        }
        int element_length(char c) { return 1; };

        // Element concat functions
        void concat_element(char *resultBuf, const std::string &elem, int len)
        {
            memcpy(resultBuf, &elem[0], len);
        }

        void concat_element(char *resultBuf, const char *str, int len)
        {
            memcpy(resultBuf, str, len);
        }

        void concat_element(char *resultBuf, int num, int len)
        {
            sprintf(resultBuf, "%d", num);
        }

        void concat_element(char *resultBuf, char c, int len)
        {
            *resultBuf = c;
        }

        template <typename Elem>
        char* concat_element(char *resultBuf, Elem &&elem)
        {
            int len = element_length(std::forward<Elem>(elem));
            concat_element(resultBuf, std::forward<Elem>(elem), len);
            char *newResultBuf = resultBuf + len;
            return newResultBuf;
        }

        // Implementation
        template <typename Elem>
        int args_length(Elem &&elem)
        {
            return element_length(std::forward<Elem>(elem));
        }

        template <typename Elem, typename ...Args>
        int args_length(Elem&& elem, Args&& ...args)
        {
            // TODO: Make this tail recursive
            return element_length(std::forward<Elem>(elem)) 
                 + args_length(std::forward<Args>(args)...);
        }

        template <typename Elem>
        void concat_elements(char *resultBuf, Elem&& elem)
        {
            concat_element(resultBuf, std::forward<Elem>(elem));
        }

        template <typename Elem, typename ...Args>
        void concat_elements(char *resultBuf, Elem&& elem, Args&& ...args)
        {
            char *nextResultBuf = concat_element(resultBuf, std::forward<Elem>(elem));
            concat_elements(nextResultBuf, std::forward<Args>(args)...);
        }

        template <typename ...Args>
        void concat_string(std::string &init, Args&& ...args)
        {
            std::string &result = init;
            int fullLength = init.size() + args_length(std::forward<Args>(args)...);
            int initialSize = init.size();
            result.resize(fullLength);
            concat_elements(&result[initialSize], std::forward<Args>(args)...);
        }

        template <typename ...Args>
        std::string build_string(Args&& ...args)
        {
            std::string result;
            concat_string(result, std::forward<Args>(args)...);
            return result;
        }
    }
}

class StringBuilder : public std::string
{
public:
    StringBuilder() : std::string() {}
    StringBuilder(const std::string &str) : std::string(str) {}
    StringBuilder(std::string &&str) : std::string(std::move(str)) {}

    template <typename ...Args>
    StringBuilder(Args&& ...args) 
        : std::string()
    {
        append(std::forward<Args>(args)...);
    }

    template <typename ...Args>
    void append(Args&& ...args) 
    {
        concat_string(*this, std::forward<Args>(args)...);
    }
};