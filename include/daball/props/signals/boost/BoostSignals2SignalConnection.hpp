/*
 * BoostSignals2SignalConnection.hpp - `props` project.
 * Author: David A. Ball, www.daball.me
 * License: Boost Software License v1
 */

#pragma once

#include <boost/signals2.hpp>
#include "daball/props/signals/base/SignalConnection.hpp"

using daball::props::signals::base::SignalConnection;

namespace daball::props::signals::boost {
    using BoostSignals2SignalConnection = SignalConnection<::boost::signals2::connection>;
}
