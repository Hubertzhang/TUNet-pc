#-------------------------------------------------
#
# Project created by QtCreator 2015-08-05T22:09:03
#
#-------------------------------------------------

TARGET = TUNet
TEMPLATE  = subdirs

SUBDIRS += TUNet-pc QtHpple

TUNet-pc.depends += QtHpple
CONFIG += mobility
MOBILITY = 

