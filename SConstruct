import os
import sys
import platform

def getAwtkRoot():
  #for pc
  awtk_root = '../awtk'
  #for linux-fb
  #awtk_root = '../awtk-linux-fb'
  return os.path.abspath(awtk_root)


AWTK_ROOT = getAwtkRoot()
sys.path.insert(0, AWTK_ROOT)
import awtk_config as awtk

APP_ROOT    = os.path.normpath(os.getcwd())
APP_BIN_DIR = os.path.join(APP_ROOT, 'bin')
APP_LIB_DIR = os.path.join(APP_ROOT, 'lib')
APP_SRC_DIR = os.path.join(APP_ROOT, 'src')

os.environ['APP_ROOT'] = APP_ROOT;
os.environ['BIN_DIR'] = APP_BIN_DIR;
os.environ['LIB_DIR'] = APP_LIB_DIR;
os.environ['APP_SRC'] = APP_SRC_DIR;

APP_CFLAGS = ''
APP_LINKFLAGS = ''
APP_CCFLAGS = APP_CFLAGS
MVVM_ROOT = os.path.normpath(os.path.join(APP_ROOT, '../awtk-mvvm'))

APP_LIBS = ['awtk_mvvm_app', 'mvvm']

APP_CPPPATH = [
  APP_SRC_DIR,
  os.path.join(APP_SRC_DIR, 'common'), 
  os.path.join(APP_SRC_DIR, 'view_models'),
  os.path.join(MVVM_ROOT, 'src') 
]

APP_LIBPATH = [
  os.path.join(APP_ROOT, 'lib'), 
  os.path.join(APP_ROOT, 'bin'), 
  os.path.join(MVVM_ROOT, 'lib'), 
  os.path.join(MVVM_ROOT, 'bin') 
]

if awtk.isBuildShared():
  AWTK_LIBS = awtk.SHARED_LIBS
  awtk.copySharedLib(AWTK_ROOT, APP_BIN_DIR, 'awtk');
  awtk.copySharedLib(MVVM_ROOT, APP_BIN_DIR, 'mvvm');

  if awtk.OS_NAME == 'Linux':
    APP_LINKFLAGS += ' -Wl,-rpath=' + APP_BIN_DIR + ' '
else:
  AWTK_LIBS = awtk.STATIC_LIBS

if hasattr(awtk, 'CC'):
  DefaultEnvironment(
    CC=awtk.CC,
    CXX=awtk.CXX,
    LD=awtk.LD,
    AR=awtk.AR,
    STRIP=awtk.STRIP,
    
    LINKFLAGS = awtk.LINKFLAGS + APP_LINKFLAGS,
    CFLAGS    = APP_CFLAGS + awtk.CFLAGS, 
    CCFLAGS   = APP_CCFLAGS + awtk.CCFLAGS, 
    LIBS      = APP_LIBS + AWTK_LIBS,
    CPPPATH   = APP_CPPPATH + awtk.CPPPATH,
    LIBPATH   = APP_LIBPATH + awtk.LIBPATH,
    OS_SUBSYSTEM_CONSOLE=awtk.OS_SUBSYSTEM_CONSOLE,
    OS_SUBSYSTEM_WINDOWS=awtk.OS_SUBSYSTEM_WINDOWS)
else:
  DefaultEnvironment(
    LINKFLAGS = awtk.LINKFLAGS + APP_LINKFLAGS,
    CFLAGS    = APP_CFLAGS + awtk.CFLAGS, 
    CCFLAGS   = APP_CCFLAGS + awtk.CCFLAGS, 
    LIBS      = APP_LIBS + AWTK_LIBS,
    CPPPATH   = APP_CPPPATH + awtk.CPPPATH,
    LIBPATH   = APP_LIBPATH + awtk.LIBPATH,
    OS_SUBSYSTEM_CONSOLE=awtk.OS_SUBSYSTEM_CONSOLE,
    OS_SUBSYSTEM_WINDOWS=awtk.OS_SUBSYSTEM_WINDOWS)


SConscript(['src/SConscript', 'tests/SConscript'])

