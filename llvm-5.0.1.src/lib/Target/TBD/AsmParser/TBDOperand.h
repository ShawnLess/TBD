#ifndef LLVM_TBD_OPERAND_H
#define LLVM_TBD_OPERAND_H

#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"

namespace llvm {

class TBDOperand : public MCParsedAsmOperand {

private:
  struct RegisterImmediate {
    unsigned Reg;
    MCExpr const *Imm;
  };

private:
  enum TBDOperandKind { k_Imm, k_Reg, k_Tok, k_Mem } Kind;

  union {
    StringRef           Tok;
    RegisterImmediate   RegImm;
  };
  //remember the location
  SMLoc                 Start, End;

public:
        //instantiate with a Token
        TBDOperand(StringRef Tok, SMLoc const &S)
                : MCParsedAsmOperand(), Kind(k_Tok), Tok(Tok), Start(S), End(S) {}
        //instantiate with a regsiter number
        TBDOperand(unsigned Reg, SMLoc const &S, SMLoc const &E)
                : MCParsedAsmOperand(), Kind(k_Reg), RegImm({Reg, nullptr}), Start(S), End(E) {}
        //instantiate with a Expr/Imm
        TBDOperand(MCExpr const *Imm, SMLoc const &S, SMLoc const &E)
                : MCParsedAsmOperand(), Kind(k_Imm), RegImm({0, Imm}), Start(S), End(E) {}
        //TODO: instantiate with a Memory operation
public:
        //funcitons required by TBDGemAsmMather.inc 
        void addRegOperands(MCInst &Inst, unsigned N) const {
                assert(Kind == k_Reg && "Unexpected operand kind");
                assert(N == 1 && "Invalid number of operands!"); 
                Inst.addOperand(MCOperand::createReg(getReg()));
        }

        StringRef getToken() const {
                assert(Kind == k_Tok && "Invalid access!");
                return Tok;
        }

public:
        //pure virtual functions needs overwrite
        unsigned getReg() const {
                assert((Kind == k_Reg ) && "Invalid access!");
                return RegImm.Reg;
        }
        bool isReg() const { return Kind == k_Reg; }
        bool isImm() const { return Kind == k_Imm; }
        bool isToken() const { return Kind == k_Tok; }
        bool isMem() const { return Kind == k_Mem; }
        SMLoc getStartLoc() const { return Start; }
        SMLoc getEndLoc() const { return End; }

        virtual void print(raw_ostream &O) const {
                switch (Kind) {
                case k_Tok:
                        O << "Token: \"" << getToken() << "\"";
                        break;
                case k_Reg:
                        O << "Register: " << getReg();
                        break;
                case k_Imm:
                        O << "Immediate: \"" << *getImm() << "\"";
                        break;
                case k_Mem:
                        O << "Mem: Not Implement yet.";
                        break;
                }
                O << "\n";
        }
public:
        //other help functions
        const MCExpr *getImm() const {
                assert((Kind == k_Imm ) && "Invalid access!");
                return RegImm.Imm;
        }

        //create operands that can be pushed directly into the operand vector
        static std::unique_ptr<TBDOperand> createToken(StringRef Str, SMLoc S) {
                return make_unique<TBDOperand>(Str, S);
        }

        static std::unique_ptr<TBDOperand> createReg(unsigned RegNum, SMLoc S,
                                               SMLoc E) {
                return make_unique<TBDOperand>(RegNum, S, E);
        }

};

}
#endif
