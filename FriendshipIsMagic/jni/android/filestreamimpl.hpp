
#pragma once

#include <string>
#include <android/asset_manager.h>

class FileStreamImpl {

    public:
        
        using FilePtr = AAsset*;

        FileStreamImpl();

        bool open(const std::string& name);

        std::string readAll();

        void close();

    private:
        FilePtr mFile;

};
