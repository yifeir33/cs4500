//
// Created by 王镱霏 on 2/27/20.
//
#include <netinet/in.h>

#ifndef ASSIGNMENT6_SOCKADDR_IN_SERIALIZE_H
#define ASSIGNMENT6_SOCKADDR_IN_SERIALIZE_H

class Sockaddr_in_Serialize{
    sockaddr_in sai;
public:Sockaddr_in_Serialize(sockaddr_in sai_i):sai(sai_i){
    }
    char* serialize(Serializer s){
        s.write(sai);
        return s.get();
    }
    Sockaddr_in_Serialize deserilize(Deserializer ds,char* buffer){
        sockaddr_in sai_o = ds.readSockAddrIn(buffer,sizeof(sai));

        Sockaddr_in_Serialize ans(sai_o);
        return ans;
    }
    sockaddr_in get_sai(){
        return sai;
    }

};
#endif //ASSIGNMENT6_SOCKADDR_IN_SERIALIZE_H
