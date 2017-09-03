import os
import sys

#pylint: disable=C0103

primitive_types = {
    "UChar"  : "unsigned char",
    "Uint8B" : "uint64_t",
    "Uint4B" : "uint32_t",
    "Uint2B" : "uint16_t",
    "Int8B"  : "int64_t",
    "Int4B"  : "int32_t",
    "Int2B"  : "int16_t",
    "Char"   : "char",
    "Void"   : "void",
    "Wchar"  : "wchar_t",
    "char"   : "char",
    "void"   : "void"
}

def SeperateTypeFromName(lines):
    name_offset = []
    _type = []

    for line in lines:
        if len(line) > 1:
            sep = line.split(' : ')

            if len(sep) != 2:
                raise AttributeError("Can't obtain types and names, probably invalid file.")
            else:
                name_offset.append(sep[0].strip().rstrip().strip('+'))
                _type.append(sep[1].strip().rstrip())

    return (name_offset, _type)

def SeperateOffsetsFromName(name_offset):
    offset = []
    name = []

    for i, line in enumerate(name_offset):
        offset.append(line.split(' ')[0])
        name.append(line.split(' ')[1])

    return (offset, name)


def CheckUnionLength(offsets):
    length = 0
    nOffsets = len(offsets)

    if nOffsets < 1:
        return length

    currOffset = offsets[0]

    for i in range(nOffsets):
        if i == 0:
            continue

        if offsets[i] == currOffset:
            length += 1
        else:
            break

    return length

def CheckBitFieldLength(types):
    retval = 0

    for i, _type in enumerate(types):
        if _type.startswith('Pos'):
            retval += 1
        else:
            break

#    if retval < 2:
#        raise TypeError("Are you sure you are parsing a bitfield?")

    return retval


'''
@return_value: If return value is "bit", call ParseCBitfields on the arrays to obtain a struct{}
'''
def ParseCType(windbg_type: str):
    c_type = primitive_types.get(windbg_type, "other")
    retval = c_type

    if c_type == "other":
        if windbg_type.startswith('Pos'):       #Should defer bitfield to other functions
            retval = "bit"

        elif windbg_type.startswith('['):       #Is array type
            tmp_list = windbg_type.split(' ')
            tmp_list = tmp_list[::-1]
            retval = ParseCType(tmp_list[0])
            for i in range(1, len(tmp_list)):
                if tmp_list[i].startswith('Ptr'):
                    retval += '*'
                else:
                    retval += tmp_list[i]

        elif windbg_type.startswith('Ptr'):
            tmp_list = windbg_type.split(' ')
            tmp_list = tmp_list[::-1]
            retval = ParseCType(tmp_list[0])

            for i in range(1, len(tmp_list)):
                if tmp_list[i].startswith('Ptr'):
                    retval += '*'
                pass    # Resolve pointer to arrays(? Does windows internal structs have these ?)

        else:                                   #Is type of other struct
            retval = windbg_type + ' '

    return retval

def PopListsFromFront(length, lists):
    for i in range(length):
        for i, _list in enumerate(lists):
            _list.pop(0)



def ParseCBitfields(lines, types, names, offsets, length, indent = 0):
    indent_line = ''
    var_indent = ''
    local_lines = []
    bitfield_length = 0
    _type = "char"
    curr_offset = offsets[0]
    for i in range(indent + 1):
        indent_line += '\t'

    var_indent = indent_line + '\t'

    for i in range(length):
        bitfield_length += int(types[i].split(', ')[1].split()[0])

    if bitfield_length > 8:
        _type = "int16_t"
    if bitfield_length > 16:
        _type = "int32_t"
    if bitfield_length > 32:
        _type = "int64_t"

    if length > 1:
        lines.append(indent_line + 'struct {')
    index = 0
    while index < length:
        bit = types[index].split(', ')[1].split()[0]
        lines.append(var_indent + _type.ljust(15, ' ') + names[index].ljust(25, ' ') + ' : ' + bit + ' ;')
        index += 1

    PopListsFromFront(length, [names, types, offsets])
    if length > 1:
        lines.append(indent_line + '} ;' + ''.ljust(20,' ') + '//' + curr_offset)
    return


def ParseCVariable(unfixed_type: str, name: str, offset: str):
    splitted_array = unfixed_type.split('[')
    fixed_type = ''
    if '[' in unfixed_type:
        fixed_type = unfixed_type[0:unfixed_type.find('[')]
    else:
        fixed_type = unfixed_type
    for i, arr in enumerate(splitted_array):
        if i != 0:
            name += '[' + arr

    retval = fixed_type
    retval = retval.ljust(15, ' ')
    name   += ';'
    retval += name.ljust(35, ' ')
    retval += '//' + offset

    return retval

def ParseCUnion(lines, offsets, names, types, union_length, indent = 0):
    indent_line = ''
    length_to_parse = union_length + 1

    for i in range(indent+1):
        indent_line += '\t'
    var_indent = indent_line + '\t'
    lines.append(indent_line + 'union {')

    index = 0

    while index < length_to_parse:

        _type = ParseCType(types[0])
        if _type == 'bit':
            bitLen = CheckBitFieldLength(types)
            _indent = 0
            if bitLen > 1:
                _indent += 1
            ParseCBitfields(lines, types, names, offsets, bitLen, _indent)
            index += bitLen
        else:
            lines.append(var_indent + ParseCVariable(_type, names[0], offsets[0]))
            PopListsFromFront(1, [names, types, offsets])
        index += 1

    lines.append(indent_line + '};')
    return


def GenerateHeader(name_offset, types):
    lines = []
    offsets, names = SeperateOffsetsFromName(name_offset)

    while len(names) > 0:

        union_length = CheckUnionLength(offsets)
        if union_length > 0:
            ParseCUnion(lines, offsets, names, types, union_length)
        else:
            _type = ParseCType(types[0])
            if _type != "bit":
                lines.append('\t' + ParseCVariable(_type, names[0], offsets[0]))
                PopListsFromFront(1, [names, types, offsets])
            else:
                bitLen = CheckBitFieldLength(types)
                ParseCBitfields(lines, types, names, offsets, bitLen)

    return lines



def parsefile(filepath):
    try:
        lines = []

        _file = open(filepath, 'r')
        lines = _file.readlines()

        for i, line in enumerate(lines):
            lines[i] = line.strip().rstrip('\n')


    finally:
        _file.close()

    name_offset, types = SeperateTypeFromName(lines)
    generated_header = GenerateHeader(name_offset, types)

    return generated_header



def getfile():
    while True:
        filename = input("Please enter .txt file name to parse : ")
        if filename.endswith(".txt") is False:
            filename += ".txt"

        filepath = os.path.join(os.getcwd(), filename)
        if os.path.exists(filepath) is False:
            print("Please enter a valid file name.")
        else:
            return filepath

def WriteHeader(filepath, contents, struct_name: str):
    with open(filepath, 'w') as f:
        f.write('struct ' + struct_name.upper() + ' {\n')
        for i, line in enumerate(contents):
            f.write(line)
            f.write('\n')

        f.write('}  ; \n')
    return


def main(argc, argv):
    filepath = None
    print(argc, argv)

    while filepath == None:
        if argc == 3:
            filepath = os.path.join(os.getcwd(), argv[1])
            if argv[1].endswith(".txt") is False:
                filepath += ".txt"
            if os.path.exists(filepath) == False:
                print(filepath + "does not exist.")
                filepath = None

        elif argc == 1:
            filepath = getfile()

        else:
            raise EnvironmentError("Call with 2 arguments, example: python dt2header.py input.txt struct_name")

    generated = parsefile(filepath)
    dirname = os.path.dirname(filepath)

    if argc == 1:
        filename = input("Enter the name of the struct :  ")
        final_file = filename + '.h'
        final_file = os.path.join(dirname, final_file)
    else:
        filename = argv[2]
        final_file = os.path.join(os.getcwd(), argv[2])
        if final_file.endswith(".h") is False:
            final_file += ".h"

    if os.path.exists(final_file):
        raise FileExistsError("File exists.")

    struct_name = filename
    WriteHeader(final_file, generated, struct_name)
    return




"""
End of function definitions
"""
if __name__ == '__main__':
    main(len(sys.argv), sys.argv)
