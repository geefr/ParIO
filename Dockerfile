FROM debian:9
LABEL project="ParIO"
LABEL MAINTAINER Gareth Francis (gfrancis.dev@gmail.com)
RUN apt-get update && apt-get install -y cmake
 
