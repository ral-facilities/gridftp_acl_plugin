#!/bin/bash

cd build
lcov --directory . --zerocounters

# build the tests and then run them
ninja
./test/testPlugin

# process the reports
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/opt/rh/devtoolset-6/root/usr/include/c++/*' \
                            '/home/vagrant/src/build/googletest-src/googletest/include/gtest/*' \
                            --output-file coverage.info
lcov --list coverage.info

genhtml --output-directory coveragereportall --legend --show-details --branch-coverage coverage.info 