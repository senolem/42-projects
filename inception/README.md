# Inception

### Prerequisites

Install docker engine, docker-compose, and sudo :

    apt-get install -y docker-ce sudo

Add your current user to the docker and sudo groups :

    usermod -aG docker $USER
    usermod -aG sudo $USER

### How to use?
Build the images and start the containers :

    make

You can stop containers :

    make stop

As well as you can start them :

    make start

Stop containers, delete mounted volumes and clean caches :

    make fclean

### Notes :

The webserver is configured to be accessible on localhost:443 only. I've seen many errors that should make the evaluation fail, for example exposing all ports in docker-compose.
Other common errors are that people don't check their containers logs (wtf?), the wordpress website works as expected, but some commands failed.

Perhaps this isn't asked by the subject, I removed --allow-root (that literally EVERYBODY seems to use at 42!) from all wp-cli core commands, as this can be extremely dangerous on a production environment (see https://make.wordpress.org/cli/handbook/guides/common-issues/#error-yikes-it-looks-like-youre-running-this-as-root) and managed to run those commands with the www-data user. Yes we are using a development environment, yes we run the containers inside a VM but this isn't a reason to why we shouldn't be aware of fundamental security principles.

mysqld is configured to run automatically as mysql user such as nginx uses the www-data for its worker processes, so they should be safe to start even as root user.

both www and maria db data folders are mounted in your home directory.

Please don't just copy my files to do this project. There is many specific things to learn with this project, and docker containers are very powerful and easy to use (except if you're asked to build an image from scratch...).

