/*
 * BoostSignals2SignalEmitter.hpp - `props` project.
 * Author: David A. Ball, www.daball.me
 * License: Boost Software License v1
 */

#pragma once

#include <boost/signals2.hpp>
#include "BoostSignals2SignalConnection.hpp"
#include "BoostSignals2SlotHandler.hpp"
#include "daball/props/signals/base/SignalEmitter.hpp"

using daball::props::signals::base::SignalEmitter;

namespace daball::props::signals::boost {
    // HUGE THANKS TO super at Stack Overflow for this template template pattern!
    // Source: https://stackoverflow.com/questions/59787317/template-alias-of-a-more-generic-template-using-externally-defined-template-type

    template<typename Signature_T>
    class BoostSignals2SignalEmitterBase;

    template<typename Return_T, typename ...Args_T>
    class BoostSignals2SignalEmitterBase<Return_T(Args_T...)>:
            public SignalEmitter</* Connection_T = */ BoostSignals2SignalConnection,
                                 /* Functional_T = */ BoostSignals2SlotHandler,
                                 /* Signature_T  = */ Return_T(Args_T...)> {
    protected:
        ::boost::signals2::signal<Return_T(Args_T...)> signal;
    public:
        virtual void cancelAll() {
            this->signal.disconnect_all_slots();
        }

        virtual BoostSignals2SignalConnection onSignal(const BoostSignals2SlotHandler<Return_T(Args_T...)> &slotHandler) {
            return this->signal.connect(slotHandler);
        }

        virtual void cancelOnSignal(const BoostSignals2SignalConnection &connection) {
            connection.getConnection().disconnect();
        }
    };

    template<typename Signature_T>
    class BoostSignals2SignalEmitter;

    template<typename Return_T, typename ...Args_T>
    class BoostSignals2SignalEmitter<Return_T(Args_T...)>:
            public BoostSignals2SignalEmitterBase<Return_T(Args_T...)> {
    public:
        BoostSignals2SignalEmitter() {}

        virtual Return_T trigger(Args_T...args) {
            return *this->signal(args...);
        }
    };

    template<typename ...Args_T>
    class BoostSignals2SignalEmitter<void(Args_T...)>:
            public BoostSignals2SignalEmitterBase<void(Args_T...)> {
    public:
        BoostSignals2SignalEmitter() {}

        virtual void trigger(Args_T...args) {
            this->signal(args...);
        }
    };
}
