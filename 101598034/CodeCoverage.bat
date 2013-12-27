SET PATH=c:\Program Files (x86)\Microsoft Visual Studio 10.0\Team Tools\Performance Tools\
vsinstr -coverage @filters.txt
vsperfcmd -start:coverage -output:CodeCoverage.coverage
"Debug\101598034_UnitTesting.exe"
vsperfcmd -shutdown