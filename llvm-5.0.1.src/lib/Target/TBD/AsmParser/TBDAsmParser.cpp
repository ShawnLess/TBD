//===---- TBDAsmParser.cpp - Parse TBD assembly to MCInst instructions ----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/TBDMCTargetDesc.h"

#include "llvm/ADT/APInt.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/MC/MCParser/MCAsmLexer.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/TargetRegistry.h"

#include "AsmParser/TBDAsmParser.h"
#include "AsmParser/TBDOperand.h"
#include <sstream>

#define DEBUG_TYPE "avr-asm-parser"

namespace llvm {

//===----------------------------------------------------------------------===//
//Auto-generated Match Functions from Tablegen

// Maps from the set of all register names to a register number.
static unsigned MatchRegisterName(StringRef Name);

//===----------------------------------------------------------------------===//
// Implement the member functions

//ParserRegister
bool TBDAsmParser::ParseRegister(unsigned &RegNo, SMLoc &StartLoc, SMLoc &EndLoc){
  	RegNo 	= -1U	;

  	StartLoc = Parser.getTok().getLoc()	;

	if ( Parser.getTok().is(AsmToken::Identifier) ) {
		StringRef 	Name 	= Parser.getTok().getString()	;
				RegNo 	= MatchRegisterName(Name)	;
	}

  	EndLoc = Parser.getTok().getLoc();
	
	return ( RegNo == -1U );	
}
//ParseInstruction
//This will parse the opcode, operands
bool TBDAsmParser::ParseInstruction(ParseInstructionInfo &Info, StringRef Name,
                                SMLoc NameLoc, OperandVector &Operands){

        DEBUG(dbgs() << "parseOperand\n");

        bool bFirstOperand = true;
        while( getLexer().isNot( AsmToken::EndOfStatement) ) {

                if( !bFirstOperand )    eatComma()              ;
                else                    bFirstOperand = false   ;
                
                switch( getLexer().getKind() ) {
                        case AsmToken::Identifier:
                                if( !tryParseRegisterOperand( Operands ) )      
                                        return false; // Succesfully parsed to register
                                LLVM_FALLTHROUGH;
                        default:
                                return Error(Parser.getTok().getLoc(), "unexpected token in operand");
                }
                
        }        
        return true;
}

//ParseDirective
bool TBDAsmParser::ParseDirective( AsmToken  DirectiveID) { return true; }

//MatchAnd EmitInstruction
bool TBDAsmParser::MatchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                             OperandVector &Operands, MCStreamer &Out,
                             uint64_t &ErrorInfo,
                             bool MatchingInlineAsm){

  MCInst Inst;
  unsigned MatchResult =
      MatchInstructionImpl(Operands, Inst, ErrorInfo, MatchingInlineAsm);

  switch (MatchResult) {
        case Match_Success:  {
        
              Inst.setLoc(IDLoc);
              Out.EmitInstruction(Inst, STI);
              return false;
        }
        case Match_MissingFeature: return Error(IDLoc, "Missing Feature");
        case Match_InvalidOperand: return Error(IDLoc, "Invalid Operand");
        case Match_MnemonicFail:   return Error(IDLoc, "invalid instruction");
        default:                   return true;
  }
}


//===----------------------------------------------------------------------===//
// The help functions

// try to parse the register
bool TBDAsmParser::tryParseRegisterOperand(OperandVector &Operands) {
        unsigned        RegNum          ;
        SMLoc           StartLoc, EndLoc;

        bool    bPR = ParseRegister(RegNum, StartLoc, EndLoc) ;

        if( bPR ) return true; 
        else {
                AsmToken const &T = Parser.getTok();
                Operands.push_back(  TBDOperand::createReg( RegNum, T.getLoc(), T.getEndLoc() )  ) ;
                Parser.Lex(); // Eat register token.
                return false;
        }

}

//eat the comma
void TBDAsmParser::eatComma() {
        if( getLexer().is( AsmToken::Comma) )   Parser.Lex( );
        else    Error( getLexer().getLoc(), "Comma needed");
}
//===----------------------------------------------------------------------===//
// Register the Asm Parser
extern "C" void LLVMInitializeTBDAsmParser() {
  RegisterMCAsmParser<TBDAsmParser> X(getTheTBDTarget());
}

//===----------------------------------------------------------------------===//
// Include the generated file
#define GET_REGISTER_MATCHER
#define GET_MATCHER_IMPLEMENTATION
#include "TBDGenAsmMatcher.inc"

} // end of namespace llvm
