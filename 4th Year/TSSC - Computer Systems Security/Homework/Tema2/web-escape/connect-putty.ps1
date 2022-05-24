#!/usr/bin/env pwsh
# Putty + PowerShell based web tunnelling script.
# For when you don't have WSL / Cygwin tools available ;)
# Hope it works :D

$SSHKEY = $args[0]
if ($SSHKEY -eq $null) {
	$SSHKEY = "id_rsa.ppk"
}
$LOCAL_PORT="8080"
$DEST="student@isc2022.1337.cx"

# Start a shared Putty session
# PRESS ENTER AND
# KEEP THIS WINDOW OPEN UNTIL THE CONTAINER STARTS!
start-process -FilePath "plink" -ArgumentList "-ssh","-share","-N","-i","$SSHKEY","$DEST"

write-host "Please press ENTER in the newly opened window..."
write-host "Also, please keep that window open at all time!"
write-host "After you confirmed putty and accepted the server's key (if asked), press any key to continue here ;)"
[void][System.Console]::ReadKey($true)

plink -shareexists "$DEST"
if (! $?) {
	Write-Error "Putty connection multiplexing check failed!"
	exit 1
}

$ALLOCATED_PORT = (plink -ssh -batch -share "$DEST" get-forward-port) | Out-String
$ALLOCATED_PORT = $ALLOCATED_PORT.Trim()
if (! $ALLOCATED_PORT) {
	Write-Error "Unable to get the forward port allocated!"
	exit 1
}
echo "Allocated server port: ${ALLOCATED_PORT}"

# Forward localhost:8080 to the server's allocated port
# (And start our container)
plink -ssh -batch -share -L "${LOCAL_PORT}:localhost:${ALLOCATED_PORT}" "$DEST" start

