import os
import shutil
import pytest

def sync(src_path, dst_path):
    """Syncs everything from src_path to dst_path and removes extra items in dst_path."""
    os.makedirs(dst_path, exist_ok=True)
    src_items = set(os.listdir(src_path))
    dst_items = set(os.listdir(dst_path))

    for item in dst_items - src_items:
        item_path = os.path.join(dst_path, item)
        if os.path.isdir(item_path):
            shutil.rmtree(item_path)
        else:
            print(f"Removing: {item_path}")
            os.remove(item_path)

    for item in src_items:
        s = os.path.join(src_path, item)
        d = os.path.join(dst_path, item)

        if os.path.isdir(s):
            sync(s, d)
        else:
            print(f"Copying: {s} to {d}")
            shutil.copy2(s, d)


