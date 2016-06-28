echo "INIT SOURCES"
git submodule init
git submodule update
cd FriendshipIsMagic
android update project --target "android-23" --path .

echo "\nCOMPILING SOURCES"
ndk-build

echo "\nCOMPILING RESOURCES"
(cd ../AssetSources && python3 ../Tools/convert_png.py . ../FriendshipIsMagic/assets/)

echo "\nCREATING APK"
ant debug

echo "\nINSTALLING ON PHONE"
ant installd
