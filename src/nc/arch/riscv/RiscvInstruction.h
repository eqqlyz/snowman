/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#pragma once

#include <nc/config.h>

#include <nc/core/arch/CapstoneInstruction.h>

namespace nc {
namespace arch {
namespace riscv {

typedef core::arch::CapstoneInstruction<CS_ARCH_RISCV, 4> RiscvInstruction;

}}} // namespace nc::arch::riscv

/* vim:set et sts=4 sw=4: */
