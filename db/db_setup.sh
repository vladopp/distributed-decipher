#!/bin/bash

# NOTE: this script assumes that
# the following directory is in your PATH
# C:\Program Files\PostgreSQL\9.6\bin

# Unfortunately, this script doesn't work as psql requires password at each step.
# However, it could be used as a reference for running each separate command manually.

SCRIPTPATH="db_setup.sql"

echo "Dropping old DB"
dropdb --username=postgres deciphy

echo "Creating new DB"
createdb --username=postgres deciphy

echo "Creating tables and relations in DB"
psql --file=$SCRIPTPATH --username=postgres deciphy