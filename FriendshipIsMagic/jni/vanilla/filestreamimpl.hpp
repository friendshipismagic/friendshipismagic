
#pragma once

#include <string>
#include <fstream>

class FileStreamImpl {

    public:
        
        using FilePtr = std::fstream*;

        bool open(const std::string& name);

        std::string readAll();

        void close();

    private:
        FilePtr mFile;

};
