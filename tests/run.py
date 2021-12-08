from pathlib import Path
import os
import glob
import subprocess
from subprocess import PIPE, STDOUT
import difflib

this_file = Path(__file__)
test_files = []
tests_folder = this_file.parent
source_folder = tests_folder.parent

os.chdir(source_folder)

c_files = glob.glob(f"*.c")

print(c_files)

subprocess.check_call(["/usr/bin/clang", "-lm", *c_files])

print("compilation ended")


for file in sorted(
    glob.glob(f"{tests_folder}/*.in"),
    key=lambda name: int(name.split("/")[-1].split(".")[0]),
):
    infile = tests_folder / file
    number, extension = file.split(".")
    outfile = f"{number}.out"

    cmd = f"{source_folder}/a.out"
    proc = subprocess.Popen(cmd, shell=True, stdout=PIPE, stdin=PIPE, stderr=STDOUT)
    try:
        out, _ = proc.communicate(input=open(infile, "rb").read(), timeout=2)
    except:
        out, _ = proc.communicate()

    equal = out.decode() == open(outfile).read()
    if not equal:
        print("Got:")
        print(out.decode())
        print()
        print("Expected:")
        print(open(outfile).read())
        print("Input:")
        print(infile.read_text())
        input()
