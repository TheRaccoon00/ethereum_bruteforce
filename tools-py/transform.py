from secrets import token_bytes
from coincurve import PublicKey
from sha3 import keccak_256
import hashlib
import sys

"""
Convert a worlist into a public address list (ethereum wallet)
"""

if len(sys.argv) != 2:
	print("Argument is missing. Usage: python3 transform.py [WORDLIST].txt")
	sys.exit()

if sys.argv[1][-4:] != ".txt":
	print("The wordlist needs to be a txt file !")
	sys.exit()

wordlist_name = sys.argv[1][:-4]
wordlist_address_file = open(wordlist_name+"_address.txt","w")

with open(wordlist_name+".txt", "r", encoding="ISO-8859-1") as wordlist:
	for word in wordlist:
		try:
			private_key = hashlib.sha256(word[:-1].encode('utf-8')).digest()
			public_key = PublicKey.from_valid_secret(private_key).format(compressed=False)[1:]
			addr = keccak_256(public_key).digest()[-20:]
			wordlist_address_file.write('0x'+addr.hex())
			wordlist_address_file.write("\n")
		except:
			pass
wordlist.close()
wordlist_address_file.close()
