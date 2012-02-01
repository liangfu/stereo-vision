all:
	cd .. && ndk-build && ant debug

rebuild:
	cd .. && rm -rf bin && android update project -p . -s --target android-10 && ndk-build && ant debug

install:
	adb -d install ../bin/TVReality-debug.apk

reinstall:
	adb -d install -r ../bin/TVReality-debug.apk

clean:
	cd .. && ant clean
