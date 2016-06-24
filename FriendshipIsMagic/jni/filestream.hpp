
#pragma once

#include <string>

class FileStreamImpl;

class FileStream {

    public:
        FileStream();
        ~FileStream();
        
        bool open(const std::string& name);

        std::string readAll();

        void close();

    private:
        FileStreamImpl* mImpl;
};
