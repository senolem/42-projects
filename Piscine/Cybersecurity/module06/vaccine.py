import os
import sys
import requests
import shutil
import urllib
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse

def is_vulnerable(response):
	print("blabla")
	return True

def get_form_data(form):
	try:
		action = form.attrs.get("action").lower()
	except:
		action = None
	data = {}
	inputs = []
	if form.has_attr("action"):
		method = form.attrs.get("method", "get").lower()
		for element in form.find_all("input"):
			type = element.attrs.get("type", "text")
			name = element.attrs.get("name")
			value = element.get("value", "")
			inputs.append({"type": type, "name": name, "value": value})
		data["action"] = action
		data["method"] = method
		data["inputs"] = inputs
		return data

def scan_sqli(url: str):
	for c in "\"'":
		self_url = f"{url}{c}"
		print(f"Checking for '{self_url}' (injection on the provided URL)")
		response = requests.get(self_url)
		if is_vulnerable(response):
			print(f"[!] Potential SQL Injection vulnerability detected on '{self_url}'")
	print(f"Scanning {url}...")
	response = requests.get(url)
	soup = BeautifulSoup(response.content, 'html.parser')
	forms = soup.find_all('form')
	print(f"Found {len(forms)} form(s).")
	if len(forms) != 0:
			print(f"Scanning for potential SQL injections...")
	for form in forms:
		form_data = get_form_data(form)
		for c in "\"'":
			request_data = {}
			for input in form_data["inputs"]:
				try:
					if input["value"] or input["type"] == "hidden":
						request_data[input["name"]] = input["value"] + c
					elif input["type"] == "submit":
						request_data[input["name"]] = f"test{c}"
				except Exception as e:
						print(f"Error : {e}")
			entrypoint = urljoin(url, form_data["action"])
			if form_data["method"] == "get":
				response = requests.get(url, params=request_data)
			elif form_data["method"] == "post":
				response = requests.post(entrypoint, data=request_data)
	

def main(archive: str, method: str, url: str):
	scan_sqli(url)
	return

if (__name__ == "__main__"):
	archive = "vaccine.tar.gz"
	method = "GET"
	url = ""
	if len(sys.argv) < 2 or len(sys.argv) > 6 or len(sys.argv) % 2 != 0:
		sys.exit("Usage: python3 ./vaccine [-oX] URL")
	for i, arg in enumerate(sys.argv):
		if arg == '-o' or arg == '-X':
			if len(sys.argv) <= i:
				sys.exit("Usage: python3 ./vaccine [-oX] URL")
			else:
				if arg == '-o' and len(sys.argv) > i + 1:
					archive = sys.argv[i + 1]
				elif arg == '-X' and len(sys.argv) > i + 1:
					method = sys.argv[i + 1]
				else:
					sys.exit("Usage: python3 ./vaccine [-oX] URL")
		elif i == 0 or i == len(sys.argv) - 1 or (i > 0 and (sys.argv[i - 1] == '-o' or sys.argv[i - 1] == '-X')):
			continue
		else:
			sys.exit("Usage: python3 ./vaccine [-oX] URL")
	url = sys.argv[len(sys.argv) - 1]
	main(archive, method, url)