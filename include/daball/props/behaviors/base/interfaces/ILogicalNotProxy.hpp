#pragma once
namespace daball::props::behaviors::base::interfaces {
    template<typename Subject_T>
    class ILogicalNotProxy
    {
    public:
        virtual Subject_T operator!() const = 0;
    };
}
