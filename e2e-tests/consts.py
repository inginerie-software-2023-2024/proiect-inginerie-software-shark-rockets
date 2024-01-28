import enum
import os

CLUSTER_SIZES=[4]
FAULTY_PERCENT=[50]

PATH_TO_PACKAGE = "../package"
PATH_NFS = os.path.expanduser("~/nfs")
PATH_EUCALYPT_BACKEND = "../eucalypt/node-api/"

USERS_CREDS = {
    "guest":
    {
        'email':'guest',
        'password':None
    },
    "test_user":
    {
        'email':'test@test.com',
        'password':'testtest'
    }
}
USERS = ['guest','test_user']

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
