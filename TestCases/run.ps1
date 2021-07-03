[string]$test_filename = $args[0]
[string]$work_dir = $PWD
If($test_filename){
    Write-Host "Compiling $test_filename..."
}
Else {
    $test_filename = "test1.pls"
    Write-Host "Compiling default test file $test_filename..."
}
[string]$test_basename = [io.path]::GetFileNameWithoutExtension($test_filename)

If ([String]::IsNullOrEmpty($test_basename)){
    Write-Host "Error filename!"
    exit(1)
}

Write-Host "Removing $test_basename[c]?.*(exclude $test_basename.pls)..."
Remove-Item $test_basename'c'?'.'* -Exclude $test_basename'.pls'

cd ../src/PL
Write-Host "Compliling PL.exe..."
Remove-Item *.exe
make
cp ./PL.exe $work_dir -Force
cp ./PL.exe $work_dir/../bin -Force
If ($?){
    Write-Host "Done."
}
Else {
    cd $work_dir
    exit(1)
}

cd ../interpret
Write-Host "Compliling interpret.exe..."
Remove-Item *.exe
make
cp ./interpret.exe $work_dir -Force
cp ./interpret.exe $work_dir/../bin -Force
If ($?){
    Write-Host "Done."
}
Else {
    cd $work_dir
    exit(1)
}
cd $work_dir

Write-Host "Running PL.exe..."
echo $test_basename".pls" | ./PL.exe
If ($?){
    Write-Host "Done."
}
Else {
    cd $work_dir
    exit(1)
}

Write-Host "Running interpret.exe..."
echo $test_basename"c.pld" | ./interpret.exe
If ($?){
    Write-Host "Done."
}
Else {
    cd $work_dir
    exit(1)
}
