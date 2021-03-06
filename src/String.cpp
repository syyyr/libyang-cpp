/*
 * Copyright (C) 2021 CESNET, https://photonics.cesnet.cz/
 *
 * Written by Václav Kubernát <kubernat@cesnet.cz>
 *
*/
#include <cstdlib>
#include <cstring>
#include <string>
#include "String.hpp"

/**
 * @brief Wraps a new C-string.
 */
String::String(char* str)
    : m_ptr(str, std::free)
{
}

/**
 * @brief Retrieves the C-string.
 */
std::shared_ptr<char> String::get()
{
    return m_ptr;
}

/**
 * @brief Returns a copy of the string as std::string.
 */
std::string String::toStdString()
{
    return m_ptr.get();
}

bool String::operator==(const char* str) const
{
    return !std::strcmp(m_ptr.get(), str);
}

