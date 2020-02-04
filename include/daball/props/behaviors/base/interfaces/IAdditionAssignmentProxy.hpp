#pragma once
#include <cstddef>
#include <optional>
namespace daball::props::behaviors::base::interfaces {
    template<typename Signature_T>
    class IAdditionAssignmentProxy;
    template<template <typename> typename Identity_T, typename LHSubject_T, typename RHSubject_T>
    class IAdditionAssignmentProxy<Identity_T<LHSubject_T>&(RHSubject_T&&)>
    {
    public:
        virtual Identity_T<LHSubject_T> &operator+=(RHSubject_T &&newValue) = 0;
    };
    template<template <typename> typename Identity_T, typename LHSubject_T, typename RHSubject_T>
    class IAdditionAssignmentProxy<Identity_T<LHSubject_T>&(const RHSubject_T&)>
    {
    public:
        virtual Identity_T<LHSubject_T> &operator+=(const RHSubject_T &newValue) = 0;
    };
}
