#pragma once
#include <cstddef>
#include <optional>
namespace daball::props::behaviors::base::interfaces {
    template<typename Signature_T>
    class IAssignmentProxy;
    template<template <typename> typename Identity_T, typename LHSubject_T>
    class IAssignmentProxy<Identity_T<LHSubject_T>&(::std::nullptr_t)>
    {
    public:
        virtual Identity_T<LHSubject_T> &operator=(const ::std::nullptr_t) = 0;
    };
    template<template <typename> typename Identity_T, typename LHSubject_T>
    class IAssignmentProxy<Identity_T<LHSubject_T>&(::std::nullopt_t)>
    {
    public:
        virtual Identity_T<LHSubject_T> &operator=(const ::std::nullopt_t) = 0;
    };
    template<template <typename> typename Identity_T, typename LHSubject_T, typename RHSubject_T>
    class IAssignmentProxy<Identity_T<LHSubject_T>&(RHSubject_T&&)>
    {
    public:
        virtual Identity_T<LHSubject_T> &operator=(RHSubject_T &&newValue) = 0;
    };
    template<template <typename> typename Identity_T, typename LHSubject_T, typename RHSubject_T>
    class IAssignmentProxy<Identity_T<LHSubject_T>&(const RHSubject_T&)>
    {
    public:
        virtual Identity_T<LHSubject_T> &operator=(const RHSubject_T &newValue) = 0;
    };
}
