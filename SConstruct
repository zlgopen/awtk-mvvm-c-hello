import os
import scripts.app_helper as app

DEPENDS_LIBS = [
  {
    "root" : '../awtk-restful-httpd',
    'shared_libs': ['httpd'],
    'static_libs': []
  },
  {
    "root" : '../awtk-ui-automation',
    'shared_libs': ['ui_automation'],
    'static_libs': []
  },
  {
    "root" : '../awtk-widget-table-view',
    'shared_libs': ['table_view'],
    'static_libs': []
  },
  {
    "root" : '../awtk-widget-table-view-mvvm',
    'shared_libs': ['table_view_mvvm'],
    'static_libs': []
  },
  {
    "root" : '../awtk-widget-slidable-row',
    'shared_libs': ['slidable_row'],
    'static_libs': []
  }
]

APP_SRC = os.path.normpath(os.path.join(os.getcwd(), 'src'))
APP_CPPPATH = [
  os.path.join(APP_SRC, 'common'),
  os.path.join(APP_SRC, 'view_models'),
]

ARGUMENTS['WITH_MVVM'] = 'true'
helper = app.Helper(ARGUMENTS);
helper.set_dll_def('src/app_base.def').set_deps(DEPENDS_LIBS).add_cpppath(APP_CPPPATH).call(DefaultEnvironment)

helper.SConscript(['src/SConscript', 'tests/SConscript'])
