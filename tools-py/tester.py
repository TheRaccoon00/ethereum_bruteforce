from coincurve import PublicKey
from sha3 import keccak_256
import hashlib
import sys

"""
Convert a word into a public address (ethereum wallet)
"""

if len(sys.argv) < 2:
	print("Argument is missing. Usage: python3 tester.py [word]")
	sys.exit()

word = sys.argv[1]

private_key = hashlib.sha256(word.encode('utf-8')).digest()
public_key = PublicKey.from_valid_secret(private_key).format(compressed=False)[1:]
addr = keccak_256(public_key).digest()[-20:]

print('0x'+addr.hex())
