FROM        debian:buster 
RUN         apt-get -y update && apt-get install -y mariadb-server
COPY        ./init_db.sh /init_db.sh
COPY        50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
RUN         chmod 700 /init_db.sh
ENTRYPOINT  ["/bin/sh", "/init_db.sh"]
EXPOSE      3306