/*
 * SlotHandler.hpp - `props` project.
 * Author: David A. Ball, www.daball.me
 * License: Boost Software License v1
 */

#pragma once

#include <functional>

namespace daball::props::signals::base {
    // HUGE THANKS TO super at Stack Overflow for this template template pattern!
    // Source: https://stackoverflow.com/questions/59787317/template-alias-of-a-more-generic-template-using-externally-defined-template-type

    template<template <typename> typename Functional_T, typename Signature_T>
    using SlotHandler = Functional_T<Signature_T>;

    template<typename Signature_T>
    using StdFunctionSlotHandler = SlotHandler<::std::function, Signature_T>;
}
