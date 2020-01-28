/*
 * SignalConnection.hpp - `props` project.
 * Author: David A. Ball, www.daball.me
 * License: Boost Software License v1
 */

#pragma once

namespace daball::props::signals::base {
    template<typename Connection_T>
    struct SignalConnection
    {
    private:
        Connection_T _connection;
    public:
        SignalConnection<Connection_T>()
        {
        }

        SignalConnection<Connection_T>(const Connection_T &connection):
                _connection{connection}
        {
        }

        Connection_T const& getConnection() const
        {
            return this->_connection;
        }

        void setConnection(Connection_T const &connection)
        {
            this->_connection = connection;
        }

        Connection_T &operator*()
        {
            return this->_connection;
        }

        Connection_T* operator->()
        {
            return &this->_connection;
        }

        operator Connection_T & ()
        {
            return this->_connection;
        }
    };
}
