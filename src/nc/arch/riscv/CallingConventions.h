/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#pragma once

#include <nc/config.h>

#include <nc/core/ir/calling/Convention.h>

namespace nc {
namespace arch {
namespace riscv {

class RiscvArchitecture;

class DefaultCallingConvention: public core::ir::calling::Convention {
public:
    DefaultCallingConvention();
};

}}} // namespace nc::arch::riscv

/* vim:set et sts=4 sw=4: */
