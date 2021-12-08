from pathlib import Path
import os
import glob
import subprocess
from subprocess import PIPE, STDOUT

this_file = Path(__file__)
test_files = []
tests_folder = this_file.parent
source_folder = tests_folder.parent

os.chdir(source_folder)

c_files = glob.glob(f"*.c")

print(c_files)

subprocess.check_call(["/usr/bin/clang", *c_files])

print("compilation ended")


for file in sorted(glob.glob(f"{tests_folder}/*.in")):
    infile = tests_folder / file
    number, extension = file.split(".")
    outfile = f"{number}.out"

    cmd = f"{source_folder}/a.out"
    print(cmd)
    proc = subprocess.Popen(cmd, shell=True, stdout=PIPE, stdin=PIPE, stderr=PIPE)
    try:
        out, _ = proc.communicate(input=open(infile, "rb").read(), timeout=2)
    except:
        out, _ = proc.communicate()
    print(out)
