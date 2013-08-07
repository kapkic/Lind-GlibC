
# Modifies ld.so's ELF Program Headers to get a version that NaCl's
# sel_ldr will run.
#
# For a discussion, see:
# http://code.google.com/p/nativeclient/issues/detail?id=156
# http://code.google.com/p/nativeclient/issues/detail?id=558

import struct
import sys


offset_e_type = 16
offset_e_phnum32 = 44
offset_e_phnum64 = 56

offset_ei_class = 4
elfclass32 = "\001"
elfclass64 = "\002"

ET_EXEC = 2
ET_DYN = 3


def main(args):
    if len(args) != 1:
        raise Exception("Usage: fixup <filename>")
    filename = args[0]
    fh = open(filename, "r+")
    
    def check(ty, offset, expected):
        fh.seek(offset)
        data = fh.read(struct.calcsize(ty))
        got = struct.unpack(ty, data)[0]
        if got != expected:
            raise AssertionError("Expected %s, got %s" % (expected, got))

    def replace(ty, offset, value):
        fh.seek(offset)
        fh.write(struct.pack(ty, value))

    # sel_ldr only accepts ELF objects with e_type=ET_EXEC.
    check("B", offset_e_type, ET_DYN)
    replace("B", offset_e_type, ET_EXEC)

    fh.close()


if __name__ == "__main__":
    main(sys.argv[1:])
