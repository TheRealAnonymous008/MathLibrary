cd bin

for /r "." %%a in (*.exe) do start "" /B "%%~fa"
move /Y *.md ../../

cd ../