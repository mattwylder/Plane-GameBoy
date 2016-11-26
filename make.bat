del plane.gb
rgbasm -o plane.obj plane.asm
rgblink -o plane.gb plane.obj
del plane.obj
rgbfix -v plane.gb
