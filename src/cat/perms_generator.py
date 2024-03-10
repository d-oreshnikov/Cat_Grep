import sys
import itertools

flags = {
    'b',
    'e',
    'n',
    's',
    't',
}

return_str = ""
if sys.argv[1] == "flags":
    for i in range(len(flags)):
        flags_perms = set(itertools.combinations(flags, i+1))
        for flag in flags_perms:
            return_str += ' ' + "".join(flag) if i > 0 else "".join(flag) + ' '

print(return_str)
