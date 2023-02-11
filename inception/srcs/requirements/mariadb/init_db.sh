if [ ! -d "/var/lib/mysql/wordpress" ]; then 
    mysql_install_db
    service mysql start
    sleep 5
    mysql -e "CREATE USER '${MYSQL_USER}'@'localhost' identified by '${MYSQL_PASSWORD}';" &&\
	mysql -e "CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};" &&\
	mysql -e "GRANT ALL PRIVILEGES ON *.* TO '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';" &&\
	mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}'; FLUSH PRIVILEGES;"
    mysqladmin -uroot -p${MYSQL_ROOT_PASSWORD} shutdown
fi
mysqld