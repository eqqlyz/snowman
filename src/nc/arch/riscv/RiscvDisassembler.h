/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#pragma once

#include <nc/config.h>

#include <memory>

#include <nc/core/arch/Capstone.h>
#include <nc/core/arch/Disassembler.h>

namespace nc {
namespace arch {
namespace riscv {

class RiscvArchitecture;

/**
 * Disassembler for ARM architecture.
 *
 * TODO: Support for THUMB instructions.
 */
class RiscvDisassembler: public core::arch::Disassembler {
    std::unique_ptr<core::arch::Capstone> capstone_;
    int mode_;

public:
    RiscvDisassembler(const RiscvArchitecture *architecture);

    virtual ~RiscvDisassembler();

    std::shared_ptr<core::arch::Instruction> disassembleSingleInstruction(ByteAddr pc, const void *buffer, ByteSize size) override;
};

}}} // namespace nc::arch::riscv

/* vim:set et sts=4 sw=4: */
