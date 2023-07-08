$target = $args[0]
Add-AppveyorTest -Name "$target" -Framework "Custom" -Filename "$target" -Outcome Running
$start = [Math]::Round((Get-Date).ToFileTimeUTC() / 10000)

xmake b "$target"
if ( ! $? ) {
    $time = [Math]::Round((Get-Date).ToFileTimeUTC() / 10000) - $start
    Update-AppveyorTest -Name "$target" -Outcome Failed -Duration $time -ErrorMessage "Failed to build"
    exit
}
xmake r "$target"
if ( ! $? ) {
    $time = [Math]::Round((Get-Date).ToFileTimeUTC() / 10000) - $start
    Update-AppveyorTest -Name "$target" -Outcome Failed -Duration $time -ErrorMessage "Error running test"
    exit
}

$time = [Math]::Round((Get-Date).ToFileTimeUTC() / 10000) - $start
Update-AppveyorTest -Name "$target" -Outcome Passed -Duration $time