#include "filestreamimpl.hpp"
#include <fstream>

FileStreamImpl::FileStreamImpl() {
    mFile = nullptr;
}

bool FileStreamImpl::open(const std::string& name) {
    if (mFile) close();

    mFile = new std::fstream(name.c_str());
    if (*mFile) return true;
    return false;
}

std::string FileStreamImpl::readAll() {
    mFile->seekg (0, mFile->end);
    int length = mFile->tellg();
    mFile->seekg (0, mFile->beg);

    char * buffer = new char [length];

    mFile->read(buffer,length);

    std::string value (buffer);
    delete[] buffer;
    return value;
}

void FileStreamImpl::close() {
    if(mFile && *mFile) mFile->close();
    delete mFile;
    mFile = nullptr;
}
