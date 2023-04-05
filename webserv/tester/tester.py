import os
import sys
import config
from typing import Callable
from tests import *

VERSION = "1.0"
C_NONE = "\033[0m"
C_RED = "\033[31m"
C_GREEN = "\033[32m"
C_BLUE = "\033[34m"

def runTest(test_description: str, test_func: Callable) -> None:
	try:
		result = test_func()
	except FileNotFoundError as e:
		print("{}Failed to open file {}{}".format(C_RED, e.filename, C_NONE))
		exit(1)
	except Exception as e:
		print("{}An error occurred: {}{}".format(C_RED, e, C_NONE))
		print("{}Failed to connect to server {}:{}{}".format(C_RED, config.SERVER_ADDRESS, config.SERVER_PORT, C_NONE))
		exit(1)
	if (result == "OK"):
		print("✅ {} : {}OK!{}".format(test_description, C_GREEN, C_NONE))
	else:
		print("❌ {} : {}{}{}".format(test_description, C_RED, result, C_NONE))

def batchStart() -> None:
	tests = [
		{"test_category": "GET", "functions": [
			{"test_description": "GET /", "test_function": testGet},
			{"test_description": "GET /test.png", "test_function": testGetSmall},
			{"test_description": "GET /ruffle/tboi.swf", "test_function": testGetMedium},
			{"test_description": "GET /100MB.bin", "test_function": testGetHuge}
		]},
		{"test_category": "POST", "functions": [
			{"test_description": "POST /cgi_test/to_upper.php", "test_function": testPostUppercase},
			{"test_description": "GET /test.png", "test_function": testGet}
		]},
		{"test_category": "Status codes", "functions": [
			{"test_description": "PATCH /", "test_function": testNotImplanted},
			{"test_description": "DELETE /", "test_function": testNotAllowed},
			{"test_description": "PATCH /html_test", "test_function": testNotImplantedLocation},
			{"test_description": "DELETE /html_test", "test_function": testNotAllowedLocation},
			{"test_description": "GET /forbidden.bin", "test_function": testForbidden}
		]},
		{"test_category": "CGI", "functions": [
			{"test_description": "GET /cgi_test/print_numbers.php", "test_function": testCgiNumbers},
			{"test_description": "GET /cgi_test/print_numbers.py", "test_function": testCgiPythonNumbers},
			{"test_description": "GET /cgi_test/print_query.php?foo=bar&bar=foo", "test_function": testCgiQuery}
		]},
		{"test_category": "Upload", "functions": [
			{"test_description": "POST / (upload 100MB.bin)", "test_function": testUploadSingle},
			{"test_description": "POST / (upload 100MB.bin & 50MB.bin)", "test_function": testUploadMultiple}
		]},
		]
	for current_test in tests:
		print("🔨 Now testing : {}{}{}".format(current_test["test_category"], C_BLUE, C_NONE))
		for current_function in current_test["functions"]:
			runTest(current_function["test_description"], current_function["test_function"])
		print("")

if (__name__ == "__main__"):
	print("🌐 Webserv Tester v{} by albaur{}{}\n".format(VERSION, C_BLUE, C_NONE))
	batchStart()