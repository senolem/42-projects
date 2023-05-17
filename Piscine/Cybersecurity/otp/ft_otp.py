import os
import sys
import time
import struct
import hmac
import hashlib
import config
from cryptography.fernet import Fernet

def is_hex(key: str) -> int:
	try:
		value = int(key, 16)
	except ValueError:
		return 1
	return 0

def encrypt_secret(secret: bytes):
	try:
		with open('ft_otp.key', "wb") as file:
			file.write(Fernet(config.ENCRYPT_KEY).encrypt(secret))
	except Exception as e:
		sys.exit(f"Error: Cannot write ft_otp.key! ({e})")

def decrypt_secret() -> bytes:
	try:
		with open(sys.argv[2], 'rb') as file:
			secret = file.read()
		return Fernet(config.ENCRYPT_KEY).decrypt(secret)
	except Exception as e:
		sys.exit(f"Error: Cannot read secret file! ({e})")

def get_secret_len() -> int:
	try:
		with open(sys.argv[2], 'rb') as file:
			secret = file.read()
		return len(secret)
	except Exception as e:
		sys.exit(f"Error: Cannot read secret file! ({e})")

def get_secret_str() -> str:
	try:
		with open(sys.argv[2], 'rb') as file:
			return file.read().decode('utf-8')
	except Exception:
		sys.exit(f"Error: Cannot read secret file! ({e})")

def otp_generator() -> str:
	secret = decrypt_secret()
	intervals = int(time.time() / 30)
	intervals_packed = struct.pack('>Q', intervals)
	hmac_hash = hmac.new(secret, intervals_packed, hashlib.sha256).digest()
	offset = hmac_hash[-1] & 0x0F
	truncated_hash = hmac_hash[offset:offset+4]
	otp = struct.unpack('>I', truncated_hash)[0] & 0x7FFFFFFF
	otp_str = str(otp % 10**6).rjust(6, '0')
	return otp_str

def main():
	if (sys.argv[1] == '-g'):
		key = get_secret_str()
		encrypt_secret(key.encode())
		print("ft_otp.key file created successfully. You can now generate OTPs using python3 ./ft_otp.py -k ft_otp.key")
	elif (sys.argv[1] == '-k'):
		otp = otp_generator()
		print(f"Your password is : {otp[:3]} {otp[3:]}")

if (__name__ == "__main__"):
	if len(sys.argv) != 3 or (sys.argv[1] != '-k' and sys.argv[1] != '-g'):
		sys.exit("Usage: python3 ./ft_otp.py [-gk] secret|key")
	elif sys.argv[1] == '-g' and (get_secret_len() < 64 or is_hex(get_secret_str())):
		sys.exit("Error: key must be at least 64 hexadecimal characters.")
	main()