// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <memory>

#include "openvino/op/util/unary_elementwise_arithmetic.hpp"

namespace ov {
namespace op {
namespace v3 {
/// \brief Elementwise inverse hyperbolic cos operation.
///
class OPENVINO_API Acosh : public util::UnaryElementwiseArithmetic {
public:
    OPENVINO_OP("Acosh", "opset4", util::UnaryElementwiseArithmetic, 3);
    BWDCMP_RTTI_DECLARATION;

    /// \brief Constructs an Acosh operation.
    Acosh() = default;
    /// \brief Constructs an Acosh operation.
    ///
    /// \param arg Output that produces the input tensor.<br>
    /// `[d1, ...]`
    ///
    /// Output `[d1, ...]`
    ///
    Acosh(const Output<Node>& arg);

    std::shared_ptr<Node> clone_with_new_inputs(const OutputVector& new_args) const override;
    bool visit_attributes(AttributeVisitor&) override {
        return true;
    }
    OPENVINO_SUPPRESS_DEPRECATED_START
    bool evaluate(const HostTensorVector& outputs, const HostTensorVector& inputs) const override;
    OPENVINO_SUPPRESS_DEPRECATED_END
    bool has_evaluate() const override;
};
}  // namespace v3
}  // namespace op
}  // namespace ov
