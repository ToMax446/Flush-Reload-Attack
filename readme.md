# FR-GTK

This is my FR attack on GTK library project
It will launch an attack and a dummy target that would eavesdrop on keystrokes in a GTK window.

## Activation

Extract the zip into the Mastik folder, alongside the /src folder.

Then just activate the python script.

```bash
python3 run_project_script.py
```
The python script will use the `make` to make the C target and attacker, and then will launch them.

## Changing test's settings
You can change the duration of each test or the number of tests by editing the global variable/macro in the `.c`/`.py` files

## Paper's Settings
The results of the tests that ran for the paper were using stats of `TIMES = 10` and RUN_TIME = 135