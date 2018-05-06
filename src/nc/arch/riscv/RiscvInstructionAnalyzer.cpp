/* The file is part of Snowman decompiler. */
/* See doc/licenses.asciidoc for the licensing information. */

#include "RiscvInstructionAnalyzer.h"

#include <QCoreApplication>

#include <boost/range/size.hpp>

#include <nc/common/CheckedCast.h>
#include <nc/common/Foreach.h>
#include <nc/common/Unreachable.h>
#include <nc/common/make_unique.h>

#include <nc/core/arch/Capstone.h>
#include <nc/core/ir/Program.h>
#include <nc/core/irgen/Expressions.h>
#include <nc/core/irgen/InvalidInstructionException.h>

#include "RiscvArchitecture.h"
#include "RiscvInstruction.h"
#include "RiscvRegisters.h"

namespace nc {
namespace arch {
namespace riscv {

namespace {

class RiscvExpressionFactory: public core::irgen::expressions::ExpressionFactory<RiscvExpressionFactory> {
public:
    RiscvExpressionFactory(const core::arch::Architecture *architecture):
        core::irgen::expressions::ExpressionFactory<RiscvExpressionFactory>(architecture)
    {}
};

typedef core::irgen::expressions::ExpressionFactoryCallback<RiscvExpressionFactory> RiscvExpressionFactoryCallback;

NC_DEFINE_REGISTER_EXPRESSION(RiscvRegisters, z)
NC_DEFINE_REGISTER_EXPRESSION(RiscvRegisters, n)
NC_DEFINE_REGISTER_EXPRESSION(RiscvRegisters, c)
NC_DEFINE_REGISTER_EXPRESSION(RiscvRegisters, v)

NC_DEFINE_REGISTER_EXPRESSION(RiscvRegisters, less)
NC_DEFINE_REGISTER_EXPRESSION(RiscvRegisters, less_or_equal)
NC_DEFINE_REGISTER_EXPRESSION(RiscvRegisters, below_or_equal)

NC_DEFINE_REGISTER_EXPRESSION(RiscvRegisters, sp)
NC_DEFINE_REGISTER_EXPRESSION(RiscvRegisters, pc)

} // anonymous namespace

class RiscvInstructionAnalyzerImpl {
    Q_DECLARE_TR_FUNCTIONS(RiscvInstructionAnalyzerImpl)

    core::arch::Capstone capstone_;
    RiscvExpressionFactory factory_;
    core::ir::Program *program_;
    const RiscvInstruction *instruction_;
    core::arch::CapstoneInstructionPtr instr_;
    const cs_riscv *detail_;

public:
    RiscvInstructionAnalyzerImpl(const RiscvArchitecture *architecture):
        capstone_(CS_ARCH_RISCV, CS_MODE_32), factory_(architecture)
    {}

    void createStatements(const RiscvInstruction *instruction, core::ir::Program *program) {
        assert(instruction != nullptr);
        assert(program != nullptr);
    }

private:
    core::arch::CapstoneInstructionPtr disassemble(const RiscvInstruction *instruction) {
        capstone_.setMode(instruction->csMode());
        return capstone_.disassemble(instruction->addr(), instruction->bytes(), instruction->size());
    }

    void createCondition(core::ir::BasicBlock *conditionBasicBlock, core::ir::BasicBlock *bodyBasicBlock, core::ir::BasicBlock *directSuccessor) {
        using namespace core::irgen::expressions;
    }

    void createBody(core::ir::BasicBlock *bodyBasicBlock) {
        using namespace core::irgen::expressions;

  
    }

    void handleWriteback(core::ir::BasicBlock *bodyBasicBlock, int memOperandIndex) {
    }

    bool handleWriteToPC(core::ir::BasicBlock *bodyBasicBlock, int modifiedOperandIndex = 0) {
    }

    /*
     * \param bodyBasicBlock Valid pointer to a basic block.
     *
     * \return True iff the last instruction added before the current one
     *         to the basic block is an assignment lr = pc.
     */
    bool isReturnAddressSaved(const core::ir::BasicBlock *bodyBasicBlock) const {
        assert(bodyBasicBlock != nullptr);

    }

    unsigned int getOperandRegister(std::size_t index) const {
        if (index >= detail_->op_count) {
            throw core::irgen::InvalidInstructionException(tr("There is no operand %1.").arg(index));
        }

        const auto &operand = detail_->operands[index];

        if (operand.type == RISCV_OP_REG) {
            return operand.reg;
        } else {
            return RISCV_REG_INVALID;
        }
    }

    core::irgen::expressions::TermExpression operand(std::size_t index, SmallBitSize sizeHint = 32) const {
        assert(index < boost::size(detail_->operands));

        const auto &operand = detail_->operands[index];

        return core::irgen::expressions::TermExpression(createTermForOperand(operand, sizeHint));
    }

    static std::unique_ptr<core::ir::Term> createTermForOperand(const cs_riscv_op &operand, SmallBitSize sizeHint) {
    }

    static std::unique_ptr<core::ir::Term> createDereferenceAddress(const cs_riscv_op &operand) {
    }

    static std::unique_ptr<core::ir::Term> applyShift(const cs_riscv_op &operand, std::unique_ptr<core::ir::Term> result) {
    }

    static std::unique_ptr<core::ir::Term> ror(std::unique_ptr<core::ir::Term> a, std::unique_ptr<core::ir::Term> b) {
    }

    static std::unique_ptr<core::ir::Term> createShiftValue(const cs_riscv_op &operand) {
    }

    static std::unique_ptr<core::ir::Term> createRegisterAccess(int reg) {
        return RiscvInstructionAnalyzer::createTerm(getRegister(reg));
    }

    static const core::arch::Register *getRegister(int reg) {
    }
};

RiscvInstructionAnalyzer::RiscvInstructionAnalyzer(const RiscvArchitecture *architecture):
    impl_(std::make_unique<RiscvInstructionAnalyzerImpl>(architecture))
{}

RiscvInstructionAnalyzer::~RiscvInstructionAnalyzer() {}

void RiscvInstructionAnalyzer::doCreateStatements(const core::arch::Instruction *instruction, core::ir::Program *program) {
    impl_->createStatements(checked_cast<const RiscvInstruction *>(instruction), program);
}

}}} // namespace nc::arch::riscv

/* vim:set et sts=4 sw=4: */
