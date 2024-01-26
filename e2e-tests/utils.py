import os
import shutil

def files_are_same(src_file, dst_file):
    """Check if two files are the same based on size and modification time."""
    src_stat = os.stat(src_file)
    dst_stat = os.stat(dst_file)
    return src_stat.st_size == dst_stat.st_size and src_stat.st_mtime == dst_stat.st_mtime

def sync(src_path, dst_path):
    """Syncs everything from src_path to dst_path and removes extra items in dst_path."""
    os.makedirs(dst_path, exist_ok=True)
    src_items = set(os.listdir(src_path))
    dst_items = set(os.listdir(dst_path))

    for item in dst_items - src_items:
        item_path = os.path.join(dst_path, item)
        if os.path.isdir(item_path):
            continue # dont remove folders for now, XXX create a method to cleanup jobs after tests
            # shutil.rmtree(item_path)
        else:
            os.remove(item_path)

    for item in src_items:
        s = os.path.join(src_path, item)
        d = os.path.join(dst_path, item)

        if os.path.isdir(s):
            sync(s, d)
        else:
            # Copy file only if it's different or doesn't exist in the destination
            if not os.path.exists(d) or not files_are_same(s, d):
                shutil.copy2(s, d)

def assert_log_chain(chain:list):
    for fun in chain:
        ans = fun()
        assert ans != None
        
def get_file_iterators(directory):
    file_iterators = []

    # Iterate over all files in the given directory
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)
        
        # Check if it's a file and not a directory
        if os.path.isfile(file_path):
            # Open the file and create an iterator
            file = open(file_path, 'r')
            iterator = iter(file)
            file_iterators.append(iterator)

    return file_iterators

def serialize_iterators(iterators):
    all_lines = []
    for file_iterator in iterators:
        for line in file_iterator:
            all_lines.append(line.strip())
    return all_lines
