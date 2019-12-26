import os
import sys
import platform

#for pc
sys.path.insert(0, '../awtk/')

#for linux-fb
#sys.path.insert(0, '../awtk-linux-fb/')

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
APP_CCFLAGS = APP_CFLAGS

APP_LIBS = ['assets']
APP_LIBPATH = [APP_LIB_DIR]
APP_CPPPATH = [APP_SRC_DIR, os.path.join(APP_SRC_DIR, 'common'), 
  os.path.join(APP_SRC_DIR, 'view_models')]

MVVM_ROOT = os.path.normpath(os.path.join(APP_ROOT, '../awtk-mvvm'))
MVVM_LIB_DIR = os.path.join(MVVM_ROOT, 'lib')
MVVM_SRC_DIR = os.path.join(MVVM_ROOT, 'src')

MVVM_CPPPATH = [MVVM_SRC_DIR]
MVVM_LIBPATH = [MVVM_LIB_DIR]

if hasattr(awtk, 'CC'):
  MVVM_LIBS = ['mvvm', 'jerryscript']
  DefaultEnvironment(
    CC=awtk.CC,
    CXX=awtk.CXX,
    LD=awtk.LD,
    AR=awtk.AR,
    STRIP=awtk.STRIP,
    
    LINKFLAGS = awtk.LINKFLAGS,
    CFLAGS    = APP_CFLAGS + awtk.CFLAGS, 
    CCFLAGS   = APP_CCFLAGS + awtk.CCFLAGS, 
    LIBS      = APP_LIBS + MVVM_LIBS + awtk.LIBS,
    CPPPATH   = APP_CPPPATH + MVVM_CPPPATH + awtk.CPPPATH,
    LIBPATH   = APP_LIBPATH + MVVM_LIBPATH + awtk.LIBPATH,
    OS_SUBSYSTEM_CONSOLE=awtk.OS_SUBSYSTEM_CONSOLE,
    OS_SUBSYSTEM_WINDOWS=awtk.OS_SUBSYSTEM_WINDOWS)
else:
  MVVM_LIBS = ['mvvm', 'jerryscript', 'nfd']
  DefaultEnvironment(
    LINKFLAGS = awtk.LINKFLAGS,
    CFLAGS    = APP_CFLAGS + awtk.CFLAGS, 
    CCFLAGS   = APP_CCFLAGS + awtk.CCFLAGS, 
    LIBS      = APP_LIBS + MVVM_LIBS + awtk.LIBS,
    CPPPATH   = APP_CPPPATH + MVVM_CPPPATH + awtk.CPPPATH,
    LIBPATH   = APP_LIBPATH + MVVM_LIBPATH + awtk.LIBPATH,
    OS_SUBSYSTEM_CONSOLE=awtk.OS_SUBSYSTEM_CONSOLE,
    OS_SUBSYSTEM_WINDOWS=awtk.OS_SUBSYSTEM_WINDOWS)


SConscript(['src/SConscript', 'tests/SConscript'])

