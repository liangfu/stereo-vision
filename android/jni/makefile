all:
	cd .. && android update project -p . -s && ndk-build && ant debug

install:
	adb -d install ../bin/MCamVisionActivity-debug.apk

reinstall:
	adb -d install -r ../bin/MCamVisionActivity-debug.apk

clean:
	cd .. && ant clean
