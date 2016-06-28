LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := friendshipismagic

LOCAL_SRC_FILES := main.cpp \
	../deps/box2d/include/Box2D/Collision/b2BroadPhase.cpp \
	../deps/box2d/include/Box2D/Collision/b2CollideCircle.cpp \
	../deps/box2d/include/Box2D/Collision/b2CollideEdge.cpp \
	../deps/box2d/include/Box2D/Collision/b2CollidePolygon.cpp \
	../deps/box2d/include/Box2D/Collision/b2Collision.cpp \
	../deps/box2d/include/Box2D/Collision/b2Distance.cpp \
	../deps/box2d/include/Box2D/Collision/b2DynamicTree.cpp \
	../deps/box2d/include/Box2D/Collision/b2TimeOfImpact.cpp \
	../deps/box2d/include/Box2D/Collision/Shapes/b2ChainShape.cpp \
	../deps/box2d/include/Box2D/Collision/Shapes/b2CircleShape.cpp \
	../deps/box2d/include/Box2D/Collision/Shapes/b2EdgeShape.cpp \
	../deps/box2d/include/Box2D/Collision/Shapes/b2PolygonShape.cpp \
	../deps/box2d/include/Box2D/Common/b2BlockAllocator.cpp \
	../deps/box2d/include/Box2D/Common/b2Draw.cpp \
	../deps/box2d/include/Box2D/Common/b2Math.cpp \
	../deps/box2d/include/Box2D/Common/b2Settings.cpp \
	../deps/box2d/include/Box2D/Common/b2StackAllocator.cpp \
	../deps/box2d/include/Box2D/Common/b2Timer.cpp \
	../deps/box2d/include/Box2D/Dynamics/b2Body.cpp \
	../deps/box2d/include/Box2D/Dynamics/b2ContactManager.cpp \
	../deps/box2d/include/Box2D/Dynamics/b2Fixture.cpp \
	../deps/box2d/include/Box2D/Dynamics/b2Island.cpp \
	../deps/box2d/include/Box2D/Dynamics/b2WorldCallbacks.cpp \
	../deps/box2d/include/Box2D/Dynamics/b2World.cpp \
	../deps/box2d/include/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
	../deps/box2d/include/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
	../deps/box2d/include/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
	../deps/box2d/include/Box2D/Dynamics/Contacts/b2Contact.cpp \
	../deps/box2d/include/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
	../deps/box2d/include/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
	../deps/box2d/include/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
	../deps/box2d/include/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
	../deps/box2d/include/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2GearJoint.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2Joint.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
	../deps/box2d/include/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
	../deps/box2d/include/Box2D/Rope/b2Rope.cpp \
	core/application.cpp \
	core/world.cpp \
	states/statestack.cpp \
	states/splash-state.cpp \
	states/titlestate.cpp \
	states/state.cpp \
	states/gamestate.cpp \
	states/settings-state.cpp \
	systems/physicsystem.cpp \
	systems/graphicsystem.cpp \
	systems/inputsystem.cpp \
	systems/timersystem.cpp \
	systems/collisionsystem.cpp \
	systems/healthsystem.cpp \
	systems/soundsystem.cpp \
	systems/logicsystem.cpp \
	systems/itemsystem.cpp \
	systems/network-system.cpp \
	systems/scoresystem.cpp \
	systems/weaponsystem.cpp \
	network/udp-agent.cpp \
	network/udp-exception.cpp \
	ressources/jsoncpp.cpp\
	ressources/filestream.cpp \
	android/filestreamimpl.cpp


LOCAL_C_INCLUDES := . \
	$(LOCAL_PATH)/../deps/box2d/include/ #WORKAROUND 

LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main

LOCAL_CPP_FEATURES := exceptions rtti

LOCAL_CFLAGS += -DANDROID_BUILD
LOCAL_CPPFLAGS += -DANDROID_BUILD

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,./deps)
#$(call import-module,gdx-box2d)
$(call import-module,sfml)


