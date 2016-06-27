

INKSCAPE_COMMAND = "inkscape"

import glob
import sys
import os
from subprocess import call

if __name__ == "__main__":
    src_dir = sys.argv[1]
    dst_dir = sys.argv[2]
    files = glob.glob(os.path.join(src_dir, '*.svg'))

    for f in files:
        f_name = os.path.split(f)[1]
        out_f = os.path.splitext(f_name)[0] + ".png"
        dest = os.path.join(dst_dir, out_f)
        print (dest)
        call([INKSCAPE_COMMAND, "-f", f, "-e", dest, "-D"])

