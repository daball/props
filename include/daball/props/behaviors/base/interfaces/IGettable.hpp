#pragma once

namespace daball::props::behaviors::base::interfaces {
    template<typename Subject_T>
    class IGettable
    {
    public:
        virtual Subject_T &get() = 0;
    };
}
