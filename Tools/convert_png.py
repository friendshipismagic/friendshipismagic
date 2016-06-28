

INKSCAPE_COMMAND = "inkscape"

import glob
import sys
import os
from subprocess import call

if __name__ == "__main__":
    src_dir = sys.argv[1]
    dst_dir = sys.argv[2]
    files = glob.glob(os.path.join(src_dir, '**/*.svg'), recursive=True)

    for f in files:
        #f_name = os.path.split(f)[1]
        f_name = f
        out_f = os.path.splitext(f_name)[0] + ".png"
        dest = os.path.join(dst_dir, out_f)
        print (dest)
        directory = os.path.dirname(dest)
        try:
            os.makedirs(directory)
        except:
            pass
        call([INKSCAPE_COMMAND, "-f", f, "-e", dest, "-D"])
        print()

