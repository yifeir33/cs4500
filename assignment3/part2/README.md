# DataFrame API
Our DataFrame API provides a simple and abstract way to get data from the provided file without imposing
any real restrictions on the internal representation of the data. It provides a modular way to get data, 
and allows implementors to decided on their own error conditions. The abstract SorColumn class is the only other
API the user must follow, and while we provided snippets of how I envisioned constructing concrete classes, they could
also implement the classes in another way. It provides basic read access to the data, and allows one to name both columns
and rows to be more descripitive. 

# Example Use
To construct a DataFrame using our API, to allow flexability and reduce complexity,
our idea was to specify the number of columns and then set them to concrete implementations
over the data. For example, based on the site:
```cpp
SorColumn int_col = new IntColumn();
int_col.appendValue(2);
int_col.appendValue(3);
int_col.appendValue(5);
SorColumn str_col = new StringColumn();
str_col.appendValue("aa");
str_col.appendValue("bb");
str_col.appendValue("cc");
DataFrame df = new DataFrame(2);
df.setColumn(0, int_col);
df.setColumn(1, str_col);
```
This style lends itself well to loops to create the dataframe, though it is admittedly verbose it reduces complexity.

Then the user can retreive data from the constructed dataframe in an easy to understand format, that lends itself well to a switch case, eg:
```cpp
DataFrame df = new DataFrame(5);
// construction

size_t column = 4;
size_t row = 100;

switch(df.getColumnType()){
    case ColumnType::STRING:
        String *str = df.getString(column, row);
        // Do something with the value
        break;
    case ColumnType::BOOl:
        bool b = df.getBool(column, row);
        // Do something with the value
        break;
    case ColumnType::INTEGER:
        int i = df.getInt(column, row);
        // Do something with the value
        break;
    case ColumnType::FLOAT:
        double d = df.getFloat(column, row);
        // Do something with the value
        break;
    default:
        // unreachable
        break;
}

```
It also supports using column and row indices or names, eg:
```cpp
DataFrame df = new DataFrame(5);
// construction


const char* column = "mpg";
const char* row = "Mazda RX4";

switch(df.getColumnType()){
    case ColumnType::STRING:
        String *str = df.getString(column, row);
        // Do something with the value
        break;
    case ColumnType::BOOl:
        bool b = df.getBool(column, row);
        // Do something with the value
        break;
    case ColumnType::INTEGER:
        int i = df.getInt(column, row);
        // Do something with the value
        break;
    case ColumnType::FLOAT:
        double d = df.getFloat(column, row);
        // Do something with the value
        break;
    default:
        // unreachable
        break;
}

```
This allows easy implementation of the API, and allows the user to receive the value in the type
they expect without the use of unions. It also lends itself to a command pattern to retreive
data from the DataFrame. It allows the user to utilize C's native types with minimum overhead or confusion,
and gives the power to the user to manipulate the data they receive from the DataFrame. It can also print the data
to stdout easily: eg: `df.print()`.
