#include <stdio.h>
#include <iostream>
#include "./framework/logger/logger.h"
#include "./application/permissionsReader.h"
#include "./application/FileInfoProvider.h"

using namespace std;

static Logger logger;
PermissionsReader permissionsReader;
FileInfoProvider fileInfoProvider;

int main(int argc, char *argv[]) {
  cout << "Hello, world!\n";

  logger.Init("/usr/tmp/", "trace");
  logger.LogInfo("Hello from the logs");
  
  for (int i = 1; i < argc; i++)
  {
    cout << "Arg permissions: " << permissionsReader.GetPermissions(argv[i], &fileInfoProvider) << endl;  
  }

  logger.LogInfo("Hello from the logs");
  cout << "my permissions are: " << permissionsReader.GetPermissions("/home/vagrant/src/main.cpp", &fileInfoProvider) << endl;
}