//
// Created by 王镱霏 on 2/27/20.
//

#ifndef ASSIGNMENT6_ARRAY_SERIALIZE_H
#define ASSIGNMENT6_ARRAY_SERIALIZE_H

class Array_Serialize{
    FloatArray fa;
    StringArray sa;
public:Array_Serialize():fa(10),sa(10){
    }

public:Array_Serialize(FloatArray fa_i, StringArray sa_i):fa(fa_i),sa(sa_i){
    }
    char* serialize(Serializer s){
        s.write(fa);
        s.write(sa);
        return s.get();
    }
    Array_Serialize deserilize(Deserializer ds, char* buffer){
        FloatArray fa_o = ds.readFloatArray(buffer, sizeof(fa.data_)+sizeof(fa.capacity_)+sizeof(fa.length_));
        StringArray sa_o = ds.readStringArray(buffer, sizeof(sa._array.data_)+sizeof(sa._array.capacity_)+sizeof(sa._array.length_));
        Array_Serialize ans(fa_o, sa_o);
        return ans;
    }
    FloatArray get_Float_array(){
        return fa;
    }
    StringArray get_String_array(){
        return sa;
    }
};
#endif //ASSIGNMENT6_ARRAY_SERIALIZE_H
