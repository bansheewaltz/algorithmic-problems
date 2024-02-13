import sys
import json
import os


def solve():
    tests_cnt = int(input())
    for _ in range(tests_cnt):
        linecnt = int(input())
        json_str = "".join([next(sys.stdin) for _ in range(linecnt)])
        json_data = json.loads(json_str)
        infected_cnt = checkdir(json_data, False)
        print(infected_cnt)


def checkdir(json_data, is_infected):
    infected_cnt = 0
    if "files" in json_data:
        for file in json_data["files"]:
            if file.endswith(".hack"):
                is_infected = True
                break
        if is_infected:
            infected_cnt += len(json_data["files"])
    if "folders" in json_data:
        for folder in json_data["folders"]:
            infected_cnt += checkdir(folder, is_infected)
    return infected_cnt


if __name__ == "__main__":
    if os.environ.get("LOCAL_TESTING"):
        sys.stdin = open("in.txt")
    solve()
