import os
import sys
from cryptography.fernet import Fernet

def	showHelp():
	print("Stockholm Ransomware Help:")
	print("[-v|-version] : Show the program's version")
	print("[-h|-help] : Show the help page (this what you're looking at)")
	print("[-r|-reverse] ENCRYPTION_KEY: Decrypt files if the given ENCRYPTION_KEY is valid")
	print("[-s|-silent] ENCRYPTION_KEY: Silence all output message")

def	showVersion():
	print("Stockholm Ransomware v1.0.0")

def setValue(settings: dict, attr: str, value: bool):
	settings[attr] = value

def main(settings: dict):
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
			sys.exit("Usage : python3 ./stockholm.py [-hvrs] ENCRYPTION_KEY")
		if (arg == '-r' or arg == '-reverse'):
			if len(sys.argv) > i + 1:
				settings["key"] = sys.argv[i + 1]
			else:
				sys.exit("Usage : python3 ./stockholm.py [-hvrs] ENCRYPTION_KEY")
	main(settings)