#prama once

#include "tinyxml2.h"

inline XMLNode *deepCopy( const XMLNode *src, XMLDocument *destDoc )
{
    XMLNode *current = src->ShallowClone( destDoc );
    for( const XMLNode *child=src->FirstChild(); child; child=child->NextSibling() )
    {
        current->InsertEndChild( deepCopy( child, destDoc ) );
    }

    return current;
}

inline std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> accu;

    std::size_t last_pos = 0;
    std::size_t size = str.size();

    while(last_pos < size) {
        std::size_t next = str.find(delimiter, last_pos+1);
        accu.push_back(str.substr(last_pos,next-1-last_pos));
        last_pos = next+1;
    }

    return accu;
}

inline std::string extract(const std::string& str, char left, char right) {
    auto lpos = str.find(str, left);
    auto rpos = str.rfind(str, right);
    return str.substr(lpos, rpos-lpos);
}
