#pragma once

namespace daball::props::behaviors::base::interfaces {
    template<typename Subject_T>
    class IPointerProxy
    {
    public:
        //* (dereference)
        /**
         * Returns a lvalue reference to the wrapped property value.
         * @return Prop_T const& reference to the wrapped property value.
         */
        virtual Subject_T const &operator*() = 0;
    };
}