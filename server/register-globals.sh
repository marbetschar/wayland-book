#!/bin/bash

cc -o register-globals register-globals.c -lwayland-server
./register-globals