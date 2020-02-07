import sys
import random
import string
from enum import IntEnum


class ColumnType(IntEnum):
    STRING = 1
    FLOAT = 2
    INTEGER = 3
    BOOLEAN = 4


def gen_string():
    generated = ""
    length = random.randint(2, 20)
    for i in range(length):
        generated = generated + random.choice(string.ascii_letters)

    return generated


def gen_bool():
    return str(random.randint(0, 1))


def gen_float():
    return str(random.uniform(-1000000, 1000000))


def gen_int():
    return str(random.randint(-2147483648, 2147483647))


def gen_columns(col_count):
    col_types = [ColumnType.STRING, ColumnType.FLOAT,
                 ColumnType.INTEGER, ColumnType.BOOLEAN]
    generated = []
    for i in range(col_count):
        generated.append(random.choice(col_types))

    return generated


def generate_file(filename, col_count, row_count):
    print("Columns: {}, Rows: {}".format(col_count, row_count))
    columns = gen_columns(col_count)
    # print("Column types: {}".format(columns))
    with open(filename, 'w+') as f:
        for r in range(row_count):
            row_str = ""
            for col in columns:
                row_str = row_str + "<"
                val = None
                if col == ColumnType.STRING:
                    val = gen_string()
                elif col == ColumnType.FLOAT:
                    val = gen_float()
                elif col == ColumnType.INTEGER:
                    val = gen_int()
                elif col == ColumnType.BOOLEAN:
                    val = gen_bool()
                if val is None:
                    raise RuntimeError("No value generated")
                # print("Value: {}".format(val))
                row_str = row_str + val
                row_str = row_str + ">"
            row_str = row_str + "\n"
            # print("Row: {}".format(row_str))
            f.write(row_str)


if __name__ == '__main__':
    generate_file(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]))


