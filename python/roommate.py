#!/usr/bin/env python2

import sys
import argparse
import fileinput
import os, inspect

datafile = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))) + "/datafiles/roommates"
datafile2 = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))) + "/datafiles/expenses"

parser = argparse.ArgumentParser(description='Roommates')
parser.add_argument('-a', '--add', help='add new roommate')
parser.add_argument('-r', '--remove', help='remove roommate')
parser.add_argument('-al', '--all', action='store_true', help='print all roomates')

args = vars(parser.parse_args())

#check if args['add'] != 'None' write to the file
#check for the name if the name exists throw error

if (args['add']):
	for line in fileinput.input(datafile):
		if args['add'] == line.strip():
			print "'" + args['add'] + "' already exists in roommates datafile."
			sys.exit(0)
	open(datafile, "a").write(args['add']+'\n')
	print "Successfully added " + args['add'] + "."
	

if (args['remove']):
	exists = False;
	f = open(datafile, "r")
	for line in f:
		#lines = f.readlines()
		if line.strip() == args['remove']:
			exists = True
			break
	if not exists:
		print "'" + args['remove'] + "' does not exist in roommates datafile."
		exit(1)
	f.close()
	
	f = open(datafile, "r")
	#data = f.readlines()
	#print data
	data = ""
	for line in f:
		if not (args['remove'] == line.strip()):
			data += line
	f.close()
	open(datafile, "w").write(data)
	print "Successfully removed " + args['remove'] + "."

	#delete entries for roommate from expenses
	expdata = ""
	f2 = open(datafile2, "r")
	for line in f2:
		if not(args['remove'] in line):
			expdata += line
	f2.close()
	open(datafile2, "w").write(expdata)

if args['all']:
	with open(datafile, 'r') as fin:
		print fin.read().strip()
