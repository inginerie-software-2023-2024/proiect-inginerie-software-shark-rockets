import sys
import os
from consts import UserExecutable as UE
from consts import PATH_NFS as NFS
sys.path.append("..")
import sandbox.data.word_counter as word_counter

def gen_data(user,executable,*args, **kwargs):
    data_dir=f"{NFS}/{user.dir()}/data/{executable.value}/"
    directory = os.path.dirname(data_dir)
    if not os.path.exists(directory):
        os.makedirs(directory)
    match executable:
        case UE.SAMPLE:
            print("gen sample data")
        case UE.WORD_COUNTER:
            word_counter.generate(dir=data_dir,*args, **kwargs,)
        case _:
            raise ValueError("Generating code not available")