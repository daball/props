#pragma once

#include <boost/signals2.hpp>
#include "../base/Observable.hpp"
#include "../../signals/boost/BoostSignals2SignalEmitter.hpp"
#include "../../signals/boost/BoostSignals2SignalConnection.hpp"
#include "../../signals/boost/BoostSignals2SlotHandler.hpp"

using daball::props::behaviors::base::Observable;
using daball::props::signals::boost::BoostSignals2SignalEmitter;
using daball::props::signals::boost::BoostSignals2SignalConnection;
using daball::props::signals::boost::BoostSignals2SlotHandler;

namespace daball::props::behaviors::boost {
//    template<typename Subject_T, typename ...Args_T>
//    class BoostObservable:
//            public BaseObservable<Subject_T, BoostSignals2SignalEmitter, BoostSignals2SignalConnection, ::boost::function, void(Args_T...)>
//    {
//    };

    template<typename Subject_T, typename ...Args_T>
    using BoostObservable = Observable<Subject_T, BoostSignals2SignalEmitter, BoostSignals2SignalConnection, ::boost::function, void(Args_T...)>;
}