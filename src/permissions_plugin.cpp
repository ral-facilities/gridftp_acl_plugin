#include <stdio.h>
#include <iostream>
#include "./framework/logger/logger.h"
#include <stdexcept>
#include <string>
#include <sys/stat.h>

 #include <sys/types.h>
 #include <fcntl.h>
 #include "./application/permissionsReader.h"
 #include "./application/permissionsSetter.h"
 #include "./application/FileInfoProvider.h"
 using namespace std;


extern "C"
{
  // IMPORTANT: the gridftp code must be inside the extern C brackets so the names are preserved  
  #include "globus_gridftp_server.h"

  static
  globus_version_t local_version =
  {
    0, /* major version number */
    1, /* minor version number */
    0,
    0 /* branch ID */
  };

  static Logger logger;

  typedef struct globus_l_gfs_permissions_plugin_handle_s
  {
    int                                 some_needed_data;
  } globus_l_gfs_permissions_plugin_handle_t;


  // Most functions will be populated from the underlying 'file' DSI
  static globus_gfs_storage_iface_t permissions_plugin_dsi_iface;

  static globus_extension_handle_t permissions_plugin_dsi_handle = NULL;

  static globus_gfs_storage_command_t original_command_function = NULL;
  static globus_gfs_storage_init_t original_init_function = NULL;

  enum {
    GLOBUS_GFS_CMD_SITE_GETPERMISSIONS = GLOBUS_GFS_MIN_CUSTOM_CMD,
    GLOBUS_GFS_CMD_SITE_SETPERMISSIONS = GLOBUS_GFS_MIN_CUSTOM_CMD+1
  };


  /*************************************************************************
   *  start
   *  -----
   *  This function is called when a new session is initialized, ie a user 
   *  connectes to the server.  This hook gives the dsi an oppertunity to
   *  set internal state that will be threaded through to all other
   *  function calls associated with this session.  And an oppertunity to
   *  reject the user.
   *
   *  finished_info.info.session.session_arg should be set to an DSI
   *  defined data structure.  This pointer will be passed as the void *
   *  user_arg parameter to all other interface functions.
   * 
   *  NOTE: at nice wrapper function should exist that hides the details 
   *        of the finished_info structure, but it currently does not.  
   *        The DSI developer should jsut follow this template for now
   ************************************************************************/
  static
  void
  globus_l_gfs_permissions_plugin_start(
      globus_gfs_operation_t              op,
      globus_gfs_session_info_t *         session_info)
  {
      // globus_l_gfs_permissions_plugin_handle_t *       permissions_plugin_handle;
      // globus_gfs_finished_info_t          finished_info;
      GlobusGFSName(globus_l_gfs_permissions_plugin_start);

      logger.LogTrace("starting GET permissions plugin session");

      globus_result_t result = globus_gridftp_server_add_command(op, "SITE GETPERMISSIONS",
                                  GLOBUS_GFS_CMD_SITE_GETPERMISSIONS,
                                  3,
                                  3,
                                  "SITE GETPERMISSIONS <sp> $location: Get permission information for a location.",
                                  GLOBUS_TRUE,
                                  GFS_ACL_ACTION_LOOKUP);

      logger.LogTrace("registered SITE GETPERMISSIONS command");
      if (result != GLOBUS_SUCCESS)
      {
          std::cout << "Failed to add custom 'SITE GETPERMISSIONS' command\n";
          globus_gridftp_server_finished_session_start(op,
                                                  result,
                                                  NULL,
                                                  NULL,
                                                  NULL);
          return;
      }

      logger.LogTrace("starting SET permissions plugin session");

      result = globus_gridftp_server_add_command(op, "SITE SETPERMISSIONS",
                                  GLOBUS_GFS_CMD_SITE_SETPERMISSIONS,
                                  3,
                                  4,
                                  "SITE SETPERMISSIONS <sp> $location: Set permission information for a location.",
                                  GLOBUS_TRUE,
                                  GFS_ACL_ACTION_LOOKUP);

      logger.LogTrace("registered SITE SETPERMISSIONS command");
      if (result != GLOBUS_SUCCESS)
      {
          std::cout << "Failed to add custom 'SITE SETPERMISSIONS' command\n";
          globus_gridftp_server_finished_session_start(op,
                                                  result,
                                                  NULL,
                                                  NULL,
                                                  NULL);
          return;
      }

      logger.LogTrace("passing through to original start function");

      original_init_function(op, session_info);
  }

  /*************************************************************************
   *  destroy
   *  -------
   *  This is called when a session ends, ie client quits or disconnects.
   *  The dsi should clean up all memory they associated wit the session
   *  here. 
   ************************************************************************/
  static
  void
  globus_l_gfs_permissions_plugin_destroy(
      void *                              user_arg)
  {
      globus_l_gfs_permissions_plugin_handle_t *       permissions_plugin_handle;

      permissions_plugin_handle = (globus_l_gfs_permissions_plugin_handle_t *) user_arg;

      logger.LogTrace("stopping permissions plugin session");
      globus_free(permissions_plugin_handle);
  }

  /*************************************************************************
   *  stat
   *  ----
   *  This interface function is called whenever the server needs 
   *  information about a given file or resource.  It is called then an
   *  LIST is sent by the client, when the server needs to verify that 
   *  a file exists and has the proper permissions, etc.
   ************************************************************************/
  static
  void
  globus_l_gfs_permissions_plugin_stat(
      globus_gfs_operation_t              op,
      globus_gfs_stat_info_t *            stat_info,
      void *                              user_arg)
  {
      globus_gfs_stat_t                   stat_array[1];
      int                                 stat_count = 1;
      globus_l_gfs_permissions_plugin_handle_t *       permissions_plugin_handle;
      GlobusGFSName(globus_l_gfs_permissions_plugin_stat);

      permissions_plugin_handle = (globus_l_gfs_permissions_plugin_handle_t *) user_arg;

      stat_array[0].mode = 0;
      stat_array[0].nlink = 0;
      stat_array[0].uid = 0;
      stat_array[0].gid = 0;
      stat_array[0].size = 0;
      stat_array[0].mtime = 0;
      stat_array[0].atime = 0;
      stat_array[0].ctime = 0;
      stat_array[0].dev = 0;
      stat_array[0].ino = 0;

      std::cout << "Calling stat command\n";

      globus_gridftp_server_finished_stat(
          op, GLOBUS_SUCCESS, stat_array, stat_count);
  }

static
void
get_permissions(
    globus_gfs_operation_t op,
    globus_gfs_command_info_t *cmd_info)
    {
        GlobusGFSName(get_permissions);

        int argc = 0;
        char **argv;

        globus_result_t result = globus_gridftp_server_query_op_info(
            op,
            cmd_info->op_info,
            GLOBUS_GFS_OP_INFO_CMD_ARGS,
            &argv,
            &argc
            );
        
        if (result != GLOBUS_SUCCESS)
        {
            result = GlobusGFSErrorGeneric("Incorrect invocation of SITE GETPERMISSIONS command");
            globus_gridftp_server_finished_command(op, result, (char*)"550 Incorrect invocation of SITE GETPERMISSIONS.\r\n");
            return;            
        }

        std::string filePath = "";
        filePath = argv[2];

        PermissionsReader permissionsReader;
        FileInfoProvider fileInfoProvider;

        try
        {
            std::string permissionsString = permissionsReader.GetPermissions(filePath, &fileInfoProvider);

            char *cstr = &permissionsString[0u];
            char final_output[1024];
            snprintf(final_output, 1024, "250 PERMISSIONS: %s\r\n", cstr);
            final_output[1023] = '\0';
            globus_gridftp_server_finished_command(op, result, final_output);
        }
        catch(std::runtime_error& e)
        {
            //cout << e.what() << endl;
            result = GlobusGFSErrorGeneric("Failed to get file permissions");
            globus_gridftp_server_finished_command(op, result, (char*)"550 Server usage query failed.\r\n");
        }
    }

  static
  void
  set_permissions(
    globus_gfs_operation_t op,
    globus_gfs_command_info_t *cmd_info)      
  {
      GlobusGFSName(set_permissions);

      int argc = 0;
      char **argv;

      globus_result_t result = globus_gridftp_server_query_op_info(
            op,
            cmd_info->op_info,
            GLOBUS_GFS_OP_INFO_CMD_ARGS,
            &argv,
            &argc
        );

      if (result != GLOBUS_SUCCESS)
        {
            result = GlobusGFSErrorGeneric("Incorrect invocation of SITE SETPERMISSIONS command");
            globus_gridftp_server_finished_command(op, result, (char*)"550 Incorrect invocation of SITE SETPERMISSIONS.\r\n");
            return;            
        }

      std::string filePath;
      filePath = argv[2];     
      std::string permissions;
      permissions = argv[3];

      PermissionsSetter permissionsSetter;
      FileInfoProvider fileInfoProvider;

      try
      {
            //std::string permissions = "mode: 16895 groupID: 1000 userID: 1000";
           // cout << permissions << endl;
            permissionsSetter.SetPermissions(filePath, permissions, &fileInfoProvider);

            // char *cstr = &permissionsString[0u];
            char final_output[1024];
            // snprintf(final_output, 1024, "250 PERMISSIONS: %s\r\n", cstr);
            snprintf(final_output, 1024, "250 PERMISSIONS: test test\r\n");
            final_output[1023] = '\0';
            globus_gridftp_server_finished_command(op, result, final_output);
        }
        catch(std::runtime_error& e)
        {
            //cout << e.what() << endl;
            result = GlobusGFSErrorGeneric("Failed to set file permissions");
            globus_gridftp_server_finished_command(op, result, (char*)"550 Server usage query failed.\r\n");
        }
  }

  /*************************************************************************
   *  command
   *  -------
   *  This interface function is called when the client sends a 'command'.
   *  commands are such things as mkdir, remdir, delete.  The complete
   *  enumeration is below.
   *
   *  To determine which command is being requested look at:
   *      cmd_info->command
   *
   *      GLOBUS_GFS_CMD_MKD = 1,
   *      GLOBUS_GFS_CMD_RMD,
   *      GLOBUS_GFS_CMD_DELE,
   *      GLOBUS_GFS_CMD_RNTO,
   *      GLOBUS_GFS_CMD_RNFR,
   *      GLOBUS_GFS_CMD_CKSM,
   *      GLOBUS_GFS_CMD_SITE_CHMOD,
   *      GLOBUS_GFS_CMD_SITE_DSI
   ************************************************************************/
  static
  void
  globus_l_gfs_permissions_plugin_command(
    globus_gfs_operation_t              op,
    globus_gfs_command_info_t *         cmd_info,
    void *                              user_arg)
{
    logger.LogTrace("Calling command function with command " + std::to_string(cmd_info->command));

    globus_result_t result;
    switch (cmd_info->command)
    {
    case GLOBUS_GFS_CMD_SITE_GETPERMISSIONS:
        logger.LogTrace("Calling SITE GETPERMISSIONS");
        // result = GLOBUS_SUCCESS;
        // globus_gridftp_server_finished_command(op, result, (char*)"250 SITE GETPERMISSIONS command called successfully.\r\n");
        get_permissions(op, cmd_info);
        return;
    case GLOBUS_GFS_CMD_SITE_SETPERMISSIONS:
        logger.LogTrace("Calling SITE SETPERMISSIONS");
        // result = GLOBUS_SUCCESS;
        // globus_gridftp_server_finished_command(op, result, (char*)"250 SITE SETPERMISSIONS command called successfully.\r\n");
        set_permissions(op, cmd_info);
        return;
    default:
        // Anything not explicitly plugin-centric is passed to the
        // underlying module.
        break;
    }

    original_command_function(op, cmd_info, user_arg);
}

  /*************************************************************************
   *  recv
   *  ----
   *  This interface function is called when the client requests that a
   *  file be transfered to the server.
   *
   *  To receive a file the following functions will be used in roughly
   *  the presented order.  They are doced in more detail with the
   *  gridftp server documentation.
   *
   *      globus_gridftp_server_begin_transfer();
   *      globus_gridftp_server_register_read();
   *      globus_gridftp_server_finished_transfer();
   *
   ************************************************************************/
  static
  void
  globus_l_gfs_permissions_plugin_recv(
      globus_gfs_operation_t              op,
      globus_gfs_transfer_info_t *        transfer_info,
      void *                              user_arg)
  {
      std::cout << "Calling recv function\n";

      globus_l_gfs_permissions_plugin_handle_t *       permissions_plugin_handle;
      GlobusGFSName(globus_l_gfs_permissions_plugin_recv);

      permissions_plugin_handle = (globus_l_gfs_permissions_plugin_handle_t *) user_arg;

      globus_gridftp_server_finished_transfer(op, GLOBUS_SUCCESS);
  }

  /*************************************************************************
   *  send
   *  ----
   *  This interface function is called when the client requests to receive
   *  a file from the server.
   *
   *  To send a file to the client the following functions will be used in roughly
   *  the presented order.  They are doced in more detail with the
   *  gridftp server documentation.
   *
   *      globus_gridftp_server_begin_transfer();
   *      globus_gridftp_server_register_write();
   *      globus_gridftp_server_finished_transfer();
   *
   ************************************************************************/
  static
  void
  globus_l_gfs_permissions_plugin_send(
      globus_gfs_operation_t              op,
      globus_gfs_transfer_info_t *        transfer_info,
      void *                              user_arg)
  {
    std::cout << "Calling send function\n";
    globus_l_gfs_permissions_plugin_handle_t *       permissions_plugin_handle;
    GlobusGFSName(globus_l_gfs_permissions_plugin_send);

    permissions_plugin_handle = (globus_l_gfs_permissions_plugin_handle_t *) user_arg;

    globus_gridftp_server_finished_transfer(op, GLOBUS_SUCCESS);
  }

  static int globus_l_gfs_permissions_plugin_activate(void);
  static int globus_l_gfs_permissions_plugin_deactivate(void);

  GlobusExtensionDefineModule(globus_gridftp_server_permissions_plugin) =
  {
    (char *)"globus_gridftp_server_permissions_plugin",
    globus_l_gfs_permissions_plugin_activate,
    globus_l_gfs_permissions_plugin_deactivate,
    NULL,
    NULL,
    &local_version
  };

  static int globus_l_gfs_permissions_plugin_activate(void)
  {
    // start the logger, these settings should eventually be loaded from a config file
    logger.Init("/usr/tmp/", "trace");
    logger.LogInfo("Activating permissions plugin");

    globus_result_t result = GLOBUS_SUCCESS;
    memset(&permissions_plugin_dsi_iface, '\0', sizeof(globus_gfs_storage_iface_t));
    char * dsi_name;
    dsi_name = (char*)"file";

    logger.LogTrace("looking up file plugin");
    void *new_dsi = (globus_gfs_storage_iface_t *) globus_extension_lookup(
        &permissions_plugin_dsi_handle, GLOBUS_GFS_DSI_REGISTRY, dsi_name);

    if (new_dsi == NULL)
    {
        logger.LogTrace("Trying to activate file dsi");
        result = globus_extension_activate("globus_gridftp_server_file");
        if (result != GLOBUS_SUCCESS)
        {
            std::cout << "Unable to activate file dsi\n";
            logger.LogError("Unable to activate file dsi");
        }
    }
    new_dsi = (globus_gfs_storage_iface_t *) globus_extension_lookup(
        &permissions_plugin_dsi_handle, GLOBUS_GFS_DSI_REGISTRY, dsi_name);

    logger.LogTrace("copying file storage interface");
    memcpy(&permissions_plugin_dsi_iface, new_dsi, sizeof(globus_gfs_storage_iface_t));

    logger.LogTrace("storing copies of the original commands");
    original_command_function = permissions_plugin_dsi_iface.command_func;
    original_init_function = permissions_plugin_dsi_iface.init_func;
    permissions_plugin_dsi_iface.command_func = globus_l_gfs_permissions_plugin_command;
    permissions_plugin_dsi_iface.init_func = globus_l_gfs_permissions_plugin_start;


    globus_extension_registry_add(
        GLOBUS_GFS_DSI_REGISTRY,
        (char *)"permissions_plugin",
        GlobusExtensionMyModule(globus_gridftp_server_permissions_plugin),
        &permissions_plugin_dsi_iface);

    return 0;
  }

  static int globus_l_gfs_permissions_plugin_deactivate(void)
  {
    logger.LogInfo("Deactivating permissions plugin");
    globus_extension_registry_remove(
        GLOBUS_GFS_DSI_REGISTRY, (char *)"permissions_plugin");

    globus_extension_release(permissions_plugin_dsi_handle);

    return 0;
  }

}