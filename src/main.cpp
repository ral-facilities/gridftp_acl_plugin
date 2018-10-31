#include <stdio.h>
#include <iostream>
#include "./framework/logger/logger.h"
#include "./application/permissionsFormatter.h"

using namespace std;

static Logger logger;
static PermissionsFormatter permissionsFormatter;

int main(int argc, char *argv[]) {
  cout << "Hello, world!\n";

  logger.Init("/usr/tmp/", "trace");
  logger.LogInfo("Hello from the logs");

  for (int i = 0; i < argc; ++i) 
    cout << permissionsFormatter.ToString(argv[i]);
  
  cout << "my permissions are: " << permissionsFormatter.ToString("/home/vagrant/src/main.cpp");
}