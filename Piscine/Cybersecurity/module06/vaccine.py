import os
import sys
import requests
import re
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse

def parse_errors():
	try:
		with open('errors.xml', 'r') as file:
			data = file.read()
		error_soup = BeautifulSoup(data, 'xml')
		return error_soup
	except Exception as e:
		sys.exit(f"Error: 'errors.xml' parsing failed. ({e})")

def is_vulnerable(response, error_soup, occurences) -> bool:
	local_occurences = []
	try:
		for dbms_element in error_soup('dbms'):
			dbms_value = dbms_element['value']
			for error_element in dbms_element.find_all('error'):
				regexp = error_element['regexp']
				fork = error_element.get('fork')
				if re.search(regexp, response.text, re.IGNORECASE):
					occurence = {
						'dbms': dbms_value,
						'regxp': regexp,
						'fork' : fork
					}
					local_occurences.append(occurence)
	except Exception as e:
		print(f"Error : {e}")
	if len(local_occurences) > 0:
		for occurence in local_occurences:
			occurences.append(occurence)
		return True
	else:
		return False

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
	return None

def scan_sqli(url: str, occurences):
	vuln_form_found = 0
	error_soup = parse_errors()
	print(f"Checking for '{url}' with single/double quote (injection on the provided URL)")
	for c in "\"'":
		self_url = f"{url}{c}"
		try:
			response = requests.get(self_url)
		except Exception as e:
			sys.exit(f"Error : {e}")
		if is_vulnerable(response, error_soup, occurences):
			print(f"\033[91m[!]\033[0m Potential SQL Injection vulnerability detected on '{self_url}'")
	print(f"Looking for forms at {url} ...")
	response = requests.get(url)
	soup = BeautifulSoup(response.content, 'html.parser')
	forms = soup.find_all('form')
	print(f"Found {len(forms)} form(s).")
	if len(forms) != 0:
			print(f"Scanning for potential SQL injections...")
	for form in forms:
		form_data = get_form_data(form)
		if form_data:
			for c in "\"'":
				request_data = {}
				for input in form_data["inputs"]:
					try:
						if input["value"] or input["type"] == "hidden":
							request_data[input["name"]] = input["value"] + c
							print(input["value"] + c)
						elif input["type"] == "submit":
							request_data[input["name"]] = f"test{c}"
							print("submit")
					except Exception as e:
							print(f"Error : {e}")
				entrypoint = urljoin(url, form_data["action"])
				if form_data["method"] == "get":
					response = requests.get(url, params=request_data)
				elif form_data["method"] == "post":
					response = requests.post(entrypoint, data=request_data)
				if form_data["method"] == "get" or form_data["method"] == "post":
					if is_vulnerable(response, error_soup, occurences):
						print(f"\033[91m[!]\033[0m Potential SQL Injection vulnerability detected on '{self_url}' :")
						vuln_form_found += 1
	if vuln_form_found == 0:
		print(f"No vulnerability detected.")
	

def main(archive: str, method: str, url: str):
	occurences = []
	scan_sqli(url, occurences)
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