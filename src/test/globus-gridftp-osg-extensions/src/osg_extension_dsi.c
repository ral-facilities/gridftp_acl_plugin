#include "globus_gridftp_server.h"
#include "globus_error_macros.h"
#include <stdio.h>
#include <string.h>

static globus_version_t osg_local_version =
{
    0, /* major version number */
    1, /* minor/bug version number */
    0,
    0 /* branch ID */
};

// From globus_i_gridftp_server.h
#define GlobusGFSErrorGenericStr(_res, _fmt)                           \
do                                                                     \
{                                                                      \
        char *                          _tmp_str;                      \
        _tmp_str = globus_common_create_string _fmt;                   \
        _res = globus_error_put(                                       \
            globus_error_construct_error(                              \
                GLOBUS_NULL,                                           \
                GLOBUS_NULL,                                           \
                GLOBUS_GFS_ERROR_GENERIC,                              \
                __FILE__,                                              \
                _gfs_name,                                             \
                __LINE__,                                              \
                "%s",                                                  \
                _tmp_str));                                            \
        globus_free(_tmp_str);                                         \
                                                                       \
} while(0)

static int osg_activate(void);
static int osg_deactivate(void);

// Most functions will be populated from the underlying 'file' DSI
static globus_gfs_storage_iface_t osg_dsi_iface;
static globus_extension_handle_t osg_dsi_handle = NULL;
static globus_gfs_storage_command_t original_command_function = NULL;
static globus_gfs_storage_init_t original_init_function = NULL;
enum {
	GLOBUS_GFS_OSG_CMD_SITE_USAGE = GLOBUS_GFS_MIN_CUSTOM_CMD,
};

// Initiate the extension and call the file dsi once done
static void
osg_extensions_init(
    globus_gfs_operation_t op, 
    globus_gfs_session_info_t * session)
{
    GlobusGFSName(osg_extensions_init);

    printf("Initiating extension\n");
    globus_result_t result = globus_gridftp_server_add_command(op, "SITE USAGE",
                                 GLOBUS_GFS_OSG_CMD_SITE_USAGE,
                                 3,
                                 5,
                                 "SITE USAGE <sp> [TOKEN <sp> $name] <sp> $location: Get usage information for a location.",
                                 GLOBUS_FALSE,
                                 GFS_ACL_ACTION_LOOKUP);

    if (result != GLOBUS_SUCCESS) {
        result = GlobusGFSErrorWrapFailed("Failed to add custom 'SITE USAGE' command", result);
        globus_gridftp_server_finished_session_start(op,
                                                 result,
                                                 NULL,
                                                 NULL,
                                                 NULL);
        return;
    }

    original_init_function(op, session);
    printf("Extension added\n");
}

/*************************************************************************
 *  destroy
 *  -------
 *  This is called when a session ends, ie client quits or disconnects.
 *  The dsi should clean up all memory they associated wit the session
 *  here. 
 ************************************************************************/
static void
osg_extensions_destroy(
    void * user_arg)
{
    globus_free(osg_dsi_handle);
}

// When the site usage command is called run this series of steps
static void
site_usage(
    globus_gfs_operation_t op,
    globus_gfs_command_info_t *cmd_info)
{
    GlobusGFSName(site_usage);
    printf("Running site usage command\n");

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
        result = GlobusGFSErrorGeneric("Incorrect invocation of SITE USAGE command");
        globus_gridftp_server_finished_command(op, result, "550 Incorrect invocation of SITE USAGE.\r\n");
        return;
    }
    if ((argc != 3) && (argc != 5))
    {
        result = GlobusGFSErrorGeneric("Incorrect number of arguments to SITE USAGE command");
        globus_gridftp_server_finished_command(op, result, "550 Incorrect number of arguments to SITE USAGE command.\r\n");
        return;
    }

    globus_gridftp_server_finished_command(op, result, (char*)"250 SITE USAGE command called successfully.\r\n");
}

static void
osg_command(
    globus_gfs_operation_t              op,
    globus_gfs_command_info_t *         cmd_info,
    void *                              user_arg)
{

    printf("Entering switch cases\n");
    switch (cmd_info->command)
    {
    case GLOBUS_GFS_OSG_CMD_SITE_USAGE:
        site_usage(op, cmd_info);
        return;
    default:
        printf("Falling back on the file dsi\n");
        // Anything not explicitly OSG-centric is passed to the
        // underlying module.
        break;
    }

    original_command_function(op, cmd_info, user_arg);
}

// Have to define dsi interface otherwise the "command_func" method is never called.
// This step isn't called in the osg code so might be bypassed somehow.
static globus_gfs_storage_iface_t       osg_dsi_iface = 
{
    GLOBUS_GFS_DSI_DESCRIPTOR_BLOCKING | GLOBUS_GFS_DSI_DESCRIPTOR_SENDER,
    osg_extensions_init,
    osg_extensions_destroy,
    NULL, /* list */
    NULL, //globus_l_gfs_permissions_plugin_send,
    NULL, //globus_l_gfs_permissions_plugin_recv,
    NULL, /* trev */
    NULL, /* active */
    NULL, /* passive */
    NULL, /* data destroy */
    osg_command, 
    NULL, //globus_l_gfs_permissions_plugin_stat,
    NULL,
    NULL
};

GlobusExtensionDefineModule(globus_gridftp_server_osg) =
{
    "globus_gridftp_server_osg",
    osg_activate,
    osg_deactivate,
    NULL,
    NULL,
    &osg_local_version
};

static int
osg_activate(void)
{
    GlobusGFSName(osg_activate);
    globus_result_t result = GLOBUS_SUCCESS;

    printf("Activating osg plugin\n");
    memset(&osg_dsi_iface, '\0', sizeof(globus_gfs_storage_iface_t));

    char * dsi_name = "file";

    // Code adapted from globus_i_gfs_data.c in Globus Toolkit.
    void *new_dsi = (globus_gfs_storage_iface_t *) globus_extension_lookup(
        &osg_dsi_handle, GLOBUS_GFS_DSI_REGISTRY, dsi_name);

    if (new_dsi == NULL)
    {
        char module_name[1024];
        snprintf(module_name, 1024, "globus_gridftp_server_%s", dsi_name);
        module_name[1023] = '\0';
        result = globus_extension_activate(module_name);
        if (result != GLOBUS_SUCCESS)
        {
            result = GlobusGFSErrorWrapFailed("DSI activation", result);
            return result;
        }
    }
    new_dsi = (globus_gfs_storage_iface_t *) globus_extension_lookup(
        &osg_dsi_handle, GLOBUS_GFS_DSI_REGISTRY, dsi_name);

    if(new_dsi == NULL)
    {
        GlobusGFSErrorGenericStr(result,
            ("DSI '%s' is not available in the module.", dsi_name));
        return result;
    }

    // copy static dsi file object and reassign functions to it
    memcpy(&osg_dsi_iface, new_dsi, sizeof(globus_gfs_storage_iface_t));
    original_command_function = osg_dsi_iface.command_func;
    original_init_function = osg_dsi_iface.init_func;
    osg_dsi_iface.command_func = osg_command; 
    osg_dsi_iface.init_func = osg_extensions_init;


    globus_extension_registry_add(
        GLOBUS_GFS_DSI_REGISTRY,
        "osg",
        GlobusExtensionMyModule(globus_gridftp_server_osg),
        &osg_dsi_iface);
    
    printf("Finished activation\n");
    return result;
}

static int
osg_deactivate(void)
{
    globus_result_t result = GLOBUS_SUCCESS;

    printf("Deactivating\n");
    globus_extension_registry_remove(
        GLOBUS_GFS_DSI_REGISTRY, "osg");

    globus_extension_release(osg_dsi_handle);

    return result;
}


