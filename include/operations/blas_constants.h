/***************************************************************************
 *
 *  @license
 *  Copyright (C) Codeplay Software Limited
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  For your convenience, a copy of the License has been included in this
 *  repository.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  SYCL-BLAS: BLAS implementation using SYCL
 *
 *  @filename blas_constants.h
 *
 **************************************************************************/

#ifndef SYCL_BLAS_CONSTANTS_H
#define SYCL_BLAS_CONSTANTS_H

#include <complex>
#include <limits>
//#include <utility>
#include "blas_meta.h"
namespace blas {

/*!
@brief Container for a scalar value and an index.
*/
template <typename ix_t, typename val_t>
struct IndexValueTuple {
  using value_t = val_t;
  using index_t = ix_t;

  index_t ind;
  value_t val;

  constexpr explicit IndexValueTuple(index_t _ind, value_t _val)
      : ind(_ind), val(_val){};
  SYCL_BLAS_INLINE index_t get_index() const { return ind; }
  SYCL_BLAS_INLINE value_t get_value() const { return val; }
};

/*!
@brief Enum class used to indicate a constant value associated with a type.
*/
enum class const_val : int {
  zero = 0,
  one = 1,
  m_one = -1,
  two = 2,
  m_two = -2,
  max = 3,
  min = 4,
  abs_max = 5,
  abs_min = 6,
};

/*!
@brief Template struct used to represent constants within a compile-time
expression tree, each instantiation will have a static constexpr member
variable of the type value_t initialized to the specified constant.
@tparam value_t Value type of the constant.
@tparam kIndicator Enumeration specifying the constant.
*/
template <typename value_t, const_val Indicator>
struct constant {
  constexpr static SYCL_BLAS_INLINE value_t value() {
    return static_cast<value_t>(Indicator);
  }
};

template <typename value_t>
struct constant<value_t, const_val::max> {
  constexpr static SYCL_BLAS_INLINE value_t value() {
    return std::numeric_limits<value_t>::max();
  }
};

template <typename value_t>
struct constant<value_t, const_val::min> {
  constexpr static SYCL_BLAS_INLINE value_t value() {
    return std::numeric_limits<value_t>::min();
  }
};

template <typename value_t>
struct constant<value_t, const_val::abs_max> {
  constexpr static SYCL_BLAS_INLINE value_t value() {
    return std::numeric_limits<value_t>::max();
  }
};

template <typename value_t>
struct constant<value_t, const_val::abs_min> {
  constexpr static SYCL_BLAS_INLINE value_t value() {
    return static_cast<value_t>(0);
  }
};

template <typename value_t, const_val Indicator>
struct constant<std::complex<value_t>, Indicator> {
  constexpr static SYCL_BLAS_INLINE std::complex<value_t> value() {
    return std::complex<value_t>(constant<value_t, Indicator>::value(),
                                 constant<value_t, Indicator>::value());
  }
};

template <typename iv_type, const_val IndexIndicator, const_val ValueIndicator>
struct constant_pair {
  constexpr static SYCL_BLAS_INLINE iv_type value() {
    return iv_type(
        constant<typename iv_type::index_t, IndexIndicator>::value(),
        constant<typename iv_type::value_t, ValueIndicator>::value());
  }
};

}  // namespace blas

#endif  // BLAS_CONSTANTS_H
