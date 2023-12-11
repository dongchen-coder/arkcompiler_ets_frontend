/**
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef ES2PANDA_IR_ETS_TUPLE_H
#define ES2PANDA_IR_ETS_TUPLE_H

#include "ir/typeNode.h"

namespace panda::es2panda::ir {

class ETSTuple : public TypeNode {
public:
    using TupleSizeType = uint32_t;

    explicit ETSTuple(ArenaAllocator *const allocator)
        : TypeNode(AstNodeType::ETS_TUPLE), type_annotation_list_(allocator->Adapter())
    {
    }

    explicit ETSTuple(ArenaAllocator *const allocator, const TupleSizeType size)
        : TypeNode(AstNodeType::ETS_TUPLE), type_annotation_list_(allocator->Adapter()), size_(size)
    {
    }
    explicit ETSTuple(const ArenaVector<ir::TypeNode *> &type_list)
        : TypeNode(AstNodeType::ETS_TUPLE),
          type_annotation_list_(type_list),
          size_(static_cast<TupleSizeType>(type_list.size()))
    {
    }

    [[nodiscard]] TupleSizeType GetTupleSize() const
    {
        return size_;
    }

    [[nodiscard]] ArenaVector<ir::TypeNode *> GetTupleTypeAnnotationsList() const
    {
        return type_annotation_list_;
    }

    [[nodiscard]] bool HasSpreadType() const
    {
        return spread_type_ != nullptr;
    }

    void SetSpreadType(TypeNode *const new_spread_type)
    {
        spread_type_ = new_spread_type;
    }

    void SetTypeAnnotationsList(const ArenaVector<TypeNode *> &type_node_list)
    {
        type_annotation_list_ = type_node_list;
    }

    void TransformChildren(const NodeTransformer &cb) override;
    void Iterate(const NodeTraverser &cb) const override;
    void Dump(ir::AstDumper *dumper) const override;
    void Compile([[maybe_unused]] compiler::PandaGen *pg) const override;
    void Compile([[maybe_unused]] compiler::ETSGen *etsg) const override;
    checker::Type *Check([[maybe_unused]] checker::TSChecker *checker) override;
    checker::Type *Check([[maybe_unused]] checker::ETSChecker *checker) override;
    checker::Type *GetType([[maybe_unused]] checker::ETSChecker *checker) override;

    checker::Type *CalculateLUBForTuple(checker::ETSChecker *checker, ArenaVector<checker::Type *> &type_list,
                                        checker::Type *spread_type);

private:
    ArenaVector<TypeNode *> type_annotation_list_;
    TypeNode *spread_type_ {};
    TupleSizeType size_ {0};
};

}  // namespace panda::es2panda::ir

#endif /* ES2PANDA_IR_ETS_TUPLE_H */