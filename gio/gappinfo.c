/* GIO - GLib Input, Output and Streaming Library
 * 
 * Copyright (C) 2006-2007 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author: Alexander Larsson <alexl@redhat.com>
 */

#include <config.h>
#include "gappinfo.h"
#include "glibintl.h"
#include <gioerror.h>


static void g_app_info_base_init (gpointer g_class);
static void g_app_info_class_init (gpointer g_class,
				   gpointer class_data);


GType
g_app_info_get_type (void)
{
  static GType app_info_type = 0;

  if (! app_info_type)
    {
      static const GTypeInfo app_info_info =
      {
        sizeof (GAppInfoIface), /* class_size */
	g_app_info_base_init,   /* base_init */
	NULL,		/* base_finalize */
	g_app_info_class_init,
	NULL,		/* class_finalize */
	NULL,		/* class_data */
	0,
	0,              /* n_preallocs */
	NULL
      };

      app_info_type =
	g_type_register_static (G_TYPE_INTERFACE, I_("GAppInfo"),
				&app_info_info, 0);

      g_type_interface_add_prerequisite (app_info_type, G_TYPE_OBJECT);
    }

  return app_info_type;
}

static void
g_app_info_class_init (gpointer g_class,
		       gpointer class_data)
{
}

static void
g_app_info_base_init (gpointer g_class)
{
}


/**
 * g_app_info_dup:
 * @appinfo: a #GAppInfo.
 *
 * Returns: a duplicate of @appinfo.
 **/
GAppInfo *
g_app_info_dup (GAppInfo *appinfo)
{
  GAppInfoIface *iface;

  g_return_val_if_fail (G_IS_APP_INFO (appinfo), NULL);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  return (* iface->dup) (appinfo);
}

/**
 * g_app_info_equal:
 * @appinfo1: the first #GAppInfo.  
 * @appinfo2: the second #GAppInfo.
 *
 * Returns: %TRUE if @appinfo1 is equal to @appinfo2. %FALSE otherwise.
 *  
 **/
gboolean
g_app_info_equal (GAppInfo    *appinfo1,
		  GAppInfo    *appinfo2)
{
  GAppInfoIface *iface;

  g_return_val_if_fail (G_IS_APP_INFO (appinfo1), FALSE);
  g_return_val_if_fail (G_IS_APP_INFO (appinfo2), FALSE);

  if (G_TYPE_FROM_INSTANCE (appinfo1) != G_TYPE_FROM_INSTANCE (appinfo2))
    return FALSE;
  
  iface = G_APP_INFO_GET_IFACE (appinfo1);

  return (* iface->equal) (appinfo1, appinfo2);
}

/**
 * g_app_info_get_id:
 * @appinfo: a #GAppInfo.
 *
 * Returns: 
 **/
const char *
g_app_info_get_id (GAppInfo *appinfo)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), NULL);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  return (* iface->get_id) (appinfo);
}

/**
 * g_app_info_get_name:
 * @appinfo: a #GAppInfo.
 *
 * Returns: the name of the application for @appinfo.
 **/
const char *
g_app_info_get_name (GAppInfo *appinfo)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), NULL);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  return (* iface->get_name) (appinfo);
}

/**
 * g_app_info_get_description:
 * @appinfo: a #GAppInfo.
 *
 * Returns: a string containing a description of the 
 * application @appinfo.  
 * The returned string should be not freed when no longer needed.
 **/
const char *
g_app_info_get_description (GAppInfo *appinfo)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), NULL);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  return (* iface->get_description) (appinfo);
}

/**
 * g_app_info_get_executable:
 * @appinfo: a #GAppInfo.
 *
 * Returns: a string containing the @appinfo's application 
 * binary's name.
 **/
const char *
g_app_info_get_executable (GAppInfo *appinfo)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), NULL);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  return (* iface->get_executable) (appinfo);
}


/**
 * g_app_info_set_as_default_for_type:
 * @appinfo: a #GAppInfo.
 * @content_type: the content type.
 * @error: a #GError.
 *
 * Returns: %TRUE if the given @appinfo is the default 
 * for the given @content_type. %FALSE if not, 
 * or in case of an error.
 **/
gboolean
g_app_info_set_as_default_for_type (GAppInfo    *appinfo,
				    const char  *content_type,
				    GError     **error)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), FALSE);
  g_return_val_if_fail (content_type != NULL, FALSE);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  return (* iface->set_as_default_for_type) (appinfo, content_type, error);
}


/**
 * g_app_info_set_as_default_for_extension:
 * @appinfo: a #GAppInfo.
 * @extension: a string containing the file extension.
 * @error: a #GError.
 *
 * Returns: %TRUE if the given @appinfo is the default 
 * for the given @extension. %FALSE if not, 
 * or in case of an error.
 **/
gboolean
g_app_info_set_as_default_for_extension (GAppInfo  *appinfo,
					 const char *extension,
					 GError **error)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), FALSE);
  g_return_val_if_fail (extension != NULL, FALSE);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  if (iface->set_as_default_for_extension)
    return (* iface->set_as_default_for_extension) (appinfo, extension, error);

  g_set_error (error, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED, "g_app_info_set_as_default_for_extension not supported yet");
  return FALSE;
}


/**
 * g_app_info_add_supports_type:
 * @appinfo: a #GAppInfo.
 * @content_type: a string.
 * @error: a #GError.
 *
 * Returns: %TRUE if @appinfo supports @content_type.
 * %FALSE if not, or in case of an error.
 **/
gboolean
g_app_info_add_supports_type (GAppInfo             *appinfo,
			      const char           *content_type,
			      GError              **error)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), FALSE);
  g_return_val_if_fail (content_type != NULL, FALSE);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  if (iface->add_supports_type)
    return (* iface->add_supports_type) (appinfo, content_type, error);

  g_set_error (error, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED, "g_app_info_add_supports_type not supported yet");
  return FALSE;
}


/**
 * g_app_info_can_remove_support_type:
 * @appinfo: a #GAppInfo.
 *
 * Returns: %TRUE if it is possible to remove supported 
 * content types from a given @appinfo, %FALSE if not.
 **/
gboolean
g_app_info_can_remove_supports_type (GAppInfo *appinfo)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), FALSE);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  if (iface->can_remove_supports_type)
    return (* iface->can_remove_supports_type) (appinfo);

  return FALSE;
}


/**
 * g_app_info_remove_supports_type:
 * @appinfo: a #GAppInfo.
 * @content_type: a string.
 * @error: a #GError.
 *
 * Returns: %TRUE if @content_type support was removed
 * from @appinfo. %FALSE if not.
 **/
gboolean
g_app_info_remove_supports_type (GAppInfo *appinfo,
				 const char *content_type,
				 GError **error)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), FALSE);
  g_return_val_if_fail (content_type != NULL, FALSE);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  if (iface->remove_supports_type)
    return (* iface->remove_supports_type) (appinfo, content_type, error);

  g_set_error (error, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED, "g_app_info_remove_supports_type not supported yet");
  return FALSE;
}


/**
 * g_app_info_get_icon:
 * @appinfo: a #GAppInfo.
 *
 * Returns: the default #GIcon for @appinfo.
 **/
GIcon *
g_app_info_get_icon (GAppInfo *appinfo)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), NULL);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  return (* iface->get_icon) (appinfo);
}


/**
 * g_app_info_launch:
 * @appinfo: a #GAppInfo.
 * @files: a #GList of #GFile objects.
 * @launch_context: a #GAppLaunchContext.
 * @error: a #GError.
 *
 * Returns: %TRUE on successful launch.
 **/
gboolean
g_app_info_launch (GAppInfo    *appinfo,
		   GList       *files,
		   GAppLaunchContext *launch_context,
		   GError     **error)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), FALSE);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  return (* iface->launch) (appinfo, files, launch_context, error);
}


/**
 * g_app_info_supports_uris:
 * @appinfo: a #GAppInfo.
 *
 * Returns: %TRUE if the @appinfo supports URIs.
 **/
gboolean
g_app_info_supports_uris (GAppInfo *appinfo)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), FALSE);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  return (* iface->supports_uris) (appinfo);
}


/**
 * g_app_info_launch_uris:
 * @appinfo: a #GAppInfo.
 * @uris: a #GList containing URIs to launch. 
 * @launch_context: a #GAppLaunchContext.
 * @error: a #GError.
 *
 * Returns: %TRUE if the @appinfo was launched 
 * with the given @uris.
 **/
gboolean
g_app_info_launch_uris (GAppInfo    *appinfo,
			GList       *uris,
			GAppLaunchContext *launch_context,
			GError     **error)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), FALSE);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  return (* iface->launch) (appinfo, uris, launch_context, error);
}


/**
 * g_app_info_should_show:
 * @appinfo: a #GAppInfo.
 * @desktop_env: a string.
 *
 * Returns: %TRUE if the @GAppInfo should be shown,
 * %FALSE otherwise.
 **/
gboolean
g_app_info_should_show (GAppInfo    *appinfo,
			const char  *desktop_env)
{
  GAppInfoIface *iface;
  
  g_return_val_if_fail (G_IS_APP_INFO (appinfo), FALSE);

  iface = G_APP_INFO_GET_IFACE (appinfo);

  return (* iface->should_show) (appinfo, desktop_env);
}

G_DEFINE_TYPE (GAppLaunchContext, g_app_launch_context, G_TYPE_OBJECT);

/**
 * g_app_launch_context_new:
 *
 * Returns: A new #GAppLaunchContext.
 **/
GAppLaunchContext *
g_app_launch_context_new (void)
{
  return g_object_new (G_TYPE_APP_LAUNCH_CONTEXT, NULL);
}

static void
g_app_launch_context_class_init (GAppLaunchContextClass *klass)
{
}

static void
g_app_launch_context_init (GAppLaunchContext *launch_context)
{
}

/**
 * g_app_launch_context_get_display:
 * @context: a #GAppLaunchContext.  
 * @info: a #GAppInfo. 
 * @files: a #GList of files.
 *
 **/
char *
g_app_launch_context_get_display (GAppLaunchContext *context,
				  GAppInfo          *info,
				  GList             *files)
{
  GAppLaunchContextClass *class;

  g_return_val_if_fail (G_IS_APP_LAUNCH_CONTEXT (context), NULL);
  g_return_val_if_fail (G_IS_APP_INFO (info), NULL);

  class = G_APP_LAUNCH_CONTEXT_GET_CLASS (context);

  if (class->get_display == NULL)
    return NULL;

  return class->get_display (context, info, files);
}

/**
 * g_app_launch_context_get_startup_notify_id:
 * @context: a #GAppLaunchContext.
 * @info: a #GAppInfo.
 * @files: a #GList of files.
 *
 **/
char *
g_app_launch_context_get_startup_notify_id (GAppLaunchContext *context,
					    GAppInfo          *info,
					    GList             *files)
{
  GAppLaunchContextClass *class;

  g_return_val_if_fail (G_IS_APP_LAUNCH_CONTEXT (context), NULL);
  g_return_val_if_fail (G_IS_APP_INFO (info), NULL);

  class = G_APP_LAUNCH_CONTEXT_GET_CLASS (context);

  if (class->get_startup_notify_id == NULL)
    return NULL;

  return class->get_startup_notify_id (context, info, files);
}


/**
 * g_app_launch_context_get_startup_notify_id:
 * @context: a #GAppLaunchContext.
 * @startup_notify_id: a string containing the startup ID of the application.
 *
 **/
void
g_app_launch_context_launch_failed (GAppLaunchContext *context,
				    const char *startup_notify_id)
{
  GAppLaunchContextClass *class;

  g_return_if_fail (G_IS_APP_LAUNCH_CONTEXT (context));
  g_return_if_fail (startup_notify_id != NULL);

  class = G_APP_LAUNCH_CONTEXT_GET_CLASS (context);

  if (class->launch_failed != NULL)
    class->launch_failed (context, startup_notify_id);
}