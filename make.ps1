#Requires -Version 3.0

[CmdletBinding()]
param
(
	[Parameter()][switch]$Test
)

Set-StrictMode -Version Latest

$ErrorActionPreference = 'Stop'

$Path_Compiler = 'C:\c_code\gbdk\bin\lcc'
$Path_Emulator = 'C:\c_code\bgb\bgb64'
$Path_Input = 'main.c songmario.c songwinner.c sound.c songbaseball.c'
$Path_Output = 'maximosnail.gb'

function Execute
{
	[CmdletBinding()]
	param
	(
		[Parameter(Mandatory=$true, Position=0)][String]$FilePath,
		[Parameter(Position=1, ValueFromRemainingArguments=$true)][String[]]$ArgumentList
	)

	if (-not $PSBoundParameters.ContainsKey('ArgumentList'))
	{
		$Process = (Start-Process -FilePath $FilePath -NoNewWindow -PassThru -Wait)
	}
	else
	{
		$Process = (Start-Process -FilePath $FilePath -ArgumentList $ArgumentList -NoNewWindow -PassThru -Wait)
	}

	if ($Process.ExitCode -ne 0)
	{
		exit $Process.ExitCode
	}
}

Execute $Path_Compiler '-Wa-l' '-Wl-m' '-Wl-j' '-DUSE_SFR_FOR_REG' '-o' $Path_Output $Path_Input

if ($Test)
{
	$Processes = [System.Diagnostics.Process]::GetProcessesByName('bgb64')

	if ($Processes.Count -eq 0)
	{
		Start-Process -FilePath $Path_Emulator -ArgumentList @('--watch', $Path_Output)
	}
}
