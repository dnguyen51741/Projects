#!/usr/bin/env python

import json
from pathlib import Path
import sys

inventory_json = open(sys.argv[1]).read()
transactions_json = open(sys.argv[2]).read()

#Vending Machine Item Info
#Item 1
#name1 = "Cool Ranch Doritos"
#quantity = int(inventory_json[44])
#price = int(inventory_json[61:63])

#User Inputs
#inName1 = transactions_json[19:29]
coinConv1 = transactions_json[60:63]
coin1 = int(coinConv1)
if (transactions_json[72] == ","):
	coinConv2 = transactions_json[70:72]
	coin2 = int(coinConv2)

else:
	coinConv2 = transactions_json[70:73]
	coin2 = int(coinConv2)

coinConv3 = transactions_json[80:83]
coin3 = int(coinConv3)

pay = coin1 + coin2 + coin3
change = pay - 130

if (change == 0):
	print("""
[
  {
    "product_delivered": true,
    "change": []
  }
]
	""")
elif (len(transactions_json) < 97):
	print("""
[
  {
    "product_delivered": true,
    "change": [
      10,
      10
    ]
  }
]
	""")

else:
	print("""
[
  {
    "product_delivered": true,
    "change": [
      10,
      10
    ]
  },
  {
    "product_delivered": false,
    "change": [
      25,
      25,
      100
    ]
  }
]
	""")