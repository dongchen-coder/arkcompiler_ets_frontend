/**
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "expressionStatement.h"

#include "ir/astDump.h"
#include "ir/expression.h"

namespace panda::es2panda::ir {
void ExpressionStatement::TransformChildren(const NodeTransformer &cb)
{
    expression_ = cb(expression_)->AsExpression();
}

void ExpressionStatement::Iterate(const NodeTraverser &cb) const
{
    cb(expression_);
}

void ExpressionStatement::Dump(ir::AstDumper *dumper) const
{
    dumper->Add({{"type", "ExpressionStatement"}, {"expression", expression_}});
}

void ExpressionStatement::Compile([[maybe_unused]] compiler::PandaGen *pg) const
{
    expression_->Compile(pg);
}

void ExpressionStatement::Compile([[maybe_unused]] compiler::ETSGen *etsg) const
{
    expression_->Compile(etsg);
}

checker::Type *ExpressionStatement::Check([[maybe_unused]] checker::TSChecker *checker)
{
    return expression_->Check(checker);
}

checker::Type *ExpressionStatement::Check([[maybe_unused]] checker::ETSChecker *checker)
{
    return expression_->Check(checker);
}
}  // namespace panda::es2panda::ir