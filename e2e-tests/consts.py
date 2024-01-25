import enum
import os

PATH_TO_PACKAGE = "../package"
PATH_NFS = os.path.expanduser("~/nfs")

class Executable(enum.Enum):
    MASTER = 'master'
    WORKER = 'worker'

class UserExecutable(enum.Enum):
    SAMPLE = "sample"
    REAL_ESTATE = "real_estate"
    WORD_COUNTER = "word_counter"
    GENOMIC_SAMPLE = "genomic_sample"
    
# constants for the tests
SANITY_TIMEOUT=10 # secs
START_PORT=7777