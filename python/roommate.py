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
	for line in fileinput.input("./datafiles/roomates"):
		if args['add'] == line.strip():
			print "already exists"
			sys.exit(0)
	open("./datafiles/roomates", "a").write(args['add']+'\n')
	

if (args['remove']):
	exists = False;
	for line in fileinput.input("./datafiles/roomates"):
		lines = f.readlines()
		if line == args['remove']:
			exists = True
			break
	if not exists:
		print "Roommate does not exist"
	
	
	for line in fileinput.input("./datafiles/roomates"):
		if not args['remove'] == line.strip():
			f.write(line)
			
			
			
			
			
			
			
			
			
			
			
