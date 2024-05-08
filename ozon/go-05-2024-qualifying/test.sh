#!/bin/bash

COLOR_BLACK=0
COLOR_RED=1
COLOR_GREEN=2
COLOR_YELLOW=3
COLOR_GREY=8

reset_color="$(tput sgr0)"

problem_number="$(echo "$1" | cut -d'-' -f1)"
exe_file="build/$1.out"

print_error() {
  local error_text="$1"
  local color_red="$(tput setaf $COLOR_RED)"
  echo "${color_red}ERROR: ${error_text}${reset_color}"
}

highlight () {
  local text="$1"
  local color="$2"
  local color_text="$(tput setab $color; tput setaf $COLOR_BLACK)"
  echo "${color_text} $text ${reset_color}"  
}

print_time () {
  local runtime=$1

  if (( $(echo "$runtime > 1000" | bc -l) )); then
    local color=$COLOR_RED
  elif (( $(echo "$runtime > 500" | bc -l) )); then
    local color=$COLOR_YELLOW
  else
    local color=$COLOR_GREY 
  fi

  local color_time="$(tput setaf $color)"
  printf "${color_time}%.0fms${reset_color}" "$runtime"
}

clear_line () {
  tput cuu1
  tput el
}

if [ ! -f "$exe_file" ]; then
  print_error "File '$exe_file' does not exist"
  tput bel
  exit 1
fi

tests_dir="tests/$problem_number"

if [ ! -d "$tests_dir" ]; then
  print_error "Tests directory does not exist"
  tput bel
  exit 1
fi

if ! which dos2unix &> /dev/null; then
  print_error "dos2unix not installed. Please install before running."
  tput bel
  exit 1
fi

tests=$(ls "$tests_dir" | sort -n)
for test_file in $tests
do
  if [[ "$test_file" =~ ^[0-9]+$ ]]; then
    test_num=$test_file
    test_input="${tests_dir}/${test_num}"
    test_output="${test_input}.a"
    test_name=$(printf "%02d." $test_num)

    echo "$test_name$(highlight "RUNS" $COLOR_YELLOW)"

    start_time=$(gdate +%s.%N)
    output=$($exe_file < "$test_input" | dos2unix)
    end_time=$(gdate +%s.%N)
    runtime=$(echo "($end_time - $start_time) * 1000" | bc)

    clear_line

    expected_output=$(cat "$test_output" | dos2unix)
    if diff -Z -q <(echo "$output") <(echo "$expected_output") > /dev/null ; then 
      echo "$test_name$(highlight "PASS" $COLOR_GREEN) $(print_time $runtime)"
    else
      echo "$test_name$(highlight "FAIL" $COLOR_RED)"
      diff -Z -y --color=auto <(echo "$output") <(echo "$expected_output")
      cat "$test_input" > in.txt
      echo "$output" > out.txt
      echo "$expected_output" > ref.txt
      exit 1
    fi
  fi
done
