/******************************************************************************
 *                       ____    _    _____                                   *
 *                      / ___|  / \  |  ___|    C++                           *
 *                     | |     / _ \ | |_       Actor                         *
 *                     | |___ / ___ \|  _|      Framework                     *
 *                      \____/_/   \_|_|                                      *
 *                                                                            *
 * Copyright 2011-2018 Dominik Charousset                                     *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 *                                                                            *
 * If you did not receive a copy of the license files, see                    *
 * http://opensource.org/licenses/BSD-3-Clause and                            *
 * http://www.boost.org/LICENSE_1_0.txt.                                      *
 ******************************************************************************/

#pragma once

#include <atomic>

#include "caf/config.hpp"

namespace caf::detail {

template<class T>
bool cas_weak(std::atomic<T>* obj, T* expected, T desired) {
# if (defined(CAF_CLANG) && CAF_COMPILER_VERSION < 30401)                      \
     || (defined(CAF_GCC) && CAF_COMPILER_VERSION < 40803)
  return std::atomic_compare_exchange_strong(obj, expected, desired);
# else
  return std::atomic_compare_exchange_weak(obj, expected, desired);
# endif
}

} // namespace caf

