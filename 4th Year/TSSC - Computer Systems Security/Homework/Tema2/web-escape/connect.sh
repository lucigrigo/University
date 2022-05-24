#!/bin/bash
# OpenSSH-based web tunnelling script.

SSHKEY="${1:-id_rsa}"
LOCAL_PORT=8080
TASK_SERVER=isc2022.1337.cx
DEST=student@$TASK_SERVER
SOCKET=/tmp/websshsocket

# cleanup hook (exits the multiplexing SSH process)
function cleanup() {
	[[ ! -f "$SOCKET" ]] || \ 
		ssh -S "$SOCKET" -O exit "$DEST" >/dev/null 2>&1 || true
}
trap cleanup EXIT

#set -x  # uncomment for debugging
set -e

# start a multiplexing (-M) SSH connection
# background (-f), no command (-N), no stdin (-n), disable pseudo-TTY (-T)
ssh -M -S "$SOCKET" -i "$SSHKEY" -fNnT "$DEST"
# control multiplexing master process (-O)
# check connection (script will exit if fails because of "set -e")
ssh -S "$SOCKET" -O check "$DEST"

# run the 'get-forward-port' remote command (implemented in server script)
ALLOCATED_PORT=$(ssh -S "$SOCKET" "$DEST" get-forward-port) || {
	echo "Could not allocate port on server:" >&2
	echo "$ALLOCATED_PORT" >&2
	exit 1
}
if [[ -z "$ALLOCATED_PORT" ]]; then
	echo "Could not allocate port on server!" >&2
	exit 1
fi
# echo "Allocated server port: $ALLOCATED_PORT"
# add a forwarded port to the multiplexed connection
ssh -S "$SOCKET" -O forward -o "ExitOnForwardFailure=yes" -L "$LOCAL_PORT:localhost:$ALLOCATED_PORT" "$DEST"

# finally, start the interactive shell (implemented as remote script)
ssh -S "$SOCKET" -t "$DEST" start

