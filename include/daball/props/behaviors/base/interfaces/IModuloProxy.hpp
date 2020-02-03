#pragma once
#include <cstddef>
#include <optional>
namespace daball::props::behaviors::base::interfaces {
    template<typename Identity_T>
    class IModuloProxy;
    template<template <typename> typename Identity_T, typename Subject_T>
    class IModuloProxy<Identity_T<Subject_T>>
    {
    public:
        virtual Subject_T operator%(Subject_T const& rh) = 0;
        virtual Subject_T operator%(Identity_T<Subject_T> const& rhp) = 0;
    };
}
