/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#pragma once

#include <nc/config.h>

#include <nc/core/arch/Registers.h>

namespace nc { namespace arch { namespace riscv {

/**
 * Container class for RISCV registers.
 */
class RiscvRegisters: public core::arch::StaticRegisters<RiscvRegisters> {
public:
    RiscvRegisters();

#define REGISTER_TABLE <nc/arch/Riscv/RiscvRegisterTable.i>
#include <nc/core/arch/Registers.i>
};

}}} // namespace nc::arch::riscv

/* vim:set et sts=4 sw=4: */
