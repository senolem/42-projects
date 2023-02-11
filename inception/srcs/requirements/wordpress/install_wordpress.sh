if [ ! -f "/var/www/html/index.php" ]; then
    sleep 10
    mkdir -p /var/www/html && chown -R www-data:www-data /var/www/html && chmod -R 755 /var/www/html
    mkdir -p /var/www/.wp-cli && chown -R www-data:www-data /var/www/.wp-cli && chmod -R 755 /var/www/.wp-cli
    sudo -u www-data wp core download --path="/var/www/html/"
    mv /wp-config.php /var/www/html/wp-config.php
    sudo -u www-data wp core install --path="/var/www/html/" --url=${WP_HOSTNAME} --title=${WP_TITLE} --admin_user=${WP_ADMIN_USER} --admin_password=${WP_ADMIN_PASSWORD} --admin_email=${WP_ADMIN_EMAIL}
    sudo -u www-data wp user create --path="/var/www/html/" ${WP_USER} ${WP_EMAIL} --role=author --user_pass=${WP_PASSWORD}
fi
php-fpm7.3 -F