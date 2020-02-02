#pragma once
namespace daball::props::behaviors::base::interfaces {
    template<typename Subject_T>
    class ISettable
    {
    public:
        virtual void set(Subject_T &newValue) = 0;
        virtual bool isSet() const = 0;
//        virtual void unset() = 0;
    };
}
