import subprocess as sp
import json
import time
import os
import webbrowser
import signal

TIMES = 10
DELTA = 100000
RUN_TIME = 135

data = {}
#clean_ret = sp.call("make clean", shell=True, stdout=sp.PIPE)
build_ret = sp.call("make",
                     shell=True, stdout=sp.PIPE)
avg = 0

for i in range(TIMES):
    data_pos = 'try {0}: '.format(i)
    data[data_pos] = []
    print("""
===========================
=        ==================
====  =====================
====  =====================
====  ======   ===  =  = ==
====  =====     ==        =
====  =====  =  ==  =  =  =
====  =====  =  ==  =  =  =
====  =====  =  ==  =  =  =
====  ======   ===  =  =  =
===========================""")
    print ("Try {0}".format(i))
    print("STARTING ATTACKER PROCCESS:\n./FR-gtk2\n\n")
    attacker = sp.Popen("./FR-gtk2", shell=False)
   # print("STARTING GTK WINDOW TARGET:\npython3 target.py\n\n")
   # target = sp.Popen("python3 target.py", shell=True)
    print("STARTING GTK WINDOW TARGET:\n./target\n\n")
    target = sp.Popen("./target", shell=False)

    time.sleep(RUN_TIME)

   
    os.system('pkill -TERM -P {pid}'.format(pid=attacker.pid))
    os.system('pkill -TERM -P {pid}'.format(pid=target.pid))
    os.kill(attacker.pid, signal.SIGTERM)
    os.kill(target.pid, signal.SIGTERM)
    attacker.kill()
    target.kill()
    attacker.terminate()
    target.terminate()


    with open("input.json", 'rb+') as file_handle:
        file_handle.seek(-2, os.SEEK_END)
        file_handle.truncate()
    with open ("input.json", 'a') as file_handle:
        file_handle.write("]}")

    target_input = open("input.json", 'r')
    target_data = json.load(target_input)
    target_input.close()
    
    with open("attacker_input.json", 'rb+') as file_handle:
        file_handle.seek(-2, os.SEEK_END)
        file_handle.truncate()
    with open ("attacker_input.json", 'a') as file_handle:
        file_handle.write("]}")
    attacker_input = open("attacker_input.json", 'r')
    attacker_data = json.load(attacker_input)
    attacker_input.close()

    hit_count = 0
    total_count = len(target_data['input time'])
    # for i in range(len(target_data['input time'])):
       # target = target_data['input time'][i]
       # attacker = attacker_data['input time'][i]
       # print ("target time: ",target)
       # print ("attacker time: ",attacker)
      #  if (attacker_data['input time'][i] is not None) and (abs(target_data['input time'][i] - attacker_data['input time'][i]) <= 50):
    for attacker_time_stamp in attacker_data['input time']:
        for target_time_stamp in target_data['input time']:
            delta = abs(attacker_time_stamp-target_time_stamp)
            if delta <= DELTA:
                hit_count += 1
                break
    ratio = hit_count/total_count
    avg += ratio
    data[data_pos].append(ratio)


data['average'] = avg/TIMES

with open('results.json', 'w+') as results_json:
    json.dump(data, results_json, ensure_ascii=False)
#sp.check_call(['open', "results.json"])
editor = os.getenv('EDITOR')
if editor:
    os.system(editor + ' ' + "results.json")
else:
    webbrowser.open("results.json")
