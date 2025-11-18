# ROBOMASTER Flight Software App

The ROBOMASTER app is a lightweight cFS task that currently exposes a small command and telemetry interface for exercising the driver shim. The default mission build wires the app into `cpu1` alongside `ci_lab`, allowing you to send CCSDS command packets over UDP port `1234`.

## Available commands

| Message ID | Command Code | Description |
|------------|--------------|-------------|
| `0x1800` (`ROBOMASTER_APP_CMD_MID`) | `0` (`ROBOMASTER_APP_NOOP_CC`) | Increment the valid command counter; emits an informational EVS log entry. |
| `0x1800` | `1` (`ROBOMASTER_APP_RESET_COUNTERS_CC`) | Clear the internal `MsgCount`/`ErrorCount` bookkeeping. |
| `0x1800` | `2` (`ROBOMASTER_APP_EXIT_CC`) | Request the ROBOMASTER app to exit cleanly (sets `RunStatus` to `CFE_ES_RunStatus_APP_EXIT`). |

> **Note:** The exit command is the preferred way to terminate the app without sending `SIGINT` to the entire cFS core. When `CI_LAB` receives the command packet it is routed through the Software Bus, the ROBOMASTER main loop exits, and `CFE_ES_ExitApp()` performs the shutdown.

## Sending the quit command with `cmdUtil`

1. Build `cmdUtil` if you have not already:
   ```bash
   cd /home/vincent/Karura/COMMS2026/cFS/tools/cFS-GroundSystem/Subsystems/cmdUtil
   make
   ```
2. Run the cFS core (`sudo ./core-cpu1`) so `ci_lab` is listening on UDP port `1234`.
3. In another terminal, send the exit command (no payload required):
   ```bash
   ./cmdUtil --pktid=0x1800 --cmdcode=2 --endian=LE --host=127.0.0.1 --port=1234
   ```

You should see an EVS message similar to `ROBOMASTER Exit command received`, followed by the app leaving the run loop. Other apps continue running; if you also want to stop the core you can still use `Ctrl+C` afterward.
