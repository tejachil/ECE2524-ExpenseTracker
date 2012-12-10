import sys
import argparse
import fileinput

parser = argparse.ArgumentParser(description='Roommates')
parser.add_argument('-a', '--add', help='add new roommates')
parser.add_argument('-r', '--remove', help='remove roommates')

args = vars(parser.parse_args())


#check if args['add'] != 'None' write to the file
#check for the name if the name exists throw error


if (args['add']):
	for line in fileinput.input("./datafiles/roommates"):
		if args['add'] == line.strip():
			print "already exists"
			sys.exit(0)
	open("./datafiles/roommates", "a").write(args['add']+'\n')
	

if (args['remove']):
	exists = False;
	f = open("./datafiles/roommates", "r")
	for line in f:
		#lines = f.readlines()
		if line.strip() == args['remove']:
			exists = True
			break
	if not exists:
		print "Roommate does not exist"
		
	f.close()
	f = open("./datafiles/roommates", "r")
	#data = f.readlines()
	#print data
	data = ""
	for line in f:
		if not (args['remove'] == line.strip()):
			data += line
	print data
	f.close()
	open("./datafiles/roommates", "w").write(data)
	
	
			
			
			
			
			
			
			
			
			
			
			
