import os

from PIL import Image


clear_color = (0, 0, 255)
FrameXSize = 48
FrameYSize = 48

our_dir = os.path.dirname(__file__)

im = Image.open(os.path.join(our_dir, "spritesheet.png")).convert("RGB")
SheetXSize, SheetYSize = im.size

SheetY = 0

while SheetY < SheetYSize:
    SheetX = 0
    while SheetX < SheetXSize:
        XOffset = FrameXSize
        YOffset = FrameYSize
        for i in range(FrameYSize-1, -1, -1):
            for j in range(FrameXSize-1, -1, -1):
                if im.getpixel((SheetX+j, SheetY+i)) != clear_color:
                    YOffset = i
                    if j < XOffset:
                        XOffset = j
        SheetX = SheetX + FrameXSize
        if XOffset < FrameXSize:
            print (XOffset, YOffset, sep=", ")
    SheetY = SheetY + FrameYSize

print ('Done!')

