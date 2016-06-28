# FriendshipIsMagic

## Introduction
Ami ou ennemi


## Compilation

### Android

Dépendances du projet : 

+ Android SDK
+ Android NDK
+ SFML
+ Box2D
+ Ant
+ Adb

Pour compiler le projet pour android, il faut installer le Sdk et le Ndk, puis définir les variables :
+ ANDROID_HOME : le chemin vers le Sdk
+ ANDROID_NDK  : le chemin vers le NDK

Puis, après clone du dépot, faire depuis la racine du dépôt, avec un portable branché et autorisé par le Sdk : 

```
git submodule init
git submodule update
(cd AssetSources && python3 ../Tools/convert_png.py . ../FriendshipIsMagic/assets/Graphics)
cd FriendshipIsMagic
android update project --target "android-23" --path .
ndk-build
ant release
ant installr
```

### Linux 

SFML et Box2D doivent être installées sur votre système ou accessible grâce au FindSFML.cmake et FindBox2D.cmake.

Une des possibilités est d'utiliser la variable SFML_ROOT pour cmake.


```
cd FriendshipIsMagic
mkdir build
cd build
cmake ..
make
cd ../assets/
../build/FriendshipIsMagic
```
