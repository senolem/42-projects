# webserv

Webserv project done all by myself.

<p align="center">
  <img src="https://i.imgur.com/nRNes00.png">
</p>

Accepted methods are GET, HEAD, POST and DELETE.
Server has been stress tested with siege to support 1000 concurrent connections, with an availability of 99.9%.

Upload is supported when sending a valid multipart/form-data body.

Configuration syntax is inspired by nginx. Accepted parameters are the following :

| Parameter  | Accepted arguments |
| ------------- | ------------- |
| listen  | any valid port |
| server_name  | domain name or IP  |
| access_log  | path to an existing file  |
| client_max_body_size  | size in bytes  |
| error_page  | any valid HTTP status code followed by an existing html file  |
| root  | any valid folder  |
| methods_allowed  | GET \| HEAD \| POST \| DELETE |
| index | any single or multiples existing html file |
| autoindex  | on \| off |
| cgi_pass | any file extension followed by an existing binary file |
| redirect | any valid URI followed by 301 \| 302 |

Each parameter can be attributed to a location block except for listen, server_name, error_page and access_log.

There is also parameters inside the includes/webserv.hpp file :

## webserv.hpp parameters

```c++
# define BUFFER_SIZE 8192 // BUFFER_SIZE used for recv/send
# define MAX_REQUEST_SIZE_PROTECTION 0 // Additional protection to avoid server overloading by sending huge headers
# define MAX_CLIENTS_PER_SOCKET 1000 // Maximum concurrent connections for each listened port
# define CLIENT_TIMEOUT 30 // Time in seconds before the connection to a client is closed (timer is resetted if the client sends data)
# define PRINT_REQUESTS 1 // Print or not incoming requests in stdout
# define LOG_REQUEST_LENGTH_LIMIT -1 // Print or not incoming requests in log file, and limit their size (-1 to disable logging, 0 to disable logging limit or any number > 0 to limit logged request size)
# define PRINT_REQUEST_LENGTH_LIMIT 512 // Limit printed request in stdout 
```

An example default.conf file is available in the conf folder.

This project also provides a custom python tester than can be adapted to your own website. It currently has some GET, POST, status codes, CGI and uploads tests.
