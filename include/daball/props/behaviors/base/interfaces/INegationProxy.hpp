#pragma once
namespace daball::props::behaviors::base::interfaces {
    template<typename Subject_T>
    class INegationProxy
    {
    public:
        virtual Subject_T operator-() const = 0;
    };
}
