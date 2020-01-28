/*
 * BoostSignals2SlotHandler.hpp - `props` project.
 * Author: David A. Ball, www.daball.me
 * License: Boost Software License v1
 */

#pragma once

#include <boost/function.hpp>
#include "daball/props/signals/base/SlotHandler.hpp"

using daball::props::signals::base::SlotHandler;

namespace daball::props::signals::boost {
    template<typename Signature_T>
    using BoostFunctionSlotHandler = SlotHandler<::boost::function, Signature_T>;

    template<typename Signature_T>
    using BoostSignals2SlotHandler = BoostFunctionSlotHandler<Signature_T>;
}
