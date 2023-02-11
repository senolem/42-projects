FROM		debian:buster
RUN			apt-get -y update && apt-get -y install php7.3 php-fpm php-mysql sendmail wget sudo
COPY		./www.conf /etc/php/7.3/fpm/pool.d/www.conf
COPY		./install_wordpress.sh /install_wordpress.sh
RUN         touch /var/log/php7.3-fpm.log && chown www-data:www-data /var/log/php7.3-fpm.log && chmod 755 /var/log/php7.3-fpm.log
RUN         mkdir -p /run/php && touch /run/php/php7.3-fpm.pid && chown www-data:www-data /run/php/php7.3-fpm.pid && chmod 755 /run/php/php7.3-fpm.pid
RUN         chmod +x /install_wordpress.sh
RUN         mkdir -p /run/php/ && touch /run/php/php7.3-fpm.pid
RUN         wget -O /usr/local/bin/wp https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && chmod +x /usr/local/bin/wp
COPY		./wp-config.php /wp-config.php
ENTRYPOINT	["/bin/sh", "/install_wordpress.sh"]
EXPOSE		9000
