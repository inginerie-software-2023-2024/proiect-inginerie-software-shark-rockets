import enum
import os

# light
CLUSTER_SIZES=[4]
FAULTY_PERCENT=[50]


# full testing
# CLUSTER_SIZES=[1,2,5,10,20,50]
# FAULTY_PERCENT=[25,50,75]


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
