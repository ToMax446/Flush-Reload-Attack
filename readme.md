# FR-GTK
Flush + Reload is a fast L3 cache attack.

This is my F+R attack proof of concept, which I have implemented an attack on GTK library.
It will launch an attack that would eavesdrop on keystrokes in a GTK window, and a dummy target that would "type" in a gtk window.

## Attacker
The attacker was implemented using [MASTIK](https://cs.adelaide.edu.au/~yval/Mastik/Mastik.pdf) and requires MASTIK in order to work. Here is just my code.

## Target
The target was implemented in C language. I have implemented a python version of it but in order to keep it simple for measuring time more accurately I decided to use the C version. The target will mimic a benign process/user. It will randomly will "type" input to a GTK window, in random times making it more realistic like and harder to detect.

## Mesurement
In order to understand the attack's efficiency I made both the attacker and the target to document their typing/keystroke discovery. After the run has ended, my python script will test the outputs of the attacker and the target and will measure those which the time difference was lower than `DELTA` (can be changed in the code).
The python script will document it's result in a JSON file and after a few runs will document the avarage.

## Results
When I tested the script for the last time it ran for about 22.5 minutes resulting in avarage of 0.6901 accuracy over 10 runs which was lower than I exptected but I was using a VM which adds noise to the measurement of the cache.
It can be optimized by using a Linux machine, and changing the time and the ==DELTA==.

## Activation

Extract the zip into the Mastik folder, alongside the /src folder.

Then just activate the python script.

```bash
python3 run_project_script.py
```
The python script will use the `make` to make the C target and attacker, and then will launch them.

## Changing test's settings
You can change the duration of each test or the number of tests by editing the global variable/macro in the `.c`/`.py` files
