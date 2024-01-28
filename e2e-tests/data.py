import sys
import os
from consts import UserExecutable as UE
from consts import PATH_NFS as NFS
sys.path.append("..")
import sandbox.data.word_counter as word_counter
import sandbox.data.sample as sample
import sandbox.data.real_estate as real_estate
import sandbox.data.genomic_dna as genomic_dna


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
        case UE.REAL_ESTATE:
            real_estate.generate(dir=data_dir,*args, **kwargs)
        case UE.GENOMIC_SAMPLE:
            genomic_dna.generate(dir=data_dir,*args, **kwargs)
        case _:
            raise ValueError("Generating code not available")
