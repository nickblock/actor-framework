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

#include "caf/io/fwd.hpp"

#include "caf/io/network/operation.hpp"
#include "caf/io/network/native_socket.hpp"
#include "caf/io/network/datagram_handler.hpp"

namespace caf::io::network {

/// A concrete datagram_handler with a technology-dependent policy.
template <class ProtocolPolicy>
class datagram_handler_impl : public datagram_handler {
public:
  template <class... Ts>
  datagram_handler_impl(default_multiplexer& mpx, native_socket sockfd,
                        Ts&&... xs)
  : datagram_handler(mpx, sockfd),
  policy_(std::forward<Ts>(xs)...) {
    // nop
  }

  void handle_event(io::network::operation op) override {
    this->handle_event_impl(op, policy_);
  }

private:
  ProtocolPolicy policy_;
};

} // namespace caf
