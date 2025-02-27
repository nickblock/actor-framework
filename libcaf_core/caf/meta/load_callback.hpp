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

#include <type_traits>

#include "caf/meta/annotation.hpp"

namespace caf::meta {

template <class F>
struct load_callback_t : annotation {
  load_callback_t(F&& f) : fun(f) {
    // nop
  }

  load_callback_t(load_callback_t&&) = default;

  load_callback_t(const load_callback_t&) = default;

  F fun;
};

template <class T>
struct is_load_callback : std::false_type {};

template <class F>
struct is_load_callback<load_callback_t<F>> : std::true_type {};

template <class F>
constexpr bool is_load_callback_v = is_load_callback<F>::value;

/// Returns an annotation that allows inspectors to call
/// user-defined code after performing load operations.
template <class F>
load_callback_t<F> load_callback(F fun) {
  return {std::move(fun)};
}

} // namespace caf

