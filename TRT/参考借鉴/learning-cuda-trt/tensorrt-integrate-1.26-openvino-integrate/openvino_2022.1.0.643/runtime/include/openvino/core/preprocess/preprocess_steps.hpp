// Copyright (C) 2018-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "openvino/core/core_visibility.hpp"
#include "openvino/core/preprocess/color_format.hpp"
#include "openvino/core/preprocess/resize_algorithm.hpp"
#include "openvino/core/type/element_type.hpp"

namespace ov {

class Node;

namespace preprocess {

/// \brief Preprocessing steps. Each step typically intends adding of some operation to input parameter
/// User application can specify sequence of preprocessing steps in a builder-like manner
/// \code{.cpp}
/// auto proc = PrePostProcessor(function);
/// proc.input().preprocess()
///                        .mean(0.2f)     // Subtract 0.2 from each element
///                        .scale(2.3f));   // then divide each element to 2.3
/// \endcode
class OPENVINO_API PreProcessSteps final {
    class PreProcessStepsImpl;
    std::unique_ptr<PreProcessStepsImpl> m_impl;
    friend class InputInfo;

    /// \brief Default empty internal constructor
    PreProcessSteps();

public:
    /// \brief Default destructor
    ~PreProcessSteps();

    /// \brief Add convert element type preprocess operation
    ///
    /// \param type Desired type of input.
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner
    PreProcessSteps& convert_element_type(const ov::element::Type& type = {});

    /// \brief Converts color format for user's input tensor. Requires source color format to be specified by
    /// InputTensorInfo::set_color_format.
    ///
    /// \param dst_format Destination color format of input image
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner
    PreProcessSteps& convert_color(const ov::preprocess::ColorFormat& dst_format);

    /// \brief Add scale preprocess operation
    /// Divide each element of input by specified value
    ///
    /// \param value Scaling value.
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner
    PreProcessSteps& scale(float value);

    /// \brief Add scale preprocess operation by specified array of scale values for each channel
    ///
    /// \param values Scaling values. Layout runtime info with channels dimension must be specified for input tensor
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner
    PreProcessSteps& scale(const std::vector<float>& values);

    /// \brief Add mean preprocess operation
    /// Subtract specified value from each element of input
    ///
    /// \param value Value to subtract from each element.
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner
    PreProcessSteps& mean(float value);

    /// \brief Add mean preprocess operation by specified array of mean values for each channel
    ///
    /// \param values Mean values. Layout runtime info with channels dimension must be specified for input tensor
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner
    PreProcessSteps& mean(const std::vector<float>& values);

    /// \brief Signature for custom preprocessing operation. Custom preprocessing operation takes one input node and
    /// produces one output node. For more advanced cases, client's code can use transformation passes over ov::Model
    /// directly
    ///
    /// \param node Input node for custom preprocessing operation (output of previous preprocessing operation)
    ///
    /// \return New node after applying custom preprocessing operation
    using CustomPreprocessOp = std::function<Output<Node>(const Output<Node>& node)>;

    /// \brief Add custom preprocess operation
    /// Client application can specify callback function for custom action
    ///
    /// \param preprocess_cb Client's custom preprocess operation.
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner
    PreProcessSteps& custom(const CustomPreprocessOp& preprocess_cb);

    /// \brief Add resize operation to known dimensions - Lvalue version.
    ///
    /// \param alg Resize algorithm.
    ///
    /// \param dst_height Desired height of resized image.
    ///
    /// \param dst_width Desired width of resized image.
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner.
    PreProcessSteps& resize(ResizeAlgorithm alg, size_t dst_height, size_t dst_width);

    /// \brief Add resize operation to model's dimensions.
    ///
    /// \param alg Resize algorithm.
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner.
    PreProcessSteps& resize(ResizeAlgorithm alg);

    /// \brief Add 'convert layout' operation to specified layout.
    ///
    /// \param dst_layout New layout after conversion. If not specified - destination layout is obtained from
    /// appropriate model input properties.
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner.
    ///
    /// Adds appropriate 'transpose' operation between user layout and target layout.
    /// Current implementation requires source and destination layout to have same number of dimensions
    ///
    /// Example: when user data has 'NHWC' layout (example is RGB image, [1, 224, 224, 3]) but model expects
    /// planar input image ('NCHW', [1, 3, 224, 224]). Preprocessing may look like this:
    ///
    /// \code{.cpp}
    ///     auto proc = PrePostProcessor(model);
    ///     proc.input().tensor().set_layout("NHWC"); // User data is NHWC
    ///     proc.input().preprocess().convert_layout("NCHW")) // model expects input as NCHW
    /// \endcode
    PreProcessSteps& convert_layout(const Layout& dst_layout = {});

    /// \brief Add convert layout operation by direct specification of transposed dimensions.
    ///
    /// \param dims Dimensions array specifying places for new axis. If not empty, array size (N) must match to input
    /// shape rank. Array values shall contain all values from 0 to N-1. If empty, no actual conversion will be added.
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner.
    ///
    /// Example: when user data has input RGB image {1x480x640x3} but model expects
    /// planar input image ('NCHW', [1, 3, 480, 640]). Preprocessing may look like this:
    ///
    /// \code{.cpp}
    /// auto proc = PrePostProcessor(function);
    /// proc.input().preprocess().convert_layout({0, 3, 1, 2});
    /// \endcode
    PreProcessSteps& convert_layout(const std::vector<uint64_t>& dims);

    /// \brief Reverse channels operation.
    ///
    /// \return Reference to 'this' to allow chaining with other calls in a builder-like manner.
    ///
    /// Adds appropriate operation which reverses channels layout. Operation requires layout having 'C'
    /// dimension Operation convert_color (RGB<->BGR) does reversing of channels also, but only for NHWC layout
    ///
    /// Example: when user data has 'NCHW' layout (example is [1, 3, 224, 224] RGB order) but model expects
    /// BGR planes order. Preprocessing may look like this:
    ///
    /// \code{.cpp}
    /// auto proc = PrePostProcessor(function);
    /// proc.input().tensor().set_layout("NCHW"); // User data is NCHW
    /// proc.input().preprocess().reverse_channels();
    /// \endcode
    ///
    PreProcessSteps& reverse_channels();
};

}  // namespace preprocess
}  // namespace ov
