#include "frombytestobe.h"

int fromBytesToBE(const QByteArray &_bytes)
{
    int data = 0;
    for(auto& byte : _bytes){
        data<<=8;
        data += byte;
    }
    return data;
}
