import random
import os
import math


def build_go(filename):
    os.system(f"go build -o {exe_path}/{filename}.out {file_path}/{filename}.go")


prog_correct = "6"
prog_check = "6-heap"
file_path = os.path.dirname(os.path.realpath(__file__))
exe_path = file_path + "/build"

build_go(prog_correct)
build_go(prog_check)

while True:
    n = random.randint(1, 10)
    k = random.randint(1, 10)
    m = random.randint(1, 5)
    a = ""
    for _ in range(m):
        a += str(random.randint(0, int(math.log2(k)))) + " "
    test = f"1\n{n} {k}\n{m}\n{a}"
    correct = os.popen(f'echo "{test}" | {exe_path}/{prog_correct}.out').read()
    checking = os.popen(f'echo "{test}" | {exe_path}/{prog_check}.out').read()
    if correct != checking:
        print("WA at:")
        print(test)
        print("correct: ", correct.rstrip("\n"))
        print("result: ", checking.rstrip("\n"))
        break
