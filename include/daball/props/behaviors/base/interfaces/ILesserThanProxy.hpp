#pragma once
namespace daball::props::behaviors::base::interfaces {
    template<typename Identity_T>
    class ILesserThanProxy;
    template<template <typename> typename Identity_T, typename Subject_T>
    class ILesserThanProxy<Identity_T<Subject_T>>
    {
    public:
        virtual bool operator<(Subject_T const& rh) const = 0;
        virtual bool operator<(Identity_T<Subject_T> const& rhp) const = 0;
    };
}
