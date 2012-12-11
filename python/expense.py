#!/usr/bin/env python2

import sys
import argparse
import fileinput
import decimal

parser = argparse.ArgumentParser(description='Expenses')
parser.add_argument('-v', '--view', help='view expenses')
subparser = parser.add_subparsers()
expenses = subparser.add_parser('add')
expenses.add_argument('expensed_roommate')
expenses.add_argument('amount', type=float)
expenses.add_argument('debted_roommate', nargs='+')
args = vars(parser.parse_args())

amount_owed = args['amount']/len(args['debted_roommate'])
count = 0
debted = args['debted_roommate']

# boolean set to false
# if it finds it set to true
# if not print error message
# for line in fileinput.input("./datafiles/roomates"):

while (count < len(debted)):
	print (debted[count] + ' OWES ' + args['expensed_roommate'] + ' $' + str("%.2f" % amount_owed) + '\n')
	open("./datafiles/expenses", "a").write(debted[count] + ' OWES ' + args['expensed_roommate'] + ' $' + str("%.2f" % amount_owed) + '\n')
	count = count + 1


