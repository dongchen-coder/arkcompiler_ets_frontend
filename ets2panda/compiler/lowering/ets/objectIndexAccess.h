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
#pragma once

#ifndef ES2PANDA_COMPILER_LOWERING_OBJECT_INDEX_ACCESS_H
#define ES2PANDA_COMPILER_LOWERING_OBJECT_INDEX_ACCESS_H

#include "compiler/lowering/phase.h"

namespace panda::es2panda::parser {
class ETSParser;
}  // namespace panda::es2panda::parser

namespace panda::es2panda::compiler {

class ObjectIndexLowering : public Phase {
public:
    std::string_view Name() override;
    bool Perform(public_lib::Context *ctx, parser::Program *program) override;
    bool Postcondition(public_lib::Context *ctx, const parser::Program *program) override;

private:
    ir::Expression *ProcessIndexGetAccess(parser::ETSParser *parser, checker::ETSChecker *checker,
                                          ir::MemberExpression *member_expression) const;
    ir::Expression *ProcessIndexSetAccess(parser::ETSParser *parser, checker::ETSChecker *checker,
                                          ir::AssignmentExpression *assignment_expression) const;
};

}  // namespace panda::es2panda::compiler

#endif