cmake -E make_directory "Solution/Win" && cmake -E chdir "Solution/Win" cmake -G "Visual Studio 15 Win64" ../../ -DTHE_PROJECT_PREFIX="gBase"

pause