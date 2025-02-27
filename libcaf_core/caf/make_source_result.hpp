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

#include <tuple>

#include "caf/delegated.hpp"
#include "caf/detail/implicit_conversions.hpp"
#include "caf/fwd.hpp"
#include "caf/stream.hpp"
#include "caf/stream_slot.hpp"
#include "caf/stream_source.hpp"

namespace caf {

/// Returns a stream source with the slot ID of its first outbound path.
template <class DownstreamManager, class... Ts>
class make_source_result
  : public delegated<stream<typename DownstreamManager::output_type>, Ts...> {
public:
  // -- member types -----------------------------------------------------------

  /// Type of a single element.
  using output_type = typename DownstreamManager::output_type;

  /// Fully typed stream manager as returned by `make_source`.
  using source_type = stream_source<DownstreamManager>;

  /// Pointer to a fully typed stream manager.
  using source_ptr_type = intrusive_ptr<source_type>;

  /// The return type for `scheduled_actor::make_stage`.
  using stream_type = stream<output_type>;

  /// Type of user-defined handshake arguments.
  using handshake_arguments = std::tuple<Ts...>;

  // -- constructors, destructors, and assignment operators --------------------

  make_source_result() noexcept : slot_(0) {
    // nop
  }

  make_source_result(stream_slot slot, source_ptr_type ptr) noexcept
      : slot_(slot),
        ptr_(std::move(ptr)) {
    // nop
  }

  make_source_result(make_source_result&&) = default;
  make_source_result(const make_source_result&) = default;
  make_source_result& operator=(make_source_result&&) = default;
  make_source_result& operator=(const make_source_result&) = default;

  // -- properties -------------------------------------------------------------

  stream_slot outbound_slot() const noexcept {
    return slot_;
  }

  source_ptr_type& ptr() noexcept {
    return ptr_;
  }

  const source_ptr_type& ptr() const noexcept {
    return ptr_;
  }

private:
  stream_slot slot_;
  source_ptr_type ptr_;
};

/// @relates make_source_result
template <class DownstreamManager, class... Ts>
using make_source_result_t =
  make_source_result<DownstreamManager, detail::strip_and_convert_t<Ts>...>;

} // namespace caf

