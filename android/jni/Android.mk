LOCAL_PATH:= $(call my-dir)/../../src

include $(CLEAR_VARS)

STRW_PATH := $(shell (echo "import os"; echo "print os.path.relpath(\"$(STRAWBERRY_SDK_PATH)\", \"$(LOCAL_PATH)\")" ) | python )

LOCAL_MODULE := strawberry-prebuilt
LOCAL_SRC_FILES := $(STRW_PATH)/lib/android/$(TARGET_ARCH_ABI)/libstrawberry.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcares-prebuilt
LOCAL_SRC_FILES := $(STRW_PATH)/third-party/android_libs/libs/$(TARGET_ARCH_ABI)/libcares.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcrypto-prebuilt
LOCAL_SRC_FILES := $(STRW_PATH)/third-party/android_libs/libs/$(TARGET_ARCH_ABI)/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libssl-prebuilt
LOCAL_SRC_FILES := $(STRW_PATH)/third-party/android_libs/libs/$(TARGET_ARCH_ABI)/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcurl-prebuilt
LOCAL_SRC_FILES := $(STRW_PATH)/third-party/android_libs/libs/$(TARGET_ARCH_ABI)/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
define  cppinsubdir
	$(patsubst ./%,%, \
	$(shell find $(1) -name "*.cpp" -and -not -name ".*") )
endef

LOCAL_MODULE    := nativesrc

LOCAL_CFLAGS    := -Werror -DNO2_ANDROID
ifeq ($(APP_OPTIM),debug)
	LOCAL_CFLAGS += -DDEBUG
endif

MY_SOURCES := $(call cppinsubdir,$(LOCAL_PATH))
LOCAL_SRC_FILES += $(MY_SOURCES:$(LOCAL_PATH)%=%)
LOCAL_C_INCLUDES += $(STRAWBERRY_SDK_PATH)/include/
LOCAL_C_INCLUDES += $(STRAWBERRY_SDK_PATH)/include/common
LOCAL_C_INCLUDES += $(STRAWBERRY_SDK_PATH)/include/android
LOCAL_C_INCLUDES += $(STRAWBERRY_SDK_PATH)/third-party
LOCAL_C_INCLUDES += $(STRAWBERRY_SDK_PATH)/third-party/android_libs/include

LOCAL_LDLIBS    := -llog -lGLESv1_CM -lz

LOCAL_CPPFLAGS := -fexceptions -frtti

LOCAL_STATIC_LIBRARIES := strawberry-prebuilt libcurl-prebuilt libssl-prebuilt libcrypto-prebuilt libcares-prebuilt 

include $(BUILD_SHARED_LIBRARY)
