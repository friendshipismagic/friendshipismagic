LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := friendshipismagic

LOCAL_SRC_FILES := main.cpp \
	Application.cpp \
	StateStack.cpp \
	TitleState.cpp \
	State.cpp \
	jsoncpp.cpp

LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main

LOCAL_CPP_FEATURES := exceptions rtti

include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)
