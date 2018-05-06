/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#include "RiscvRegisters.h"

namespace nc { namespace arch { namespace riscv {

RiscvRegisters::RiscvRegisters() {
#define REGISTER_TABLE <nc/arch/riscv/RiscvRegisterTable.i>
#include <nc/core/arch/RegistersConstructor.i>
}

}}} // namespace nc::arch::riscv

/* vim:set et sts=4 sw=4: */
