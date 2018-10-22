#!/bin/bash

cppcheck --enable=all ./main.cpp ./framework 2>"build/cppcheck_result.txt"