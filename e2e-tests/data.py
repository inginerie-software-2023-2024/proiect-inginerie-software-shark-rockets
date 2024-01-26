import sys
import os
from consts import UserExecutable as UE
from consts import PATH_NFS as NFS
sys.path.append("..")
import sandbox.data.word_counter as word_counter
import sandbox.data.sample as sample

from functools import lru_cache
import logging


@lru_cache(maxsize=1) # cache the function, ie in case the same data was used in the previous computation dont regenerate
def gen_data(user,executable,*args, **kwargs):
    data_dir=f"{NFS}/{user.dir()}/data/{executable.value}/"
    directory = os.path.dirname(data_dir)
    if not os.path.exists(directory):
        os.makedirs(directory)
    
    match executable:
        case UE.SAMPLE:
            sample.generate(dir=data_dir,*args, **kwargs)
        case UE.WORD_COUNTER:
            word_counter.generate(dir=data_dir,*args, **kwargs)
        case _:
            raise ValueError("Generating code not available")