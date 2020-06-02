import sys
import cv2
import os 
import pytesseract
from pathlib import Path

path = "./"
files = []
sizes = []

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

    def build_whole_pipe():
        # Enum all files
        files = [f for f in os.listdir(self.source_repo) if os.path.isfile(f)]

        transfer = [

        ]

        for file in files:
            if ('.png' in file) or ('.jpg' in file):
                lb = label_of_file(file)

                if lb != ' ':
                    # Success
                        transfer.append(
                            [ file
                            ]
                        )

        return

    def alter_file_name(file, label):
        path = pathlib.Path(file)



        return
#
# Build Pip labelling
# 

img = cv2.imread(sys.argv[1])
custom_config = r'-psm 10'
mystr = pytesseract.image_to_string(img, config=custom_config)

# print(mystr)

path = Path(sys.argv[1])
print(path.parent)
print(path.name)
print(path)


