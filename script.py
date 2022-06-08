#!/usr/bin/env python
 
import sys
import os.path
 
# This is a tiny script to help you creating a CSV file from a face
# database with a similar hierarchie:
#
#  philipp@mango:~/facerec/data/at$ tree
#  .
#  |-- README
#  |-- s1
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#  |-- s2
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#  ...
#  |-- s40
#  |   |-- 1.pgm
#  |   |-- ...
#  |   |-- 10.pgm
#
 
if __name__ == "__main__":
 
    #if len(sys.argv) != 2:
    #   print("usage: create_csv <base_path>")
    #   sys.exit(1)
 
    BASE_PATH = "G:/Qprogram/untitled/photo"   #数据集的路径
    SEPARATOR = ";"
    fh = open("G:/Qprogram/untitled/photo/at.txt",'w')   #生成csv格式数据的路径
    label = 0
    for dirname, dirnames, filenames in os.walk(BASE_PATH):
        for subdirname in dirnames:
            subject_path = "%s/%s" % (dirname, subdirname)
            for filename in os.listdir(subject_path):
                abs_path = "%s/%s" % (subject_path, filename)
                print("%s%s%d" % (abs_path, SEPARATOR, label))
                fh.write(abs_path)
                fh.write(SEPARATOR)
                fh.write(str(label))
                fh.write("\n")
            label = label + 1
    fh.close()