################################################################
#公共参数
################################################################
MAKE_PATH=./make
include $(MAKE_PATH)/makecmd.inc

################################################################
#编译参数设置
################################################################
# 多个编译源文件目录的共同根目录
CPP_ROOT_DIR=../..

# 多个编译源文件目录
CPP_SRC_DIR=../../src

# 包含头文件目录
DEBUG_INCS=-I../../inc -I../../inc/lua
RELEASE_INCS=-I../../inc -I../../inc/lua

# 包含库文件目录
DEBUG_LIBS=
RELEASE_LIBS=

# 输出中间文件目录
DEBUG_OUT_DIR=../../../../EXLibOut/luatinkere/cos-x86-64/debug
RELEASE_OUT_DIR=../../../../EXLibOut/luatinkere/cos-x86-64/release

# 输出目标文件目录
OUT_TARGET_DIR=../../lib/cos-x86-64

# 额外的宏定义
DEBUG_DEFS=-DLOG4CXX_STATIC -D__NEW_ADDITION_SAVE__ -DLUA_USE_POSIX
RELEASE_DEFS=-DLOG4CXX_STATIC -D__NEW_ADDITION_SAVE__ -DLUA_USE_POSIX

# 编译C++文件参数
DEBUG_CXX_FLAGS=-Wno-deprecated
RELEASE_CXX_FLAGS=-Wno-deprecated

# 编译C文件参数
DEBUG_C_FLAGS=-Wno-deprecated
RELEASE_C_FLAGS=-Wno-deprecated

################################################################
#编译文件
################################################################
OBJ_CPP=$(call fun_get_cpp_src_file)
OBJ_CC=$(call fun_get_cc_src_file)
OBJ_C=$(call fun_get_c_src_file)
OBJ_S=

################################################################
#静态库参数设置
################################################################
# 生产静态库参数
DEBUG_LIB_FLAGS=
RELEASE_LIB_FLAGS=

# 输出静态库
DEBUG_LIB_FILE=$(OUT_TARGET_DIR)/libluatinkere_d.a
RELEASE_LIB_FILE=$(OUT_TARGET_DIR)/libluatinkere.a

################################################################
#动态库参数设置
################################################################
# 生产静态库参数
DEBUG_DLL_FLAGS=
RELEASE_DLL_FLAGS=

# 输出动态库
DEBUG_DLL_FILE=$(OUT_TARGET_DIR)/libluatinkere_d.so
RELEASE_DLL_FILE=$(OUT_TARGET_DIR)/libluatinkere.so

################################################################
#可执行文件参数设置
################################################################
# 生产静态库参数
DEBUG_EXE_FLAGS=
RELEASE_EXE_FLAGS=

# 输出静态库
DEBUG_EXE_FILE=
RELEASE_EXE_FILE=

include $(MAKE_PATH)/makeobj.inc