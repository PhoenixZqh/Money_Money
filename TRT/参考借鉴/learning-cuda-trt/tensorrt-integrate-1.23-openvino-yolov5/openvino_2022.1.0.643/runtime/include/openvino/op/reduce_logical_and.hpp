// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "openvino/op/util/logical_reduction_keep_dims.hpp"

namespace ov {
namespace op {
namespace v1 {
/// \brief Performs a reduction using "logical and"
///
/// The reduction is performed over slices of the first input. The slices shape depends
/// on the values passed to the second input - the axes.
class OPENVINO_API ReduceLogicalAnd : public util::LogicalReductionKeepDims {
public:
    OPENVINO_OP("ReduceLogicalAnd", "opset1", util::LogicalReductionKeepDims, 1);
    BWDCMP_RTTI_DECLARATION;
    ReduceLogicalAnd() = default;
    /// \brief Constructs a ReduceLogicalAnd node.
    ///
    /// \param data - The input tensor with data to be reduced
    /// \param reduction_axes - The input tensor with information about axes over which
    /// the first tensor should be sliced prior to the reduction operation
    /// \param keep_dims - Indicates if the axes used for reduction should be held/kept
    ReduceLogicalAnd(const Output<Node>& data, const Output<Node>& reduction_axes, const bool keep_dims = false);

    std::shared_ptr<Node> clone_with_new_inputs(const OutputVector& new_args) const override;

    OPENVINO_SUPPRESS_DEPRECATED_START
    bool evaluate(const HostTensorVector& outputs, const HostTensorVector& inputs) const override;
    OPENVINO_SUPPRESS_DEPRECATED_END
    bool has_evaluate() const override;
};
}  // namespace v1
}  // namespace op
}  // namespace ov
