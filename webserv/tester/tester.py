import os
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
		print("{}Error: Failed to open file {}{}".format(C_RED, e.filename, C_NONE))
		exit(1)
	except Exception as e:
		print("{}Error: {}{}".format(C_RED, e, C_NONE))
		exit(1)
	if (result == "OK"):
		print("✅ {} : {}OK!{}".format(test_description, C_GREEN, C_NONE))
	else:
		print("❌ {} : {}{}{}".format(test_description, C_RED, result, C_NONE))

def batchStart() -> None:
	tests = [
	{"test_category": "GET", "functions": [
		{"test_description": "GET / (200)", "test_function": testGet},
		{"test_description": "GET /test.png (200)", "test_function": testGetSmall},
		{"test_description": "GET /ruffle/tboi.swf (200)", "test_function": testGetMedium},
		{"test_description": "GET /{} (200)".format(config.FILE_1), "test_function": testGetHuge}
	]},
	{"test_category": "POST", "functions": [
		{"test_description": "POST /cgi_test/to_upper.php (200)", "test_function": testPostUppercase},
		{"test_description": "POST /cgi_test/to_upper.php (chunked) (200)", "test_function": testPostUppercaseChunked},
		{"test_description": "POST /cgi_test/to_upper.php (case sensitive headers) (200)", "test_function": testCaseSensitiveHeaders}
	]},
	{"test_category": "Status codes", "functions": [
		{"test_description": "PATCH / (501)", "test_function": testNotImplanted},
		{"test_description": "DELETE / (405)", "test_function": testNotAllowed},
		{"test_description": "PATCH /html_test (501)", "test_function": testNotImplantedLocation},
		{"test_description": "DELETE /html_test (405)", "test_function": testNotAllowedLocation},
		{"test_description": "GET /{} (403)".format(config.FILE_FORBIDDEN), "test_function": testForbidden},
		{"test_description": "GET /{} (404)".format(config.FILE_NOT_FOUND), "test_function": testNotFound},
		{"test_description": "GET /html_test/{} (404)".format(config.FILE_NOT_FOUND), "test_function": testNotFoundLocation},
		{"test_description": "GET /to/redirect (301)", "test_function": testPermanentRedirection},
		{"test_description": "GET /redirect/to (302)", "test_function": testTemporaryRedirection},
		{"test_description": "GET /redirect/to/{} (404)".format(config.FILE_NOT_FOUND), "test_function": testTemporaryRedirectionNotFound}
	]},
	{"test_category": "CGI", "functions": [
		{"test_description": "GET /cgi_test/print_numbers.php (200)", "test_function": testCgiNumbers},
		{"test_description": "GET /cgi_test/print_numbers.py (200)", "test_function": testCgiPythonNumbers},
		{"test_description": "GET /cgi_test/print_query.php?foo=bar&bar=foo (200)", "test_function": testCgiQuery}
	]},
		{"test_category": "Upload", "functions": [
			{"test_description": "POST / (upload {}) (204)".format(config.FILE_1), "test_function": testUploadSingle},
			{"test_description": "POST / (upload {} & {}) (204)".format(config.FILE_1, config.FILE_2), "test_function": testUploadMultiple}
		]},
		]
	for current_test in tests:
		print("🔨 Now testing : {}{}{}".format(current_test["test_category"], C_BLUE, C_NONE))
		for current_function in current_test["functions"]:
			runTest(current_function["test_description"], current_function["test_function"])
		print("")

def prepare() -> None:
	safe_remove(config.SERVER_ROOT + config.SERVER_UPLOAD + config.FILE_1)
	safe_remove(config.SERVER_ROOT + config.SERVER_UPLOAD + config.FILE_2)
	os.chmod(config.SERVER_ROOT + config.FILE_FORBIDDEN, 0o000)
def cleanup() -> None:
	safe_remove(config.SERVER_ROOT + config.SERVER_UPLOAD + config.FILE_1)
	safe_remove(config.SERVER_ROOT + config.SERVER_UPLOAD + config.FILE_2)
	os.chmod(config.SERVER_ROOT + config.FILE_FORBIDDEN, 0o755)

def safe_remove(file_path):
	try:
		os.remove(file_path)
	except OSError:
		pass

if (__name__ == "__main__"):
	print("🌐 Webserv Tester v{} by albaur{}{}\n".format(VERSION, C_BLUE, C_NONE))
	prepare()
	batchStart()
	cleanup()