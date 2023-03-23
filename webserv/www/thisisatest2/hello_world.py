import os

print("Content-Type: text/html")
print()
print("<html>")
print("<head><title>CGI Test</title></head>")
print("<body>")
print("<h1>CGI Test</h1>")
print("<p>This is a test of the CGI script.</p>")
print("<p>Environment variables:</p>")
print("<ul>")
for key, value in os.environ.items():
    print("<li>{}: {}</li>".format(key, value))
print("</ul>")
print("</body>")
print("</html>")