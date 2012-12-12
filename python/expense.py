#!/usr/bin/env python2

import sys
import argparse
import fileinput
import decimal

# creating the parser
parser = argparse.ArgumentParser(description='Expenses')
subparser = parser.add_subparsers(help='commands')
# parsers for add
add_parser = subparser.add_parser('add', help='add expenses')
add_parser.add_argument('expensed_roommate')
add_parser.add_argument('amount', type=float)
add_parser.add_argument('debted_roommate', nargs='+')
add_parser.set_defaults(which='add')
# parsers for view
view_parser = subparser.add_parser('view', help='view expenses')
view_parser.add_argument('name')
view_parser.set_defaults(which='view')

args = vars(parser.parse_args())
count = 0
count2 = 0
count3 = 0

# for viewing expenses
if(sys.argv[1] == 'view'):
	view_expenses = []
	info = open('./datafiles/expenses', 'r')
	info2 = open('./datafiles/expenses', 'r')

	for line in info.readlines():
		cols = line.split('\t')
		if(cols[0] == args['name']):
			exists = False
			ind = 0
			for each in view_expenses:
				if each[0] == cols[2]:
					exists = True
					break
				ind += 1
			if not exists:
				view_expenses.append([])
				view_expenses[count2].append(cols[2])
				view_expenses[count2].append(float(cols[3][1:].strip()))
				count2 = count2 + 1
			elif exists:
				view_expenses[ind][1] += float(cols[3][1:].strip())
				print float(cols[3][1:].strip())
		print view_expenses	
	info.close()

	for line in info2.readlines():
		cols = line.split('\t')
		if(cols[2] == args['name']):
			exists = False
			ind = 0
			for each in view_expenses:
				if each[0] == cols[0]:
					exists = True
					break
				ind += 1
			if not exists:
				view_expenses.append([])
				view_expenses[count3].append(cols[0])
				view_expenses[count3].append(-1*float(cols[3][1:].strip()))
				count2 = count2 + 1
			elif exists:
				view_expenses[ind][1] -= float(cols[3][1:].strip())
				print float(cols[3][1:].strip())
		print view_expenses	
	info2.close()

# for adding expenses
elif(sys.argv[1] == 'add'):
	# this divides the amount entered by the number of debted roommates
	amount_owed = args['amount']/len(args['debted_roommate'])
	debted = args['debted_roommate']

	# going through debted roommates to enter into file how much is owed by each
	while (count < len(debted)):
		print (debted[count] + ' OWES ' + args['expensed_roommate'] + ' $' + str("%.2f" % amount_owed))
		open("./datafiles/expenses", "a").write(debted[count] + '\tOWES\t' + args['expensed_roommate'] + '\t$' + str("%.2f" % amount_owed) + '\n')
		count = count + 1

# error check
else:
	sys.stderr.write("Incorrect command input. Choose between 'view' or 'add'\n")
	sys.exit(1)

