//===--- SimplifyIfCheck.cpp - clang-tidy----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "SimplifyIfCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace modernize {

void SimplifyIfCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  //Finder->addMatcher(functionDecl().bind("x"), this);
  Finder->addMatcher(conditionalOperator().bind("cond"), this);
}

void SimplifyIfCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *MatchedDecl = Result.Nodes.getNodeAs<ConditionalOperator>("cond");
  if (MatchedDecl->getTrueExpr()->getType()->isBooleanType() &&
      MatchedDecl->getFalseExpr()->getType()->isBooleanType())
  {
    if((MatchedDecl->getTrueExpr()->isCXX98IntegralConstantExpr(*Result.Context) &&
       MatchedDecl->getFalseExpr()->isCXX98IntegralConstantExpr(*Result.Context)) ||
       (MatchedDecl->getTrueExpr()->isCXX11ConstantExpr(*Result.Context) &&
       MatchedDecl->getFalseExpr()->isCXX11ConstantExpr(*Result.Context)))
    {
      diag(MatchedDecl->getLocStart(), "simplify it")
              << FixItHint::CreateInsertion(MatchedDecl->getLocStart(), "collapse it");
    }
  }
}

} // namespace modernize
} // namespace tidy
} // namespace clang
