svn up
call generate_docs

rem http://www.ncftp.com/download/
cd ../doxygen
ncftpput -u u71977750-docs -p rusefi.com /html html/*

