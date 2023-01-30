#include "llvm/Transforms/Scalar/DCE.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"
#include "llvm/Support/DebugCounter.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils/AssumeBundleBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Local.h"
using namespace llvm;



namespace {
  struct DeadCodeElimination : public FunctionPass {
    static char ID;
    DeadCodeElimination() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      std::vector<Instruction*> toRemove;

      for (auto &BB : F) {
        for (auto &I : BB) {
          if (isInstructionTriviallyDead(&I)) {
            toRemove.push_back(&I);
          }
        }
      }

      // Erase the dead instructions
      for (auto *I : toRemove) {
        I->eraseFromParent();
      }

      return !toRemove.empty();
    }
  };
}

char DeadCodeElimination::ID = 0;
static RegisterPass<DeadCodeElimination> X("dead-code-elimination", "Dead Code Elimination Pass", false, false);
