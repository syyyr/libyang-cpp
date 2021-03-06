/*
 * Copyright (C) 2021 CESNET, https://photonics.cesnet.cz/
 *
 * Written by Václav Kubernát <kubernat@cesnet.cz>
 *
*/

#include <libyang/libyang.h>
#include <stdexcept>
#include "Context.hpp"
#include "DataNode.hpp"
#include "utils/enum.hpp"

namespace libyang {
/**
 * @brief Creates a new libyang context.
 */
Context::Context()
    : m_ctx(nullptr, nullptr) // fun-ptr deleter deletes the default constructor
{
    ly_ctx* ctx;
    auto err = ly_ctx_new(nullptr, 0, &ctx);
    if (err != LY_SUCCESS) {
        throw std::runtime_error("Can't create libyang context (" + std::to_string(err) + ")");
    }

    m_ctx = std::unique_ptr<ly_ctx, decltype(&ly_ctx_destroy)>(ctx, ly_ctx_destroy);
}

/**
 * @brief Parses module from a string.
 *
 * @param data String containing the module definition.
 * @param format Format of the module definition.
 */
void Context::parseModuleMem(const char* data, const SchemaFormat format)
{
    // FIXME: Return the module handle that lys_parse_mem gives.
    auto err = lys_parse_mem(m_ctx.get(), data, utils::toLysInformat(format), nullptr);
    if (err != LY_SUCCESS) {
        throw std::runtime_error("Can't parse module (" + std::to_string(err) + ")");
    }
}

/**
 * @brief Parses data from a string into libyang.
 *
 * @param data String containing the input data.
 * @param format Format of the input data.
 */
DataNode Context::parseDataMem(const char* data, const DataFormat format)
{
    lyd_node* tree;
    // TODO: Allow specifying all the arguments.
    auto err = lyd_parse_data_mem(m_ctx.get(), data, utils::toLydFormat(format), 0, LYD_VALIDATE_PRESENT, &tree);
    if (err != LY_SUCCESS) {
        throw std::runtime_error("Can't parse data (" + std::to_string(err) + ")");
    }

    return DataNode{tree};
}
}
