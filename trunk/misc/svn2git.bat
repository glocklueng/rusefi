
rem call git_force_update.bat

echo going to Root of SVN project
cd ..
echo Updating from SVN
call svn update

set RUSEFI_GIT_PATH=..\rusefi.github\rusefi

echo going to git version


ls -l %RUSEFI_GIT_PATH%
rd /s /q %RUSEFI_GIT_PATH%\firmware
rd /s /q %RUSEFI_GIT_PATH%\hardware
rd /s /q %RUSEFI_GIT_PATH%\java_console
rd /s /q %RUSEFI_GIT_PATH%\unit_tests
rd /s /q %RUSEFI_GIT_PATH%\win32_functional_tests

cp -r firmware %RUSEFI_GIT_PATH%
cp -r hardware %RUSEFI_GIT_PATH%
cp -r java_console %RUSEFI_GIT_PATH%
cp -r unit_tests %RUSEFI_GIT_PATH%
cp -r win32_functional_tests %RUSEFI_GIT_PATH%



cd %RUSEFI_GIT_PATH%

git config --global user.email "russianefi@gmail.com"
git config --global user.name "rusEfi"

git add *
git commit -a -m "auto-sync"
git push --repo https://rusefi:PASSWORD@github.com/rusefi/rusefi
