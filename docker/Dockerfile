FROM ubuntu:20.04
ARG CHECKOUT=master
RUN apt update

RUN DEBIAN_FRONTEND="noninteractive" apt-get -y install tzdata

RUN apt -y install autoconf automake autotools-dev bc \
    bison build-essential curl expat libexpat1-dev flex gawk gcc git \
    gperf libgmp-dev libmpc-dev libmpfr-dev libtool texinfo tmux \
    patchutils zlib1g-dev wget bzip2 patch vim-common lbzip2 python \
    pkg-config libglib2.0-dev libpixman-1-dev libssl-dev screen locales \
    device-tree-compiler expect makeself unzip cpio rsync cmake ninja-build p7zip-full \
    ripgrep fd-find tree cscope universal-ctags
# last line are just some tools suggested by AI
RUN apt-get update && apt-get install --reinstall ca-certificates

# Set the locale
# Ubuntu: https://stackoverflow.com/a/28406007
RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && \
    locale-gen
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

# User/group names/ids which will be overwritten: https://stackoverflow.com/a/44683248
ARG UNAME
ARG GNAME
ARG UID
ARG GID
RUN groupadd -g $GID -o $GNAME
# Add a user
RUN useradd -m -u $UID -g $GID -o -s /bin/bash $UNAME

# Set the user (for subsequent commands)
USER $UNAME

# Set the working directory (for subsequent commands)
WORKDIR /home/$UNAME

# Run when the container launches
CMD /bin/bash
