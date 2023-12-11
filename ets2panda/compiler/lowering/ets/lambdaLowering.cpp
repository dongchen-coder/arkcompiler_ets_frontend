/*
 * Copyright (c) 2021 - 2023 Huawei Device Co., Ltd.
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

#include "lambdaLowering.h"
#include "checker/checker.h"
#include "compiler/core/compilerContext.h"
#include "util/declgenEts2Ts.h"

namespace panda::es2panda::compiler {

std::string_view LambdaLowering::Name()
{
    return "lambda-lowering";
}

static ir::AstNode *ConvertExpression(checker::ETSChecker *const checker, ir::ArrowFunctionExpression *const arrow)
{
    auto *const function = arrow->Function();
    auto *const scope = function->Scope();
    auto *const expr = function->Body()->AsExpression();

    ArenaVector<ir::Statement *> statements(checker->Allocator()->Adapter());
    statements.emplace_back(checker->AllocNode<ir::ReturnStatement>(expr));
    auto *const block = checker->AllocNode<ir::BlockStatement>(checker->Allocator(), scope, std::move(statements));
    block->SetParent(function);

    function->SetBody(block);
    function->AddFlag(ir::ScriptFunctionFlags::HAS_RETURN);

    return arrow;
}

bool LambdaLowering::Perform(public_lib::Context *ctx, parser::Program *program)
{
    for (auto &[_, ext_programs] : program->ExternalSources()) {
        (void)_;
        for (auto *ext_prog : ext_programs) {
            Perform(ctx, ext_prog);
        }
    }

    checker::ETSChecker *const checker = ctx->checker->AsETSChecker();

    program->Ast()->TransformChildrenRecursively([checker](ir::AstNode *const node) -> ir::AstNode * {
        if (node->IsArrowFunctionExpression() &&
            node->AsArrowFunctionExpression()->Function()->Body()->IsExpression()) {
            return ConvertExpression(checker, node->AsArrowFunctionExpression());
        }

        return node;
    });

    return true;
}

bool LambdaLowering::Postcondition(public_lib::Context *ctx, const parser::Program *program)
{
    for (auto &[_, ext_programs] : program->ExternalSources()) {
        (void)_;
        for (auto *ext_prog : ext_programs) {
            if (!Postcondition(ctx, ext_prog)) {
                return false;
            }
        }
    }

    return !program->Ast()->IsAnyChild([](const ir::AstNode *node) {
        return node->IsArrowFunctionExpression() &&
               node->AsArrowFunctionExpression()->Function()->Body()->IsExpression();
    });
}

}  // namespace panda::es2panda::compiler