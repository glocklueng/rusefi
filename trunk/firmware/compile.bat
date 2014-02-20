rm -rf .dep/

rm -rf build\rusefi.hex
make

cd build
if not exist rusefi.hex echo "compilation failed"
if not exist rusefi.hex exit -1
cd ..

svn info > ../firmware_binary/version.txt
cp config/features.h ../firmware_binary
cp build/rusefi.hex ../firmware_binary
cp build/rusefi.elf ../firmware_binary

cp tunerstudio/rusefi.ini ../firmware_binary

cd ../firmware_binary
del firmaware_binary.zip
7z a firmaware_binary.zip rusefi.hex rusefi.ini features.h flash.bat
cd ../firmware


cd build
java -jar ../../java_tools/gcc_map_reader.jar > ../../firmware_binary/rusefi_ram_report.txt
cd ..

flash.bat