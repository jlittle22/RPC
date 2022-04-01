import subprocess
import os

PATH_TO_EXECUTABLE = "./idl_to_json"

def idl_to_json(filepath):
    args = (PATH_TO_EXECUTABLE, filepath)
    proc = subprocess.Popen(args, stdout=subprocess.PIPE)
    proc.wait()
    
    return proc.stdout.read().decode()