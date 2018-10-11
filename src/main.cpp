#include <stdio.h>
#include <iostream>
#include "./framework/logger/logger.h"

using namespace std;

static Logger logger;

int main(int argc, char *argv[]) {
  cout << "Hello, world!\n";

  logger.Init("/usr/tmp/", "trace");
  logger.LogInfo("Hello from the logs");
}