import os
import sys
import time
import struct
import hmac
import hashlib
import config
import base64
import qrcode
import secrets
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
			length = len(secret)
		if (length % 2):
			sys.exit(f"Error: Cannot read secret file! (secret length is odd!)")
		return length
	except Exception as e:
		sys.exit(f"Error: Cannot read secret file! ({e})")

def get_secret_str() -> str:
	try:
		with open(sys.argv[2], 'rb') as file:
			return file.read().decode('utf-8')
	except Exception:
		sys.exit(f"Error: Cannot read secret file! ({e})")

def generate_otp_uri(secret: bytes, name: str, issuer: str) -> str:
	base32_secret = base64.b32encode(secret).decode('utf-8')
	otp_uri = f"otpauth://totp/{issuer}:{name}?secret={base32_secret}&issuer={issuer}"
	return otp_uri

def generate_qr_code():
	otp_uri = generate_otp_uri(decrypt_secret(), 'ft_otp', 'albaur')
	qr = qrcode.QRCode(version=1, box_size=10, border=4)
	qr.add_data(otp_uri)
	qr.make(fit=True)
	image = qr.make_image(fill_color="black", back_color="white")
	image.show()


def otp_generator() -> str:
	secret = decrypt_secret().decode('utf-8')
	key = bytes.fromhex(secret)
	intervals = struct.pack('>Q', int(time.time() // 30))
	hmac_hash = hmac.new(key, intervals, hashlib.sha256).digest()
	offset = hmac_hash[-1] & 15
	truncated_hash = (struct.unpack(">I", hmac_hash[offset:offset+4])[0] & 0x7fffffff) % 1000000
	otp = str(truncated_hash)
	return otp.rjust(6, '0')

def main():
	if (sys.argv[1] == '-g'):
		key = get_secret_str()
		encrypt_secret(key.encode())
		print("ft_otp.key file created successfully. You can now generate OTPs using python3 ./ft_otp.py -k ft_otp.key")
	elif (sys.argv[1] == '-k'):
		otp = str(otp_generator())
		print(f"Your password is : {otp[:3]} {otp[3:]}")
	elif (sys.argv[1] == '-q'):
		key = secrets.token_hex(32)
		print(key)
		encrypt_secret(key.encode())
		print("ft_otp.key file created successfully. You can now generate OTPs using python3 ./ft_otp.py -k ft_otp.key")
		generate_qr_code()

if (__name__ == "__main__"):
	if len(sys.argv) != 3 or (sys.argv[1] != '-k' and sys.argv[1] != '-g' and sys.argv[1] != '-q'):
		sys.exit("Usage: python3 ./ft_otp.py [-gkq] secret|key")
	elif sys.argv[1] == '-g' and (get_secret_len() < 64 or is_hex(get_secret_str())):
		sys.exit("Error: key must be at least 64 hexadecimal characters.")
	main()