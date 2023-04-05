import os
import requests
import config
from tester import safe_remove

OK = "OK"
E_WRONG_STATUS_CODE = "Wrong status code"
E_WRONG_CONTENT_LENGTH = "Wrong content length"
E_WRONG_CONTENT_TYPE = "Wrong content type"
E_WRONG_CONTENT = "Wrong content"

def baseUrl() -> str:
	return ("http://{}:{}/".format(config.SERVER_ADDRESS, config.SERVER_PORT))

def testGet() -> str:
	response = requests.get(baseUrl())
	try:
		with open(config.SERVER_ROOT + 'index.html', 'rb') as file:
			file_content = file.read()
	except FileNotFoundError:
		raise
	if (response.status_code != 200):
		return (E_WRONG_STATUS_CODE)
	if (int(response.headers["Content-Length"]) != len(file_content)):
		return (E_WRONG_CONTENT_LENGTH)
	if (response.headers["Content-Type"] != "text/html"):
		return (E_WRONG_CONTENT_TYPE)
	if (response.content != file_content):
		return (E_WRONG_CONTENT)
	return (OK)

def testGetSmall() -> str:
	response = requests.get(baseUrl() + '/test.png')
	try:
		with open(config.SERVER_ROOT + 'test.png', 'rb') as file:
			file_content = file.read()
	except FileNotFoundError:
		raise
	if (response.status_code != 200):
		return (E_WRONG_STATUS_CODE)
	if (int(response.headers["Content-Length"]) != len(file_content)):
		return (E_WRONG_CONTENT_LENGTH)
	if (response.headers["Content-Type"] != "image/png"):
		return (E_WRONG_CONTENT_TYPE)
	if (response.content != file_content):
		return (E_WRONG_CONTENT)
	return (OK)

def testGetMedium() -> str:
	response = requests.get(baseUrl() + '/ruffle/tboi.swf')
	try:
		with open(config.SERVER_ROOT + 'ruffle/tboi.swf', 'rb') as file:
			file_content = file.read()
	except FileNotFoundError:
		raise
	if (response.status_code != 200):
		return (E_WRONG_STATUS_CODE)
	if (int(response.headers["Content-Length"]) != len(file_content)):
		return (E_WRONG_CONTENT_LENGTH)
	if (response.headers["Content-Type"] != "application/x-shockwave-flash"):
		return (E_WRONG_CONTENT_TYPE)
	if (response.content != file_content):
		return (E_WRONG_CONTENT)
	return (OK)

def testGetHuge() -> str:
	response = requests.get(baseUrl() + '/100MB.bin')
	try:
		with open(config.SERVER_ROOT + '100MB.bin', 'rb') as file:
			file_content = file.read()
	except FileNotFoundError:
		raise
	if (response.status_code != 200):
		return (E_WRONG_STATUS_CODE)
	if (int(response.headers["Content-Length"]) != len(file_content)):
		return (E_WRONG_CONTENT_LENGTH)
	if (response.headers["Content-Type"] != "application/octet-stream"):
		return (E_WRONG_CONTENT_TYPE)
	if (response.content != file_content):
		return (E_WRONG_CONTENT)
	return (OK)

def testGetSmall() -> str:
	response = requests.get(baseUrl() + '/test.png')
	try:
		with open(config.SERVER_ROOT + 'test.png', 'rb') as file:
			file_content = file.read()
	except FileNotFoundError:
		raise
	if (response.status_code != 200):
		return (E_WRONG_STATUS_CODE)
	if (int(response.headers["Content-Length"]) != len(file_content)):
		return (E_WRONG_CONTENT_LENGTH)
	if (response.headers["Content-Type"] != "image/png"):
		return (E_WRONG_CONTENT_TYPE)
	if (response.content != file_content):
		return (E_WRONG_CONTENT)
	return (OK)

def testPostUppercase() -> str:
	data = {'text_input': "Lorem ipsum dolor sit amet, consectetur adipiscing elit."}
	response = requests.post(baseUrl() + '/cgi_test/to_upper.php', data=data)
	if (response.status_code != 200):
		return (E_WRONG_STATUS_CODE)
	if (int(response.headers["Content-Length"]) != len(data["text_input"])):
		return (E_WRONG_CONTENT_LENGTH)
	if (response.headers["Content-Type"] != "text/html; charset=UTF-8"):
		return (E_WRONG_CONTENT_TYPE)
	if (response.text != data["text_input"].upper()):
		return (E_WRONG_CONTENT)
	return (OK)

def testNotImplanted() -> str:
	response = requests.patch(baseUrl())
	if (response.status_code != 501):
		return (E_WRONG_STATUS_CODE)
	return (OK)

def testNotAllowed() -> str:
	response = requests.delete(baseUrl())
	if (response.status_code != 405):
		return (E_WRONG_STATUS_CODE)
	return (OK)

def testNotImplantedLocation() -> str:
	response = requests.patch(baseUrl() + 'html_test')
	if (response.status_code != 501):
		return (E_WRONG_STATUS_CODE)
	return (OK)

def testNotAllowedLocation() -> str:
	response = requests.delete(baseUrl() + 'html_test')
	if (response.status_code != 405):
		return (E_WRONG_STATUS_CODE)
	return (OK)

def testForbidden() -> str:
	response = requests.get(baseUrl() + 'forbidden.bin')
	if (response.status_code != 403):
		return (E_WRONG_STATUS_CODE)
	return (OK)

def testCgiNumbers() -> str:
	response = requests.get(baseUrl() + 'cgi_test/print_numbers.php')
	if (response.status_code != 200):
		return (E_WRONG_STATUS_CODE)
	if (int(response.headers["Content-Length"]) != 12):
		return (E_WRONG_CONTENT_LENGTH)
	if (response.headers["Content-Type"] != "text/html; charset=UTF-8"):
		return (E_WRONG_CONTENT_TYPE)
	if (response.text != "012345678910"):
		return (E_WRONG_CONTENT)
	return (OK)

def testCgiPythonNumbers() -> str:
	response = requests.get(baseUrl() + 'cgi_test/print_numbers.py')
	if (response.status_code != 200):
		return (E_WRONG_STATUS_CODE)
	if (int(response.headers["Content-Length"]) != 12):
		return (E_WRONG_CONTENT_LENGTH)
	if (response.headers["Content-Type"] != "text/plain"):
		return (E_WRONG_CONTENT_TYPE)
	if (response.text != "012345678910"):
		return (E_WRONG_CONTENT)
	return (OK)

def testCgiQuery() -> str:
	response = requests.get(baseUrl() + 'cgi_test/print_query.php?foo=bar&bar=foo')
	if (response.status_code != 200):
		return (E_WRONG_STATUS_CODE)
	if (int(response.headers["Content-Length"]) != 15):
		return (E_WRONG_CONTENT_LENGTH)
	if (response.headers["Content-Type"] != "text/html; charset=UTF-8"):
		return (E_WRONG_CONTENT_TYPE)
	if (response.text != "foo=bar&bar=foo"):
		return (E_WRONG_CONTENT)
	return (OK)

def testUploadSingle() -> str:
	try:
		with open(config.SERVER_ROOT + '100MB.bin', 'rb') as file:
			file_content = file.read()
	except FileNotFoundError:
		raise
	files = {'file': ('100MB.bin', file_content, 'application/octet-stream')}
	response = requests.post(baseUrl() + 'upload_files', files=files)
	if (response.status_code != 204):
		print(response.status_code)
		return (E_WRONG_STATUS_CODE)
	try:
		with open(config.SERVER_ROOT + 'uploads/100MB.bin', 'rb') as file:
			uploaded_file_content = file.read()
	except FileNotFoundError:
		safe_remove(config.SERVER_ROOT + 'uploads/100MB.bin')
		raise
	if (len(uploaded_file_content) != len(file_content)):
		safe_remove(config.SERVER_ROOT + 'uploads/100MB.bin')
		return (E_WRONG_CONTENT_LENGTH)
	if (uploaded_file_content != file_content):
		safe_remove(config.SERVER_ROOT + 'uploads/100MB.bin')
		return (E_WRONG_CONTENT)
	safe_remove(config.SERVER_ROOT + 'uploads/100MB.bin')
	return (OK)

def testUploadMultiple() -> str:
	try:
		with open(config.SERVER_ROOT + '100MB.bin', 'rb') as file1, open(config.SERVER_ROOT + '50MB.bin', 'rb') as file2:
			file1_content = file1.read()
			file2_content = file2.read()
	except FileNotFoundError:
		raise
	files = {'file1': ('100MB.bin', file1_content, 'application/octet-stream'), 
			'file2': ('50MB.bin', file2_content, 'application/octet-stream')}
	response = requests.post(baseUrl() + 'upload_files', files=files)
	if (response.status_code != 204):
		print(response.status_code)
		return (E_WRONG_STATUS_CODE)
	try:
		with open(config.SERVER_ROOT + 'uploads/100MB.bin', 'rb') as file1, open(config.SERVER_ROOT + 'uploads/50MB.bin', 'rb') as file2:
			uploaded_file1_content = file1.read()
			uploaded_file2_content = file2.read()
	except FileNotFoundError:
		safe_remove(config.SERVER_ROOT + 'uploads/100MB.bin')
		safe_remove(config.SERVER_ROOT + 'uploads/50MB.bin')
		raise
	if (len(uploaded_file1_content) != len(file1_content)) or (len(uploaded_file2_content) != len(file2_content)):
		safe_remove(config.SERVER_ROOT + 'uploads/100MB.bin')
		safe_remove(config.SERVER_ROOT + 'uploads/50MB.bin')
		return (E_WRONG_CONTENT_LENGTH)
	if (uploaded_file1_content != file1_content) or (uploaded_file2_content != file2_content):
		safe_remove(config.SERVER_ROOT + 'uploads/100MB.bin')
		safe_remove(config.SERVER_ROOT + 'uploads/50MB.bin')
		return (E_WRONG_CONTENT)
	safe_remove(config.SERVER_ROOT + 'uploads/100MB.bin')
	safe_remove(config.SERVER_ROOT + 'uploads/50MB.bin')
	return (OK)
