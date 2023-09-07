# Set the base image
FROM ubuntu:latest

# Set the working directory
WORKDIR /app

# Copy the necessary files to the container
COPY FIFA23_official_data.csv /app
COPY storage.c /app

# Install dependencies and set up the environment
RUN apt-get update && \
    apt-get install -y gcc

# Define the command to compile and run the C program
CMD gcc -o storage storage.c && ./storage
