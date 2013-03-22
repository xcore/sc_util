# The TARGET variable determines what target system the application is 
# compiled for. It either refers to an XN file in the source directories
# or a valid argument for the --target option when compiling.

TARGET = SLICEKIT-L16

# The APP_NAME variable determines the name of the final .xe file. It should
# not include the .xe postfix. If left blank the name will default to 
# the project name

APP_NAME =

# The flags passed to xcc when building the application
# You can also set the following to override flags for a particular language:
#
#    XCC_XC_FLAGS, XCC_C_FLAGS, XCC_ASM_FLAGS, XCC_CPP_FLAGS
#
# If the variable XCC_MAP_FLAGS is set it overrides the flags passed to 
# xcc for the final link (mapping) stage.

XCC_FLAGS_test_assert = -g -DTEST_ASSERT=1
XCC_FLAGS_test_fail = -g -DTEST_FAIL=1
XCC_FLAGS_test_unreachable = -g -DTEST_UNREACHABLE=1
XCC_FLAGS_test_assert_disabled = -g -DTEST_ASSERT=1 -DXASSERT_ENABLE_ASSERTIONS=0
XCC_FLAGS_test_fail_disabled = -g -DTEST_FAIL=1 -DXASSERT_ENABLE_ASSERTIONS=0
XCC_FLAGS_test_unreachable_disabled = -g -DTEST_UNREACHABLE=1  -DXASSERT_ENABLE_ASSERTIONS=0
XCC_FLAGS_test_assert_with_debug = -g -DTEST_ASSERT=1 -DXASSERT_ENABLE_DEBUG=1
XCC_FLAGS_test_fail_with_debug = -g -DTEST_FAIL=1 -DXASSERT_ENABLE_DEBUG=1
XCC_FLAGS_test_unreachable_with_debug = -g -DTEST_UNREACHABLE=1 -DXASSERT_ENABLE_DEBUG=1
XCC_FLAGS_test_unitB_disabled = -g -DTEST_ASSERT=1 -DTEST_MULTI_UNIT -DXASSERT_DISABLE_ASSERTIONS_UNITB=1
XCC_FLAGS_test_unitA_disabled = -g -DTEST_ASSERT=1 -DTEST_MULTI_UNIT -DXASSERT_DISABLE_ASSERTIONS_UNITA=1
XCC_FLAGS_test_unitB_enabled = -g -DTEST_ASSERT=1 -DTEST_MULTI_UNIT -DXASSERT_ENABLE_ASSERTIONS=0 -DXASSERT_ENABLE_ASSERTIONS_UNITB=1
XCC_FLAGS_test_unitA_enabled = -g -DTEST_ASSERT=1 -DTEST_MULTI_UNIT -DXASSERT_ENABLE_ASSERTIONS=0 -DXASSERT_ENABLE_ASSERTIONS_UNITA=1

XCC_FLAGS_unitA.xc = $(XCC_FLAGS) -DDEBUG_UNIT=UNITA
XCC_FLAGS_unitB.c = $(XCC_FLAGS) -DDEBUG_UNIT=UNITB

# This change to the module path is so that this application can be in the
# tests sub-directory in it's git repo
ifeq ($(notdir $(abspath ..)),tests)
PATHSEP = $(if $(findstring Windows, $(OS))$(findstring WINDOWS,$(OS)),;,:)
XMOS_MODULE_PATH := $(XMOS_MODULE_PATH)$(PATHSEP)../../..
endif


# The USED_MODULES variable lists other module used by the application. 
USED_MODULES = module_xassert



#=============================================================================
# The following part of the Makefile includes the common build infrastructure
# for compiling XMOS applications. You should not need to edit below here.

XMOS_MAKE_PATH ?= ../..
include $(XMOS_MAKE_PATH)/xcommon/module_xcommon/build/Makefile.common
