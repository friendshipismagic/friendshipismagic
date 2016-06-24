#include "filestreamimpl.hpp"
#include <SFML/System/NativeActivity.hpp>
#include <android/native_activity.h>

FileStreamImpl::FileStreamImpl() {
    mFile = nullptr;
}

bool FileStreamImpl::open(const std::string& name) {
    if (mFile) close();

    mFile = AAssetManager_open(sf::getNativeActivity()->assetManager, name.c_str(), AASSET_MODE_UNKNOWN);
    if (mFile) return true;
    return false;
}

std::string FileStreamImpl::readAll() {
    if(!mFile) return "";
    std::size_t size = AAsset_getLength(mFile);
    char buffer[size];
    AAsset_read(mFile,buffer,size);
    return std::string(buffer);
}

void FileStreamImpl::close() {
    AAsset_close(mFile);
}
