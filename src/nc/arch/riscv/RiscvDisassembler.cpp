/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#include "RiscvDisassembler.h"

#include <nc/common/make_unique.h>

#include "RiscvArchitecture.h"
#include "RiscvInstruction.h"

namespace nc {
namespace arch {
namespace riscv {

RiscvDisassembler::RiscvDisassembler(const RiscvArchitecture *architecture):
    core::arch::Disassembler(architecture)
{
    mode_ = CS_MODE_ARM;
    if (architecture->byteOrder() == ByteOrder::LittleEndian) {
        mode_ |= CS_MODE_LITTLE_ENDIAN;
    } else if (architecture->byteOrder() == ByteOrder::BigEndian) {
        mode_ |= CS_MODE_BIG_ENDIAN;
    }
    capstone_ = std::make_unique<core::arch::Capstone>(CS_ARCH_RISCV, mode_);
}

RiscvDisassembler::~RiscvDisassembler() {}

std::shared_ptr<core::arch::Instruction> RiscvDisassembler::disassembleSingleInstruction(ByteAddr pc, const void *buffer, ByteSize size) {
    if (auto instr = capstone_->disassemble(pc, buffer, size, 1)) {
        /* Instructions must be aligned to their size. */
        if ((instr->address & (instr->size - 1)) == 0) {
            return std::make_shared<RiscvInstruction>(mode_, instr->address, instr->size, buffer);
        }
    }
    return nullptr;
}

}}} // namespace nc::arch::riscv

/* vim:set et sts=4 sw=4: */
