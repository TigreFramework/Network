//
// Created by Pedro Soares on 03/07/16.
//

#ifndef NETWORKMANAGER_SOCKET_H
#define NETWORKMANAGER_SOCKET_H

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <String/String.h>

namespace Tigre {

    class SocketException : public std::exception {
    public:
        /** Constructor (C strings).
         *  @param message C-style string error message.
         *                 The string contents are copied upon construction.
         *                 Hence, responsibility for deleting the \c char* lies
         *                 with the caller.
         */
        explicit SocketException(const char* message):
                msg_(message)
        {
        }

        /** Constructor (C++ STL strings).
         *  @param message The error message.
         */
        explicit SocketException(const std::string& message):
                msg_(message)
        {}

        /** Destructor.
         * Virtual to allow for subclassing.
         */
        virtual ~SocketException() throw (){}

        /** Returns a pointer to the (constant) error description.
         *  @return A pointer to a \c const \c char*. The underlying memory
         *          is in posession of the \c Exception object. Callers \a must
         *          not attempt to free the memory.
         */
        virtual const char* what() const throw (){
            return msg_.c_str();
        }

    protected:
        /** Error message.
         */
        std::string msg_;

    };

    enum SocketType {
        TCP,
        UDP
    };

    class Socket {

        public:
            Socket(Tigre::String host, int port, SocketType type);
            ~Socket();
            void Bind(int clients=5);
            void Connect();
            Socket * Accept();
            void Write(String data);
            void Write(char * data);
            String Read(int size=2048);
            void Read(void *buffer, int size);
            void Close();

        private:
            Socket(int socket);
            int socket_;
            struct sockaddr_in config;
            socklen_t config_len;
            bool conected = false;

    };

}


#endif //NETWORKMANAGER_SOCKET_H
