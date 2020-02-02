/*
 * boost_strategy.hpp - `props` project.
 * Author: David A. Ball, www.daball.me
 * License: Boost Software License v1
 */

#pragma once

#include "../signals/boost/BoostSignals2SlotHandler.hpp"
#include "../signals/boost/BoostSignals2SignalConnections.hpp"
#include "../signals/boost/BoostSignals2SignalEmitter.hpp"

#ifndef PROPS_STRATEGY_SELECTION
// define the strategy so that another strategy can't pollute the global scope
#define PROPS_STRATEGY_SELECTION boost

namespace daball::props {
    typedef BoostSignals2SignalConnection SignalConnection;
    typedef BoostSignals2SlotHandler SlotHandler;
    typedef BoostSignals2SignalEmitter SignalEmitter;
    typedef Boost2SignalsObservableProperty ObservableProperty;
}

#endif
