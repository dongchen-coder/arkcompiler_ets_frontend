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

#ifndef ES2PANDA_IR_EXPRESSION_FUNCTION_EXPRESSION_H
#define ES2PANDA_IR_EXPRESSION_FUNCTION_EXPRESSION_H

#include "ir/expression.h"

namespace panda::es2panda::ir {
class ScriptFunction;

class FunctionExpression : public Expression {
public:
    explicit FunctionExpression(ScriptFunction *func) : Expression(AstNodeType::FUNCTION_EXPRESSION), func_(func) {}

    const ScriptFunction *Function() const
    {
        return func_;
    }

    ScriptFunction *Function()
    {
        return func_;
    }

    void TransformChildren(const NodeTransformer &cb) override;
    void Iterate(const NodeTraverser &cb) const override;
    void Dump(ir::AstDumper *dumper) const override;
    void Compile([[maybe_unused]] compiler::PandaGen *pg) const override;
    void Compile(compiler::ETSGen *etsg) const override;
    checker::Type *Check([[maybe_unused]] checker::TSChecker *checker) override;
    checker::Type *Check([[maybe_unused]] checker::ETSChecker *checker) override;

private:
    ScriptFunction *func_;
};
}  // namespace panda::es2panda::ir

#endif