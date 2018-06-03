import os
import sys
import shutil

def remove_prefix_of_directories(work_path, prefix):

    folder_list = os.listdir(work_path)
    print(folder_list)
    moving_folder_list = [f for f in folder_list if f.startswith(prefix)]
    print(moving_folder_list)
    for fn in moving_folder_list:
        newname = fn.replace(prefix, '', 1)
        oldpath = os.path.join(work_path, fn)
        newpath = os.path.join(work_path, newname)
        print(oldpath, newpath)
        shutil.move(oldpath, newpath)
    

print(sys.argv)
remove_prefix_of_directory(sys.argv[1], sys.argv[2])
        
