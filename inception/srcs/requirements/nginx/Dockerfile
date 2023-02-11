FROM    debian:buster
RUN     apt-get -y update && apt-get -y install nginx openssl
COPY    ./nginx.conf /etc/nginx/conf.d/nginx.conf
RUN     openssl req -x509 -nodes -days 365 -newkey rsa:4096 -keyout /etc/ssl/private/nginx.key -out /etc/ssl/certs/nginx.pem -subj "/C=FR/ST=Haut-Rhin/L=Mulhouse/O=42 Network/OU=42/CN=albaur.42.fr"
CMD     ["nginx", "-g", "daemon off;"]
EXPOSE  443