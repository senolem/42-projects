import os
import sys
from PIL import Image

def get_exif(path: str):
	return Image.open(path)

def main():
	for file in sys.argv[1:]:
		exif = get_exif(file)
		for metadata in exif:
			print(metadata)

if (__name__ == "__main__"):
	if len(sys.argv) == 1:
		sys.exit("Usage: python3 ./scorpion.py FILE1 [FILE2 ...]")
	main()
