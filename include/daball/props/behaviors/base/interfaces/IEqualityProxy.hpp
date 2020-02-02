#pragma once

namespace daball::props::behaviors::base::interfaces {
    template<typename Identity_T>
    class IEqualityProxy;
    template<template <typename> typename Identity_T, typename Subject_T>
    class IEqualityProxy<Identity_T<Subject_T>>;
    template<template <typename> typename SubjectContainer_T, template <typename> typename Identity_T, typename Subject_T>
    class IEqualityProxy<SubjectContainer_T<Identity_T<Subject_T>>>
    {
    public:
        virtual bool operator==(Subject_T const& rh) const = 0;
        virtual bool operator==(SubjectContainer_T<Identity_T<Subject_T>> const& rhp) const = 0;
    };
}