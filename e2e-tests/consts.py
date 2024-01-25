import enum

class Executable(enum.Enum):
    MASTER = 'master'
    WORKER = 'worker'

PATH_TO_PACKAGE = "../package"

SANITY_TIMEOUT=10 # secs
START_PORT=7777