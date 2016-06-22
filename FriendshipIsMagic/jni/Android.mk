LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := friendshipismagic

LOCAL_SRC_FILES := main.cpp \
	application.cpp \
	statestack.cpp \
	titlestate.cpp \
	state.cpp \
	gamestate.cpp \
	world.cpp \
	physicsystem.cpp \
	GraphicSystem.cpp \
	bloc.cpp \
	player.cpp \
	jsoncpp.cpp

LOCAL_C_INCLUDES := . \
	$(LOCAL_PATH)/../deps/gdx-box2d/include/ #WORKAROUND 

LOCAL_SHARED_LIBRARIES := gdx-box2D
LOCAL_SHARED_LIBRARIES += sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main

LOCAL_CPP_FEATURES := exceptions rtti
include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,./deps)
$(call import-module,gdx-box2d)
$(call import-module,sfml)


