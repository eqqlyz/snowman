/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#pragma once

#include <nc/config.h>

#include <nc/core/irgen/InstructionAnalyzer.h>

namespace nc {
namespace arch {
namespace riscv {

class RiscvArchitecture;
class RiscvInstructionAnalyzerImpl;

class RiscvInstructionAnalyzer: public core::irgen::InstructionAnalyzer {
    std::unique_ptr<RiscvInstructionAnalyzerImpl> impl_;

public:
    RiscvInstructionAnalyzer(const RiscvArchitecture *architecture);

    ~RiscvInstructionAnalyzer();

protected:
    virtual void doCreateStatements(const core::arch::Instruction *instruction, core::ir::Program *program) override;
};

}}} // namespace nc::arch::riscv

/* vim:set et sts=4 sw=4: */
