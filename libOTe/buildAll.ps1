
# Update this if needed
$MSBuild = 'C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe'

if(!(Test-Path $MSBuild))
{
    Write-Host "Could not find MSBuild as"
    Write-Host "     $MSBuild"
    Write-Host ""
    Write-Host "Please update its lication in the script"

    exit
}

cd ./thirdparty/win

& ./getBoost.ps1
& ./getMiracl.ps1

cd ../..

& $MSBuild libOTe.sln  /p:Configuration=Release /p:Platform=x64
& $MSBuild libOTe.sln  /p:Configuration=Debug /p:Platform=x64


