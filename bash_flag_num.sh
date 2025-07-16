#!/bin/bash

# This script outputs a number based on the provided flag.

if [[ -z "$1" ]]; then
  echo "Usage: $0 <flag>"
  echo "Flags: -a (outputs 10), -b (outputs 20), -c (outputs 30)"
  exit 1
fi

case "$1" in
  -a)
    echo 10
    ;;
  -b)
    echo 20
    ;;
  -c)
    echo 30
    ;;
  *)
    echo "Invalid flag: $1"
    echo "Accepted flags: -a, -b, -c"
    exit 1
    ;;
esac