#pragma once

namespace daball::props::behaviors::base::interfaces {
    template<typename Subject_T>
    class IArrowProxy
    {
    public:
        //* (dereference)
        /**
         * Returns a lvalue reference to the wrapped property value.
         * @return Prop_T const& reference to the wrapped property value.
         */
        virtual Subject_T *operator->() = 0;
    };
}