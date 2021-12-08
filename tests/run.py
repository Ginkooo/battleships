from pathlib import Path
import os
import glob
import subprocess
from subprocess import PIPE

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
    outfile = f"{tests_folder}/{number}.out"

    proc = subprocess.Popen(f"./a.out", shell=True, stdout=PIPE, stdin=PIPE)
    proc.stdin.writelines(open(outfile, "rb").readlines())
    while True:
        line = proc.stdout.readline()
        print(line)
