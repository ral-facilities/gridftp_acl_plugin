import os
import shutil
import pytest

@pytest.fixture(scope="session", autouse=True)
def set_up_system_test_environment(request):
    print("setting up a system test environment")

    # clear out the old programs
    execution_space = '../execution_space'
    if (os.path.isdir(execution_space)):
        shutil.rmtree(execution_space)

    # copy over the web api and dms
    os.makedirs(execution_space)
    shutil.copytree('../../dms-web-api/DMSWebApi', execution_space + '/web-api/DMSWebApi')
    shutil.copytree('../../dms-web-api/build', execution_space + '/web-api/build')
    
    fuse_client_folder = execution_space + '/dms-fuse-client'
    os.makedirs(fuse_client_folder)
    shutil.copy('../../dms-fuse-client/build/dms-fuse-client', fuse_client_folder + '/dms-fuse-client')
    shutil.copy('../../dms-fuse-client/src/example-dms-authentication.json', fuse_client_folder + '/dms-authentication.json')
    shutil.copytree('../../dms-fuse-client/build/subprojects', fuse_client_folder + '/subprojects')

    os.makedirs(execution_space + '/logs')
    os.makedirs(execution_space + '/testing_area/src')
    os.makedirs(execution_space + '/testing_area/staging')
    os.makedirs(execution_space + '/testing_area/target')
