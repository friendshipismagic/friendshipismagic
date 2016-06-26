#include "filestream.hpp"

#ifdef ANDROID_BUILD
    #include "../android/filestreamimpl.hpp"
#else
    #include "../vanilla/filestreamimpl.hpp"
#endif

FileStream::FileStream() {
    mImpl = new FileStreamImpl();
}

FileStream::~FileStream() {
    delete mImpl;
}

bool FileStream::open(const std::string& name) {
    return mImpl->open(name);
}

std::string FileStream::readAll() {
    return mImpl->readAll();
}

void FileStream::close() {
    mImpl->close();
}

