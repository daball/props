/*
 * SignalEmitter.hpp - `props` project.
 * Author: David A. Ball, www.daball.me
 * License: Boost Software License v1
 */

#pragma once

#include "SignalConnection.hpp"
#include "SlotHandler.hpp"

namespace daball::props::signals::base {
    // HUGE THANKS TO super at Stack Overflow for this template template pattern!
    // Source: https://stackoverflow.com/questions/59787317/template-alias-of-a-more-generic-template-using-externally-defined-template-type

    template<typename Connection_T, template <typename> typename Functional_T, typename Signature_T>
    struct SignalEmitter; // Base declaration to match the specialization against

    template<typename Connection_T, template <typename> typename Functional_T, typename Return_T, typename ...Args_T>
    struct SignalEmitter<Connection_T, Functional_T, Return_T(Args_T...)> // Matching Return_T and Args_T against Signature_T
    {
    public:
        typedef Connection_T _Connection_T;
        typedef Functional_T<Return_T(Args_T...)> _Functional_T;
//        typedef Return_T Return_T;
//        typedef Signature_T Return_T(Args_T...);
        virtual Return_T trigger(Args_T ...args) = 0;
        virtual void cancelAll() = 0;
        virtual Connection_T onSignal(const SlotHandler<Functional_T, Return_T(Args_T...args)> &slotHandler) = 0;
        virtual void cancelOnSignal(const Connection_T &connection) = 0;
    };

//    template<typename SignalEmitter_T>
//    struct make_signal_emitter;
//
//    template<template <typename Signature_T> typename SignalEmitter_T, typename Signature_T>
//    struct make_signal_emitter<SignalEmitter_T<Signature_T>>;
//
//    template<template <typename, typename> typename SignalEmitter_T, typename Return_T, typename ...Args_T>
//    struct make_signal_emitter<SignalEmitter_T<Return_T, Args_T...>> {
//        typedef typename SignalEmitter_T<Return_T, Args_T...>::_Connection_T Connection_T;
//        typedef typename SignalEmitter_T<Return_T, Args_T...>::_Functional_T Functional_T;
//        SignalEmitter<Connection_T, Functional_T<Return_T(Args_T...)>, Return_T, Args_T...> operator() {
//            return new SignalEmitter_T<Return_T, ...Args_T>();
//        }
//    };
}
