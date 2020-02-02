#pragma once

namespace daball::props::behaviors::base::interfaces {
    template<typename Subject_T>
    class ICoercionProxy
    {
    public:
        /**
         * Coerces a lvalue reference to the wrapped property value.
         * @return Prop_T const& reference to the wrapped property value.
         */
        virtual operator Subject_T const&() const = 0;
    };
}