rem
rem This script would compile firmware, dev console and win32 simulator into a single bundle file
rem This script depends on Cygwin tools: zip
rem

echo Hello rusEfi
date

echo Building win32 functional tests
cd win32_functional_tests
gcc -v
make -v
cd ..



cd firmware
date
echo "CD to ${PWD}"
echo Building firmware
rm -fR .dep
rm -fR build
java -jar ../java_tools/version2header.jar

call clean_compile_two_versions.bat
if not exist deliver/rusefi_release.hex echo FAILED RELEASE
if not exist deliver/rusefi_release.hex exit -1

if not exist deliver/rusefi_debug.hex echo FAILED DEBUG
if not exist deliver/rusefi_debug.hex exit -1

cd ..


echo Building java console
cd java_console
call ant clean
call ant
cd ..

echo Building rusefi simulator
cd win32_functional_tests

mkdir out
rm -rf build
rm -rf .dep
call compile.bat

if not exist build/rusefi_simulator.exe echo FAILED
if not exist build/rusefi_simulator.exe exit -1

cd ..

rm -rf temp
mkdir temp

set folder_name=snapshot_%date:~10%%date:~4,2%%date:~7,2%_%time:~0,2%%time:~3,2%_rusefi
set folder=temp\%folder_name%
# this replaces spaces with 0s - that's needed before 10am
set folder=%folder: =0%

echo %folder%
mkdir %folder%

cp java_console_binary/rusefi_console.jar %folder%
cp win32_functional_tests/build/rusefi_simulator.exe %folder%
cp firmware/tunerstudio/rusefi.ini %folder%

cp firmware/svnversion.h %folder%
cp -r misc/install/openocd %folder% 
cp java_console/rusefi.xml %folder%
cp firmware/deliver/rusefi_release.* %folder%
cp firmware/deliver/rusefi_debug.* %folder%
cp misc/console_launcher/rusefi_console.exe %folder%


cd temp
echo TODO remove .svn folders
for /d /r . %d in (.svn) do @if exist "%d" rd /s/q "%d"
echo "Building bundle"
pwd
zip -r rusefi_bundle.zip *
echo "Bundle ready"

cd %folder_name%
echo "Building only console"
pwd
zip ../rusefi_console.zip rusefi_console.jar rusefi.xml
echo "only console ready"

echo "Changin folder"
cd ..
cd ..                                                             
pwd
date /t

echo "DONE here"