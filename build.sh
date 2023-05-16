#!/bin/bash
# run: chmod +x build_and_run.sh

cmake -S . -B build && cmake --build build --config Debug && ./build/Debug/ED2_Rework.exe ./input/tiktok_app_reviews.csv ./out/bin.bin