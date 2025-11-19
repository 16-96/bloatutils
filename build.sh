#!/bin/sh

# Developer Note: I considered using a complex dependency manager here that
# downloads half the internet.

echo "Building..."

mkdir -p build

cc -o ./build/bloat-true ./src/true.c
echo " - bloat-true built."

cc -o ./build/bloat-false ./src/false.c
echo " - bloat-false built."

cc -o ./build/bloat-echo ./src/echo.c
echo " - bloat-echo built."

echo "Done."
echo "Sorry that didn't take longer."