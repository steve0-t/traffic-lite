#ifndef RSTR_H
#define RSTR_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstdint>
#endif

typedef uint16_t LEN_DATA_TYPE;

struct rstr
{
    char*         data;
    LEN_DATA_TYPE len;

    LEN_DATA_TYPE length() const { return len; }

    /**
    * Returns data pointer at position @pos
    */
    char* str_view(LEN_DATA_TYPE pos) const
    {
        if (pos < len && !empty() && pos >= 0) return data + pos;
        return nullptr;
    }

    /**
    * Sets data to null
    */
    void remove_data()
    {
        len  = 0;
        data = nullptr;
    }

    /**
    * Zeroes out data and len
    */
    void clear_str()
    {
        if (data == nullptr) return;
        for (LEN_DATA_TYPE i = 0; i < len; i++) data[i] = 0;
        len = 0;
    }

    /// Checks whether data is emtpy.
    int8_t empty() const { return data == nullptr || len == 0; }

    /**
    * Returns character at position i of data.
    */
    char at_pos(LEN_DATA_TYPE i) const
    {
        return (!empty() && i >= 0 && i < len) ? data[i] : 0;
    }

    /**
    * Returns first character of data.

    * Takes whitespace into consideration.
    */
    char front() const
    {
        if (!empty())
        {
            for (LEN_DATA_TYPE i = 0; i < len; i++)
            {
                if (data[i] != ' ') return data[i];
            }
        }
        return 0;
    }

    /**
    * Returns last character of data.

    * Takes whitespace into consideration.
    */
    char back() const
    {
        if (!empty())
        {
            for (LEN_DATA_TYPE i = len - 1; i >= 0; i--)
            {
                if (data[i] != ' ') return data[i];
            }
        }
        return 0;
    }

    /**
    * Trim leading and trailing whitespace.
    *
    * WARNING: modifies data
    */
    void trim()
    {
        if (empty()) return;

        uint16_t start = 0;
        while (start < len && data[start] == ' ') start++;

        uint16_t end = len;
        while (end > start && data[end - 1] == ' ') end--;

        data = data + start;
        len  = end - start;
    }
};

#endif