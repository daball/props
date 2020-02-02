#pragma once

#include "../base/ObservableProperty.hpp"
#include "../signals/boost/BoostSignals2SignalConnection.hpp"
#include "../signals/boost/BoostSignals2SignalEmitter.hpp"
#include "../signals/boost/BoostSignals2SlotHandler.hpp"

using daball::props::base::ObservableProperty;
using daball::props::signals::boost::BoostSignals2SignalConnection;
using daball::props::signals::boost::BoostSignals2SignalEmitter;
using daball::props::signals::boost::BoostSignals2SlotHandler;

namespace daball::props::boost {
    template<typename Prop_T>
    using Boost2SignalsObservableProperty = ObservableProperty<Prop_T, BoostSignals2SignalEmitter, BoostSignals2SignalConnection, ::boost::function>;
}
