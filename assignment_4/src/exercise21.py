import hashlib
import hmac

key = str.encode("hilko-janssen")
my = open("data/ex21/security.png", "rb").read()

h = hmac.new( key, my, hashlib.sha256 )
print("key:", key)
print("HMAC hash value:", h.hexdigest())
