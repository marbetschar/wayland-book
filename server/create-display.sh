#!/bin/bash

cc -o create-display create-display.c -lwayland-server
./create-display