import os

print("Content-Type: text/html\r\n", end="")
print("Set-Cookie: mycookie=abc123; Expires=Wed, 21 Apr 2023 06:08:41 GMT; Path=/\r\n\r\n", end="")
print("Set-Cookie: mycookie2=efg456; Expires=Wed, 21 Apr 2023 06:08:41 GMT; Path=/\r\n\r\n", end="")
print("<html>")
print("<head><title>Python CGI Test</title></head>")
print("<body>")
print("<h1>Python CGI Test</h1>")
print("<p>This is a test of the Python CGI script.</p>")
print("<p>Environment variables:</p>")
print("<ul>")
for key, value in os.environ.items():
    print("<li>{}: {}</li>".format(key, value))
print("</ul>")
print("</body>")
print("</html>")