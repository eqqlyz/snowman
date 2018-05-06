/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#include "CallingConventions.h"

#include <nc/common/make_unique.h>
#include <nc/core/ir/Statements.h>
#include <nc/core/ir/Terms.h>

#include "RiscvArchitecture.h"
#include "RiscvRegisters.h"

namespace nc {
namespace arch {
namespace riscv {

DefaultCallingConvention::DefaultCallingConvention():
    core::ir::calling::Convention(QLatin1String("Default"))
{
    setStackPointer(RiscvRegisters::sp()->memoryLocation());

    setFirstArgumentOffset(0);
    setArgumentAlignment(32);

    std::vector<core::ir::MemoryLocation> args;
    args.push_back(RiscvRegisters::r0()->memoryLocation());
    args.push_back(RiscvRegisters::r1()->memoryLocation());
    args.push_back(RiscvRegisters::r2()->memoryLocation());
    args.push_back(RiscvRegisters::r3()->memoryLocation());
    addArgumentGroup(std::move(args));

    addReturnValueLocation(RiscvRegisters::r0()->memoryLocation());

    addEnterStatement(std::make_unique<core::ir::Assignment>(
        std::make_unique<core::ir::MemoryLocationAccess>(RiscvRegisters::lr()->memoryLocation()),
        std::make_unique<core::ir::Intrinsic>(core::ir::Intrinsic::RETURN_ADDRESS, RiscvRegisters::lr()->size())
    ));
}

}}} // namespace nc::arch::riscv

/* vim:set et sts=4 sw=4: */
