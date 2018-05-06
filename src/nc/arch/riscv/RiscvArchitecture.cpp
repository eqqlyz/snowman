/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#include "RiscvArchitecture.h"

#include <nc/common/make_unique.h>

#include <nc/core/MasterAnalyzer.h>

#include "RiscvDisassembler.h"
#include "RiscvInstruction.h"
#include "RiscvInstructionAnalyzer.h"
#include "RiscvRegisters.h"
#include "CallingConventions.h"

namespace nc {
namespace arch {
namespace riscv {

RiscvArchitecture::RiscvArchitecture(ByteOrder byteOrder):
    byteOrder_(byteOrder)
{
    if (byteOrder == ByteOrder::LittleEndian) {
        setName(QLatin1String("riscv-le"));
    } else {
        setName(QLatin1String("riscv-be"));
    }
    setBitness(32);
    setMaxInstructionSize(RiscvInstruction::maxSize());

    setRegisters(RiscvRegisters::instance());

    static core::MasterAnalyzer masterAnalyzer;
    setMasterAnalyzer(&masterAnalyzer);

    addCallingConvention(std::make_unique<DefaultCallingConvention>());
}

RiscvArchitecture::~RiscvArchitecture() {}

ByteOrder RiscvArchitecture::getByteOrder(core::ir::Domain domain) const {
    if (domain == core::ir::MemoryDomain::MEMORY ||
        domain == core::ir::MemoryDomain::STACK)
    {
        return byteOrder_;
    } else {
        return ByteOrder::LittleEndian;
    }
}

std::unique_ptr<core::arch::Disassembler> RiscvArchitecture::createDisassembler() const {
    return std::make_unique<RiscvDisassembler>(this);
}

std::unique_ptr<core::irgen::InstructionAnalyzer> RiscvArchitecture::createInstructionAnalyzer() const {
    return std::make_unique<RiscvInstructionAnalyzer>(this);
}

}}} // namespace nc::arch::riscv

/* vim:set et sts=4 sw=4: */
