@echo off

set filename= ONEBIT.cpp

if exist %filename% del %filename%

:: Replace the line below with: for /r %%a in (*.cpp) do (
:: to also seek out and merge .cpp files in nearby, recursive directories.
for /r %%a in (*.cpp) do (
echo -- -------------------------------------------------------- >>%filename%
echo -- %%a >>%filename%
echo -- -------------------------------------------------------- >>%filename%
copy/b %filename%+"%%a" %filename%
echo. >>%filename%
echo. >>%filename%)
:: Replace the line below with: for /r %%a in (*.h) do (
:: to also seek out and merge .h files in nearby, recursive directories.
for /r %%a in (*.h) do (
echo -- -------------------------------------------------------- >>%filename%
echo -- %%a >>%filename%
echo -- -------------------------------------------------------- >>%filename%
copy/b %filename%+"%%a" %filename%
echo. >>%filename%
echo. >>%filename%)