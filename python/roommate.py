#!/usr/bin/env python2

import sys
import argparse
import fileinput

parser = argparse.ArgumentParser(description='Roommates')
parser.add_argument('-a', '--add', help='add new roommate')
parser.add_argument('-r', '--remove', help='remove roommate')

args = vars(parser.parse_args())

#check if args['add'] != 'None' write to the file
#check for the name if the name exists throw error

if (args['add']):
	for line in fileinput.input("./datafiles/roommates"):
		if args['add'] == line.strip():
			print "'" + args['add'] + "' already exists in roommates datafile."
			sys.exit(0)
	open("./datafiles/roommates", "a").write(args['add']+'\n')
	print "Successfully added " + args['add'] + "."
	

if (args['remove']):
	exists = False;
	f = open("./datafiles/roommates", "r")
	for line in f:
		#lines = f.readlines()
		if line.strip() == args['remove']:
			exists = True
			break
	if not exists:
		print "'" + args['remove'] + "' does not exist in roommates datafile."
		
	f.close()
	f = open("./datafiles/roommates", "r")
	#data = f.readlines()
	#print data
	data = ""
	for line in f:
		if not (args['remove'] == line.strip()):
			data += line
	f.close()
	open("./datafiles/roommates", "w").write(data)
	
	
			
			
			
			
			
			
			
			
			
			
			
