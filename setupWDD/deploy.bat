echo @on
cd ./
set arg1=%1
if "%arg1%" == "p" call cordova platform add android  
set arg2=%2
if "%arg2%" == "b" call cordova build android
echo "install"
call adb install -r E:\WDD\Repository\Pivot\setupWDD\platforms\android\app\build\outputs\apk\debug\app-debug.apk

