//
// Created by 王镱霏 on 2/21/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <iostream>
//#include <fstream>
#include "schema.h"
#include "row.h"
#include "modified_dataframe.h"

ModifiedDataFrame* load_dataframe() {
    FILE *fPointer;
    fPointer = fopen("./datafile.txt", "r");
    if (fPointer == NULL) {
        std::cerr << "File wouldn't open:" << strerror(errno) << "\n" << std::endl;
        return nullptr;
    }
    //this is the order same as my dataset
    //"ISSIISSFFSSFSSSSSSSSSSSSFFFFFSFFSBBBBBBBBBBBBBBSSSS"
    Schema *sch = new Schema("ISSIISSFFFFFSISSSSSSSSSSFFFFFSFFSBBBBBBBBBBBBBSSSS");
    ModifiedDataFrame *mdf = new ModifiedDataFrame(*sch);
    char singleLine[1024];
    while(!feof(fPointer)){
        if(fgets(singleLine, 1024, fPointer) == NULL) break;

        Row r(*sch);
        int r_index = 0;
        char *pchar = nullptr;
        pchar = strtok(singleLine, ",");
        while(pchar){
            switch(r.col_type(r_index)){
                case 'I':
                case 'B':
                    {
                        int i = atoi(pchar);
                        if(r.col_type(r_index) == 'I')
                            r.set(r_index, i);
                        else
                            r.set(r_index, (bool) i);
                        break;
                    }
                case 'F':
                    {
                        float f = strtof(pchar, nullptr);
                        r.set(r_index, f);
                        break;
                    }
                case 'S':
                    {
                        String *s = new String(pchar);
                        r.set(r_index, s);
                        break;
                    }
                default:
                    assert(false);
            }
            pchar = strtok(NULL, ",");
            ++r_index;
        }

        mdf->add_row(r);
    }
    fclose(fPointer);

    return mdf;
}
