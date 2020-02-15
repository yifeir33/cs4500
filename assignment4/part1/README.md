# ReadMe
## Introduction
In our implementation, we used the Array class from last hw from the
previous assignment. And implemented based on the assignment already 
designed.

### row:
In row we used a union value to storage four types of data,
as following: 

```c++
 union Schema_Value {
        int i;
        float f;
        bool b;
        String *s;
    };
```
Then keep track of the width and the types in this row and the 
index in the dataframe, as well as the name of the string.

### column:
The column is being inheritanced by the different of types columns:
 IntColumn, FloatColumn, StringColumn, BoolColumn, and for each of 
  them it is implemented by an array of that type.
  


### schema:
ColumnName - StringArray  
RowName - StringArray  
ColumnType - IntArray  
Schema attracts the information of the column name, and row name
The column type shows the type of the column by tracking an 
integer

### dataframe:
schemas - Object array  
Schema keeps track of both the row and col information 

### rower:
With the interface already provided, we could inheritance different
type of the rower by writing a sub class. In our test, we did a test
such as GPA_culculator  used for map and a height filter
used for filter method.

## DataFrame example:
```c++
//create a schema
  Schema s("II");

  DataFrame df(s);
  Row  r(df.get_schema());
  for(size_t i = 0; i <  1000 * 1000; i++) {
    r.set(0,(int)i);
    r.set(1,(int)i+1);
    df.add_row(r);
  }
```





