#!/usr/bin/env python2

import sys
import argparse
import fileinput
import os, inspect

path = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))

parser = argparse.ArgumentParser(description='Roommates')
parser.add_argument('-a', '--add', help='add new roommate')
parser.add_argument('-r', '--remove', help='remove roommate')

args = vars(parser.parse_args())

#check if args['add'] != 'None' write to the file
#check for the name if the name exists throw error

print args

if (args['add']):
	print "IM HERE"
	for line in fileinput.input(path + "/datafiles/roommates"):
		if args['add'] == line.strip():
			print "'" + args['add'] + "' already exists in roommates datafile."
			sys.exit(0)
	print "here"
	open(path +"/datafiles/roommates", "a").write(args['add']+'\n')
	print "Successfully added " + args['add'] + "."
	

if (args['remove']):
	exists = False;
	f = open(path +"/datafiles/roommates", "r")
	for line in f:
		#lines = f.readlines()
		if line.strip() == args['remove']:
			exists = True
			break
	if not exists:
		print "'" + args['remove'] + "' does not exist in roommates datafile."
		
	f.close()
	f = open(path + "/datafiles/roommates", "r")
	#data = f.readlines()
	#print data
	data = ""
	for line in f:
		if not (args['remove'] == line.strip()):
			data += line
	f.close()
	open(path + "/datafiles/roommates", "w").write(data)
	
	
			
			
			
			
			
			
			
			
			
			
			
