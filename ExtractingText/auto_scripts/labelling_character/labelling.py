import sys
import cv2
import os 
import pytesseract
from pathlib import Path
from shutil import copyfile

# 
# Interface for labelling
# 
class ILabellingPipe(object):

    def __init__(self, source_repo, dest_repo):
        super(ILabellingPipe, self).__init__()
        return

    def label_of_file(self, imgfile):
        return

    def build_whole_pipe(self):
        return

class LabellingDirectory(object):

    """docstring for LabellingDirectory"""
    def __init__(self, source_repo, dest_repo):
        super(LabellingDirectory, self).__init__()
        self.source_repo = source_repo
        self.dest_repo = dest_repo

    def label_of_file(self, imgfile):
        img = cv2.imread(imgfile)
        mystr = pytesseract.image_to_string(img,config=r'-psm 10')  # Single character mode

        if (len(mystr) > 0):
            return mystr[0]
        else:
            return ' '

    def build_whole_pipe(self):
        # Enum all files
        files = [os.path.join(self.source_repo, f) for f in os.listdir(str(self.source_repo)) if os.path.isfile(os.path.join(self.source_repo, f)) ]

        print(self.source_repo)
        print(files)

        transfer = [
        ]

        for file in files:
            if ('.png' in file) or ('.jpg' in file):
                print("PROCESSING: ", file)
                lb = self.label_of_file(file)

                if lb != ' ':
                    # Success
                    transfer.append([file, self.alter_file_name(file, lb)])
        
        for transfer1 in transfer:
            # Copy from source to destination
            print("Copy file from ", transfer1[0], " to ", transfer1[1])
            copyfile(transfer1[0], transfer1[1])

        return

    def alter_file_name(self, file, label):
        path = Path(file)
        myext = path.name[len(path.stem):]
        new_file_name = path.stem + "_[LABEL_IS_" + label + "]" + myext

        return os.path.join(path.parent, new_file_name)

#
# Build Pip labelling
# 

img = cv2.imread(sys.argv[1])
custom_config = r'-psm 10'
mystr = pytesseract.image_to_string(img, config=custom_config)

# print(mystr)

ld = LabellingDirectory("/home/ducvd/work/2020/github/cvstudio/ExtractingText/auto_scripts/labelling_character/in/", "out")
ld.build_whole_pipe()


