/* The file is part of Snowman decompiler.             */
/* See doc/licenses.txt for the licensing information. */

//
// SmartDec decompiler - SmartDec is a native code to C/C++ decompiler
// Copyright (C) 2015 Alexander Chernov, Katerina Troshina, Yegor Derevenets,
// Alexander Fokin, Sergey Levin, Leonid Tsvetkov
//
// This file is part of SmartDec decompiler.
//
// SmartDec decompiler is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SmartDec decompiler is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SmartDec decompiler.  If not, see <http://www.gnu.org/licenses/>.
//

#include "IntelArchitecture.h"

#include <boost/range/adaptor/map.hpp>

#include <nc/common/Foreach.h>
#include <nc/common/Unreachable.h>
#include <nc/common/make_unique.h>

#include "CallingConventions.h"
#include "IntelInstructionAnalyzer.h"
#include "IntelInstructionDisassembler.h"
#include "IntelUniversalAnalyzer.h"
#include "IntelRegisters.h"
#include "IntelOperands.h"
#include "IntelMnemonics.h"

namespace nc {
namespace arch {
namespace intel {

IntelArchitecture::IntelArchitecture(Mode mode):
    mOperands(new IntelOperands(this))
{
    /* Init instruction analyzer. */
    mInstructionAnalyzer.reset(new IntelInstructionAnalyzer(this));
    setInstructionAnalyzer(mInstructionAnalyzer.get());

    /* Init universal analyzer. */
    static IntelUniversalAnalyzer universalAnalyzer;
    setUniversalAnalyzer(&universalAnalyzer);

    /* Init registers. */
    setRegisters(IntelRegisters::instance());

    /* Init mnemonics. */
    setMnemonics(IntelMnemonics::instance());

    /* Perform mode-dependent initialization. */
    switch(mode) {
    case REAL_MODE:
        setBitness(16);
        setInstructionPointer(IntelRegisters::ip());
        mStackPointer = IntelRegisters::sp();
        mBasePointer  = IntelRegisters::bp();
        addCallingConvention(std::make_unique<Cdecl16CallingConvention>(this));
        break;
    case PROTECTED_MODE:
        setBitness(32);
        setInstructionPointer(IntelRegisters::eip());
        mStackPointer = IntelRegisters::esp();
        mBasePointer  = IntelRegisters::ebp();
        addCallingConvention(std::make_unique<Cdecl32CallingConvention>(this));
        addCallingConvention(std::make_unique<Stdcall32CallingConvention>(this));
        break;
    case LONG_MODE:
        setBitness(64);
        setInstructionPointer(IntelRegisters::rip());
        mStackPointer = IntelRegisters::rsp();
        mBasePointer  = IntelRegisters::rbp();
        addCallingConvention(std::make_unique<AMD64CallingConvention>(this));
        addCallingConvention(std::make_unique<Microsoft64CallingConvention>(this));
        break;
    default:
        unreachable();
    }

    setByteOrder(ByteOrder::LittleEndian);
    setMaxInstructionSize(15);

    /* Init instruction disassembler. */
    mInstructionDisassembler.reset(new IntelInstructionDisassembler(this));
    setInstructionDisassembler(mInstructionDisassembler.get());
}

IntelArchitecture::~IntelArchitecture() {
    foreach(FpuStackOperand *operand, mFpuStackOperands | boost::adaptors::map_values) {
        delete operand;
    }
}

FpuStackOperand *IntelArchitecture::fpuStackOperand(int index) const {
    auto &result = mFpuStackOperands[index];
    if (!result) {
        result = new FpuStackOperand(index);
    }
    return result;
}

} // namespace intel
} // namespace arch
} // namespace nc

/* vim:set et sts=4 sw=4: */
